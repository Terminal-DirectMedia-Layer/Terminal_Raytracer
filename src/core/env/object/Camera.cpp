#include "core/env/object/Camera.hpp"

#include <numbers>

namespace RayTracer
{
    Camera::Camera(
        const std::string &name,
        const Rectangle2i &viewport,
        double fov,
        const std::vector<std::shared_ptr<IFilter>> &filters
    ) :
        _name(name),
        _viewport(viewport),
        _fov(fov),
        _filters(filters)
    {}

    Camera::Camera(const libconfig::Setting &node, const std::string &defaultName)
    {
        if (!node.lookupValue("name", this->_name))
            this->_name = defaultName;
        if (node.exists("viewport"))
            this->_viewport = Rectangle2i(node["viewport"]);
        if (!node.lookupValue("fov", this->_fov)) {
            int fovInt;
            if (node.lookupValue("fov", fovInt))
                this->_fov = fovInt;
        }
        if (!node.lookupValue("msaa", this->_msaa))
            this->_msaa = 1;

        if (node.exists("filters")) {
            libconfig::Setting &filtersSetting = node["filters"];
            const FilterFactory &_filterFactory = RT().getFilterFactory();

            for (int i = 0; i < filtersSetting.getLength(); i++) {
                std::string filterName = filtersSetting[i];
                this->_filters.push_back(
                    _filterFactory.createObject(filterName, filtersSetting[i])
                );
            }
        }
    }
    
    Ray3d Camera::rayAt(double u, double v) const
    {
        double aspectRatio = this->_viewport.width() * 1.0 / this->_viewport.height();
        double halfHeight = std::tan(this->_fov * std::numbers::pi_v<double> / 360.0);
        double halfWidth = aspectRatio * halfHeight;

        Vector3d direction(
            2.0 * halfWidth * u - halfWidth,
            2.0 * halfHeight * v - halfHeight,
            -1.0
        );

        return Ray3d({}, direction);
    }
};
