/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** file for Scene functions
*/

#include "core/RayTracer.hpp"

#include "core/library/IDisplay.hpp"
#include "core/env/object/ILight.hpp"

#include "core/env/scene/Scene.hpp"

#include "core/math/Rectangle.hpp"
#include "core/math/Transformation3.hpp"
#include "core/math/Point.hpp"

#include <omp.h>

#include <stack>
#include <utility>

#include <chrono>

namespace RayTracer
{
    Scene::Scene(const std::shared_ptr<SceneNode> &sceneNode, int jobCount, bool fast) :
        _transformer(sceneNode),
        _jobCount(jobCount),
        _fast(fast)
    {}

    void Scene::render(SceneContext &context, std::shared_ptr<IDisplay> &display)
    {
        const RayTracer &raytracer = RT();

        Rectangle2i    viewport        = context.camera->getViewport();
        DisplayLibrary &displayLibrary = raytracer.getDisplayLibrary();
        Framebuffer    &framebuffer    = display->getFramebuffer();

        std::size_t    threadCount     = std::max(1, this->_jobCount);

        ::omp_set_num_threads(threadCount);

        displayLibrary.pushEvent({
            .display = display.get(),
            .type    = RenderEvent::Type::RENDER_BEGIN,

            .data = {
                .render_begin = {
                    .time = std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now().time_since_epoch()),
                    .thread_count = threadCount,
                }
            }
        });

        std::size_t msaaPower = context.camera->getMSAA();

        double eventMarkerModBaseline = std::max(viewport.width(), viewport.height()) * threadCount * 0.5;

        std::size_t eventMarkerMod = eventMarkerModBaseline;
        std::size_t eventMarkerCount = viewport.width() * viewport.height() / eventMarkerModBaseline + 1;
        std::atomic<std::size_t> eventMarkerCalced = 0;

        std::mt19937 generators[threadCount];

        #pragma omp parallel for
        for (std::size_t i = 0; i < static_cast<std::size_t>(viewport.width() * viewport.height()); i++) {
            std::size_t x     = i % viewport.width();
            std::size_t y     = i / viewport.width();

            Color pixel;

            for (std::size_t subY = 0; subY < msaaPower; subY++)
                for (std::size_t subX = 0; subX < msaaPower; subX++) {
                    Ray3d subRay = context.camera->rayAt(
                        (x + (subX * 1.0 / msaaPower) - 0.5) * 1.0 / viewport.width(),
                        (y + (subY * 1.0 / msaaPower) - 0.5) * 1.0 / viewport.height()
                    );

                    pixel = pixel.blend(
                        this->query(context, subRay, generators[::omp_get_thread_num()]),
                        1.0 / (msaaPower * msaaPower)
                    );
                }

            // Write to the framebuffer
            framebuffer.access([i, pixel](Color *framebufferPtr) {
                framebufferPtr[i] = pixel;
            });

            if (i % eventMarkerMod == 0) {
                eventMarkerCalced++;

                displayLibrary.pushEvent({
                    .display = display.get(),
                    .type    = RenderEvent::Type::RENDER_PROGRESS,

                    .data = {
                        .render_progress = {
                            .progress = 1.0f * eventMarkerCalced / eventMarkerCount,
                            .sections_calculated = eventMarkerCalced,
                            .sections_total = eventMarkerCount
                        }
                    }
                });
            }
        }

        displayLibrary.pushEvent({
            .display = display.get(),
            .type    = RenderEvent::Type::RENDER_PROGRESS,

            .data = {
                .render_progress = {
                    .progress = 1.0f,
                    .sections_calculated = eventMarkerCount,
                    .sections_total = eventMarkerCount
                }
            }
        });
        displayLibrary.pushEvent({
            .display = display.get(),
            .type    = RenderEvent::Type::RENDER_END,

            .data = {
                .render_end = {
                    .time = std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now().time_since_epoch()),
                }
            }
        });
    }

    Color Scene::query(SceneContext &context, Ray3d &ray, std::mt19937 &generator)
    {
        Color                pixel;
        std::optional<Ray3d> intersect = std::nullopt;

        std::optional<TransformedPrimitive> nearestObject = std::nullopt;

        for (auto &primitive : context.primitives) {
            std::optional<Ray3d> ci = primitive.object->hits(ray, primitive.transformation);

            if (ci.has_value() && (!intersect.has_value() ||
                    std::abs((ci->getOrigin() - ray.getOrigin()).norm()) <
                    std::abs((intersect->getOrigin() - ray.getOrigin()).norm()))) {
                intersect = ci;
                Point3d intersectPoint = intersect->getOrigin();
                pixel = primitive.object->colorAt(intersectPoint);
                nearestObject = primitive;
            }
        }

        // Apply materials
        if (intersect.has_value() && nearestObject.has_value()) {
            for (auto &material : nearestObject->object->getMaterials()) {
                pixel = material->tranform(ray, intersect.value(), pixel, context);
            }
        }

        // Apply light
        if (intersect.has_value()) {
            Color  lightColor = {0.0, 0.0, 0.0};
            for (auto &light : context.lights) {
                double intensity = light.object->getIntensity(intersect.value(), context, light.transformation);
                lightColor = {
                        lightColor.r + (light.object->getColor().r * intensity),
                        lightColor.g + (light.object->getColor().g * intensity),
                        lightColor.b + (light.object->getColor().b * intensity)
                };
            }
            pixel = {pixel.r * std::clamp(lightColor.r, 0.0, 1.0),
                     pixel.g * std::clamp(lightColor.g, 0.0, 1.0),
                     pixel.b * std::clamp(lightColor.b, 0.0, 1.0)};
        }

        // Ambient occlusion
        if (intersect.has_value() && !this->_fast) {
            double occlusion = 1;
            int rays = 100;
            for (int j = 0; j < rays; j++) {
                std::uniform_real_distribution<double> distribution(0, 1);

                double theta = 2 * std::numbers::pi * distribution(generator);
                double phi = std::acos(1 - 2 * distribution(generator));
                double maxDistOcclusion = 10;

                Vector3d randomVector = {std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta), std::cos(phi)};
                Ray3d randomRay = {intersect->getOrigin(), randomVector};
                for (auto &primitive : context.primitives) {
                    std::optional<Ray3d> randomIntersect = primitive.object->hits(randomRay, primitive.transformation);
                    if (randomIntersect.has_value()) {
                        double distance = std::clamp(
                                (randomIntersect->getOrigin() - intersect->getOrigin()).norm(),
                                0.0, maxDistOcclusion);
                        occlusion -= (10 - distance) / (10 * rays);
                        break;
                    }
                }
            }
            double maxOcclusionPercentage = 1;
            occlusion = 1 - std::clamp((1 - occlusion) * maxOcclusionPercentage, 0.0, maxOcclusionPercentage);
            pixel = {pixel.r * occlusion, pixel.g * occlusion, pixel.b * occlusion};
        }

        // Apply filter
        std::for_each(context.camera->getFilters().begin(), context.camera->getFilters().end(),
            [&pixel](auto &filter) {
                pixel = filter->apply(pixel);
            });

        return pixel;
    }

    void Scene::render()
    {
        this->_transformer.process(this, &Scene::render);
    }
};
