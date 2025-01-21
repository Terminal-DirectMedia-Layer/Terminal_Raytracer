/*
** EPITECH PROJECT, 2024
** ObjectMaterialWrapper
** File description:
** file for ObjectMaterialWrapper functions
*/

#pragma once

#include "core/env/object/Object.hpp"
#include "core/env/object/IMaterial.hpp"

#include "core/factory/Factory.hpp"

#include <libconfig.h++>
#include <functional>

namespace RayTracer
{
    class ObjectPrimitiveWrapper
    {
    public:
        using FactoryWrapperBuilder = const std::function<std::shared_ptr<Object>(libconfig::Setting &, std::vector<std::shared_ptr<IMaterial>> &, std::shared_ptr<ISurface> &)>;

        static Factory<Object>::FactoryBuilder createFactory(const FactoryWrapperBuilder &primitiveFactory);
    };
} // RayTracer
