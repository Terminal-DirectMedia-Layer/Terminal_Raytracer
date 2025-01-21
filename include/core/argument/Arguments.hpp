/*
** EPITECH PROJECT, 2024
** Arguments
** File description:
** file for Arguments functions
*/


#pragma once

#include <utility>

#include "Argument.hpp"
#include "core/config/RayConfig.hpp"

namespace RayTracer
{
    class Arguments
    {
    public:
        class Error : public std::exception
        {
        public:
            explicit Error(std::string message) : _message(std::move(message)) {};
            ~Error() override = default;

            [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
        };

        Arguments() = default;
        ~Arguments() = default;

        RayConfig parseArguments(int ac, char **av);

        void addArgument(const Argument &arg);
        void addArgument(const std::string &cmd, const std::string &longCmd, const std::string &description, int nbArgs,
                         const std::function<void(const std::vector<std::string> &, RayConfig &)> &callback);
    protected:
        std::vector<Argument> _arguments;
    };
} // RayTracer
