/*
** EPITECH PROJECT, 2024
** Factory
** File description:
** file for Factory functions
*/

#pragma once

#include "core/env/object/Object.hpp"
#include "core/env/object/IMaterial.hpp"
#include "core/env/object/ISurface.hpp"
#include "core/env/object/IFilter.hpp"

#include <map>
#include <string>
#include <functional>
#include <memory>
#include <utility>
#include <libconfig.h++>
#include <format>

namespace RayTracer
{
    template<typename T>
    class Factory
    {
    public:
        class Error : public std::exception
        {
        public:
            explicit Error(std::string message) : _message(std::move(message)) {}

            [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

        protected:
            std::string _message;
        };

        using FactoryBuilder = std::function<std::shared_ptr<T>(libconfig::Setting &setting)>;

        explicit Factory(std::string objName) :
            _objName(std::move(objName)) {};

        void registerObject(const std::string &name, FactoryBuilder object)
        {
            if (_map.contains(name))
                throw Error(std::format("{} {} already registered", _objName, name));
            _map.emplace(name, object);
        }

        void unregisterObject(const std::string &name)
        {
            if (!_map.contains(name))
                throw Error(std::format("{} {} not found", _objName, name));
            _map.erase(name);
        }

        std::shared_ptr<T> createObject(const std::string &name, libconfig::Setting &setting) const
        {
            if (!_map.contains(name))
                throw Error(std::format("{} {} not found", _objName, name));

            return _map.at(name)(setting);
        }

    protected:
        std::map<std::string, FactoryBuilder> _map;
        std::string _objName;
    };

    #define DECLARE_FACTORY(NAME, PRODUCED_TYPE, OBJECT_NAME) \
        class NAME : public Factory<PRODUCED_TYPE>            \
        {                                                     \
        public:                                               \
            NAME() :                                          \
                Factory(OBJECT_NAME)                          \
            {}                                                \
        };

    DECLARE_FACTORY(ObjectFactory, Object, "Object");
    DECLARE_FACTORY(MaterialFactory, IMaterial, "Material");
    DECLARE_FACTORY(FilterFactory, IFilter, "Filter");
    DECLARE_FACTORY(SurfaceFactory, ISurface, "Surface")

    #undef DECLARE_FACTORY
} // RayTracer
