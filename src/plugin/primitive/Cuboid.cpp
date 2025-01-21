/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Cuboid.cpp
*/

#include "plugin/primitive/Cuboid.hpp"
#include <algorithm>

namespace RayTracer {

    Cuboid::Cuboid(Vector3d dimensions, std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface) : dimensions(dimensions), APrimitive(materials, surface) {
        //seting up points
        points[0] = Vector3d(-0.5, -0.5, -0.5);
        points[1] = Vector3d(0.5, -0.5, -0.5);
        points[2] = Vector3d(0.5, 0.5, -0.5);
        points[3] = Vector3d(-0.5, 0.5, -0.5);
        points[4] = Vector3d(-0.5, -0.5, 0.5);
        points[5] = Vector3d(0.5, -0.5, 0.5);
        points[6] = Vector3d(0.5, 0.5, 0.5);
        points[7] = Vector3d(-0.5, 0.5, 0.5);
        
        //seting up faces
        faces[0] = std::make_tuple(points[0], points[1], points[2], points[3]); // front
        faces[1] = std::make_tuple(points[4], points[5], points[6], points[7]); // back
        faces[2] = std::make_tuple(points[0], points[1], points[5], points[4]); // top
        faces[3] = std::make_tuple(points[1], points[2], points[6], points[5]); // right
        faces[4] = std::make_tuple(points[2], points[3], points[7], points[6]); // bottom
        faces[5] = std::make_tuple(points[3], points[0], points[4], points[7]); // left
        isSetup = false;
    }

    Vector3d Cuboid::normalFace(Face face) {
        Point3d p1 = std::get<0>(face);
        Point3d p2 = std::get<1>(face);
        Point3d p3 = std::get<2>(face);
        Vector3d v1 = p2 - p1;
        Vector3d v2 = p3 - p1;
        Vector3d normal = v1.cross(v2);
        return normal.normalize();
    }

    std::optional<Vector3d> getIntersection(Ray3d &ray, Vector3d point, Vector3d normal) {
        Point3d rayOrigin = ray.getOrigin();
        Vector3d direction = ray.getDirection().normalize();
        if (direction.dot(normal) == 0)
            return std::nullopt;
        double t = -(point - rayOrigin).dot(normal) / direction.dot(normal);
        if (t <= 0)
            return std::nullopt;
        return rayOrigin + direction * -t;
    }

    /* void Cuboid::setupPoints(Transformation3d &trans) {
        dimensions = trans.scale() * dimensions;
        for (int i = 0; i < 8; i++) {
            points[i].x() *= dimensions.x();
            points[i].y() *= dimensions.y();
            points[i].z() *= dimensions.z();
            points[i] = trans.rotationMatrix() * points[i];
            points[i] = trans.translationMatrix() * points[i];
            if (points[i].x() < minX)
                minX = points[i].x();
            if (points[i].y() < minY)
                minY = points[i].y();
            if (points[i].z() < minZ)
                minZ = points[i].z();
            if (points[i].x() > maxX)
                maxX = points[i].x();
            if (points[i].y() > maxY)
                maxY = points[i].y();
            if (points[i].z() > maxZ)
                maxZ = points[i].z();
        }
        faces[0] = std::make_tuple(points[0], points[1], points[2], points[3]); // front
        faces[1] = std::make_tuple(points[4], points[5], points[6], points[7]); // back
        faces[2] = std::make_tuple(points[0], points[1], points[5], points[4]); // top
        faces[3] = std::make_tuple(points[1], points[2], points[6], points[5]); // right
        faces[4] = std::make_tuple(points[2], points[3], points[7], points[6]); // bottom
        faces[5] = std::make_tuple(points[3], points[0], points[4], points[7]); // left
    } */

    std::optional<Ray3d> Cuboid::hits(Ray3d &ray, Transformation3d &trans)
    {
        std::vector<std::tuple<double, Point3d, Face>> intersections; // distance, point
        std::array<Point3d, 8> newPoints;
        Vector3d newDimensions = trans.scale() * dimensions;
        float minX = INFINITY;
        float minY = INFINITY;
        float minZ = INFINITY;
        float maxX = -INFINITY;
        float maxY = -INFINITY;
        float maxZ = -INFINITY;
        for (int i = 0; i < 8; i++) {
            newPoints[i] = points[i];
            newPoints[i].x() *= newDimensions.x();
            newPoints[i].y() *= newDimensions.y();
            newPoints[i].z() *= newDimensions.z();
            newPoints[i] = trans.rotationMatrix() * newPoints[i];
            newPoints[i] = trans.translationMatrix() * newPoints[i];
            if (newPoints[i].x() < minX)
                minX = newPoints[i].x();
            if (newPoints[i].y() < minY)
                minY = newPoints[i].y();
            if (newPoints[i].z() < minZ)
                minZ = newPoints[i].z();
            if (newPoints[i].x() > maxX)
                maxX = newPoints[i].x();
            if (newPoints[i].y() > maxY)
                maxY = newPoints[i].y();
            if (newPoints[i].z() > maxZ)
                maxZ = newPoints[i].z();
        }
        for (int i = 0; i < 6; i++) {
            Vector3d normal = normalFace(faces[i]);
            Point3d p1 = std::get<0>(faces[i]);
            p1.x() *= newDimensions.x();
            p1.y() *= newDimensions.y();
            p1.z() *= newDimensions.z();
            p1 = trans.rotationMatrix() * p1;
            p1 = trans.translationMatrix() * p1;
            std::optional<Point3d> intersection = getIntersection(ray, p1, normal);
            if (intersection.has_value()) {
                Point3d point = intersection.value();
                if (point.x() >= minX && point.x() <= maxX&& point.y() >= minY && point.y() <= maxY && point.z() >= minZ && point.z() <= maxZ) {
                    double distance = point.distanceFrom(ray.getOrigin());
                    intersections.push_back(std::make_tuple(distance, point, faces[i]));
                }
            }
        }
        if (intersections.size() == 0)
            return std::nullopt;
        std::sort(intersections.begin(), intersections.end(), [](std::tuple<double, Point3d, Face> a, std::tuple<double, Point3d, Face> b) {
            return std::get<0>(a) < std::get<0>(b);
        });
        Vector3d resVect;
        Vector3d normal = normalFace(std::get<2>(intersections[0]));
        Ray3d resRay(std::get<1>(intersections[0]), normal);
        return resRay;
    }

    Color Cuboid::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Cuboid::getNormal(Point3d &intersect)
    {
        return (intersect);
    }
}