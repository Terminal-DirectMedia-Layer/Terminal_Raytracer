#pragma once

#include "core/library/DisplayLibrary.hpp"

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace RayTracer
{
    class DisplayLoader
    {
    public:
        class Error : public std::exception
        {
        public:
            explicit Error(std::string message) :
                _message(std::move(message))
            {}

            ~Error() override = default;

            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
        };

        DisplayLoader(const std::string &path = "displays") :
            _path(path)
        {}

        void load();

        void use(const std::string &name);
        DisplayLibrary & active() const;

    protected:
        std::string _path;

        using DisplayLibraryHive = std::unordered_map<std::string, std::filesystem::path>;

        DisplayLibraryHive _displayLibraries;
        std::unique_ptr<DisplayLibrary> _activeDisplayLibrary;
    };
};
