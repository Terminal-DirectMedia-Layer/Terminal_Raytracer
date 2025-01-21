#include "core/env/scene/SceneTransformer.hpp"
#include "core/env/scene/TransformedObject.hpp"
#include "core/env/tree/TransformNode.hpp"
#include "core/env/tree/ObjectNode.hpp"
#include "core/env/object/ILight.hpp"

#include <stack>
#include <thread>
#include <list>

namespace RayTracer
{
    SceneTransformer::SceneTransformer(std::shared_ptr<SceneNode> sceneNode) :
        _sceneNode(sceneNode)
    {}

    void SceneTransformer::process(ContextHandler &&callback)
    {
        struct Render {
            std::shared_ptr<IDisplay> display;
            SceneContext context;
        };
        std::list<Render> renders;

        std::stack<TransformedNode> stack;
        stack.emplace(Transformation3d(), _sceneNode);

        while (!stack.empty()) {
            TransformedNode node = stack.top();
            stack.pop();

            if (std::shared_ptr<ParentNode> parent = std::dynamic_pointer_cast<ParentNode>(node.object)) {
                if (std::shared_ptr<TransformNode> transformationNode = std::dynamic_pointer_cast<TransformNode>(parent))
                    node.transformation = node.transformation + transformationNode->transformation;

                for (const std::shared_ptr<Node> &child: parent->children)
                    stack.emplace(node.transformation, child);
                continue;
            }

            if (std::shared_ptr<ObjectNode> objectNode = std::dynamic_pointer_cast<ObjectNode>(node.object)) {
                if (std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(objectNode->object)) {
                    SceneContext context = {{}, {}, camera, node.transformation.inverse()};
                    fillContext(context);

                    Rectangle2i viewport = camera->getViewport();

                    renders.push_front({
                        RT().getDisplayLibrary()
                            .createDisplay(viewport.width(), viewport.height(), camera->getName()),
                        std::move(context)
                    });
                }
                continue;
            }
        }

        std::thread runner([&]() {
            for (Render &render : renders)
                callback(render.context, render.display);
        });

        {
            constexpr std::chrono::milliseconds frameTime(1000 / 30);
            
            DisplayLibrary &displayLibrary = RT().getDisplayLibrary();
            bool running = true;

            while (running) {
                displayLibrary.flushEvents();

                std::chrono::milliseconds lastFrameTime =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch());

                running = displayLibrary.update();

                std::chrono::milliseconds now =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch());
                
                if (now - lastFrameTime < frameTime)
                    std::this_thread::sleep_for(frameTime - (now - lastFrameTime));

                lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch());
            }
        }

        runner.join();
    }

    void SceneTransformer::fillContext(SceneContext &context)
    {
        std::stack<TransformedNode> stack;
        stack.emplace(context.inverseCameraTransformation, _sceneNode);

        while (!stack.empty()) {
            TransformedNode node = stack.top();
            stack.pop();
            if (std::shared_ptr<ParentNode> parent = std::dynamic_pointer_cast<ParentNode>(node.object)) {
                if (std::shared_ptr<TransformNode> transformationNode = std::dynamic_pointer_cast<TransformNode>(parent))
                    node.transformation += transformationNode->transformation;

                for (const std::shared_ptr<Node> &child: parent->children)
                    stack.emplace(node.transformation, child);
                continue;
            } else if (std::shared_ptr<ObjectNode> objectNode = std::dynamic_pointer_cast<ObjectNode>(node.object)) {
                if      (std::shared_ptr<APrimitive> primitive = std::dynamic_pointer_cast<APrimitive>(objectNode->object))
                    context.primitives.emplace_back(node.transformation, primitive);
                else if (std::shared_ptr<ILight> light = std::dynamic_pointer_cast<ILight>(objectNode->object))
                    context.lights.emplace_back(node.transformation, light);
                continue;
            }
        }
        std::sort(context.primitives.begin(), context.primitives.end(), [&](const TransformedPrimitive& p1, const TransformedPrimitive& p2) {
            return (p1.transformation.translation() - p2.transformation.translation()).norm() < 0;
        });
    }
};
