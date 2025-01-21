#pragma once

#include "core/RayTracer.hpp"

#include "core/env/object/IFilter.hpp"
#include "core/env/object/Object.hpp"

#include "core/math/Rectangle.hpp"

#include <libconfig.h++>

#include <memory>
#include <vector>

namespace RayTracer
{
    class Camera : public Object
    {
    public:
        Camera(
            const std::string &name,
            const Rectangle2i &viewport = {1920, 1080},
            double fov = 90,
            const std::vector<std::shared_ptr<IFilter>> &filters = {}
        );

        Camera(const libconfig::Setting &node, const std::string &defaultName);

        const std::string & getName() const
        {
            return this->_name;
        }

        const Rectangle2i & getViewport() const
        {
            return this->_viewport;
        }

        double getFOV() const
        {
            return this->_fov;
        }

        int getMSAA() const
        {
            return this->_msaa;
        }

        const std::vector<std::shared_ptr<IFilter>> & getFilters() const
        {
            return this->_filters;
        }

        Ray3d rayAt(double u, double v) const;

    protected:
        std::string _name;
        Rectangle2i _viewport{1920, 1080};

        double _fov;
        int _msaa;
        std::vector<std::shared_ptr<IFilter>> _filters;
    };
};
