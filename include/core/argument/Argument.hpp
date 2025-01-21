/*
** EPITECH PROJECT, 2024
** Argument
** File description:
** file for Argument functions
*/


#pragma once

#include <string>
#include <vector>
#include <functional>
#include "core/config/RayConfig.hpp"

namespace RayTracer
{
    class Argument
    {
    public:
        Argument(std::string cmd, std::string longCmd, std::string description, int nbArgs, std::function<void(
                const std::vector<std::string> &, RayConfig &)> callback);
        ~Argument() = default;

        void setArgs(std::vector<std::string> args);
        void addArg(const std::string& arg);
        void execute(RayConfig &cfg);

        [[nodiscard]] std::string getCmd() const;
        [[nodiscard]] std::string getLongCmd() const;
        [[nodiscard]] std::string getDescription() const;
        [[nodiscard]] int getNbArgs() const;
        [[nodiscard]] std::vector<std::string> getArgs() const;

    protected:
        std::string _cmd;
        std::string _longCmd;
        std::string _description;
        int _nbArgs;
        std::vector<std::string> _args;

        std::function<void(std::vector<std::string>, RayConfig &)> _callback;
    };
} // RayTracer
