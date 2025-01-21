/*
** EPITECH PROJECT, 2024
** Argument
** File description:
** file for Argument functions
*/

#include "core/argument/Argument.hpp"

#include <utility>

namespace RayTracer
{
    Argument::Argument(std::string cmd, std::string longCmd, std::string description, int nbArgs, std::function<void(
            const std::vector<std::string> &, RayConfig &)> callback)
        : _cmd(std::move(cmd)), _longCmd(std::move(longCmd)), _description(std::move(description)), _nbArgs(nbArgs),
        _callback(std::move(callback)) {}

    void Argument::setArgs(std::vector<std::string> args)
    {
        _args = std::move(args);
    }

    void Argument::addArg(const std::string& arg)
    {
        _args.push_back(arg);
    }

    void Argument::execute(RayConfig &cfg)
    {
        _callback(_args, cfg);
    }

    std::string Argument::getCmd() const
    {
        return _cmd;
    }

    std::string Argument::getLongCmd() const
    {
        return _longCmd;
    }

    std::string Argument::getDescription() const
    {
        return _description;
    }

    int Argument::getNbArgs() const
    {
        return _nbArgs;
    }

    std::vector<std::string> Argument::getArgs() const
    {
        return _args;
    }
} // RayTracer