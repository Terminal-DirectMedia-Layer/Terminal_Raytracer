/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** file for DLLoader functions
*/


#pragma once

#include <string>

#include <dlfcn.h>

namespace RayTracer
{
    class DLLoader
    {
    public:
        class Error : public std::exception
        {
        public:
            explicit Error(const std::string &error)
            {
                _error = error;
            }

            [[nodiscard]] const char *what() const noexcept override
            {
                return _error.c_str();
            }

        private:
            std::string _error;
        };

        explicit DLLoader(const std::string &path) : _path(path)
        {
            _handle = ::dlopen(path.c_str(), RTLD_LAZY);

            if (!_handle)
                throw Error(::dlerror());
        }

        DLLoader(const DLLoader &) = default;
        DLLoader(DLLoader &&) = default;

        DLLoader &operator=(const DLLoader &) = default;
        DLLoader &operator=(DLLoader &&) = default;

        ~DLLoader()
        {
            ::dlclose(_handle);
        }

        template<typename F>
        F getMethod(const std::string &method)
        {
            auto constructor = F(::dlsym(_handle, method.c_str()));

            if (!constructor)
                throw Error(::dlerror());

            return constructor;
        }

    private:
        std::string _path;
        void *_handle = nullptr;
    };
} // RayTracer
