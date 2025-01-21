/*
** EPITECH PROJECT, 2024
** Arguments
** File description:
** file for Arguments functions
*/

#include <iostream>
#include <format>
#include <sstream>
#include "core/argument/Arguments.hpp"

namespace RayTracer
{
    RayConfig Arguments::parseArguments(int ac, char **av)
    {
        if (ac == 1)
            throw Error("Invalid count of argument. Use -h for help.");
        Argument help = Argument("-h", "--help", "This help message.", 1, [this](const std::vector<std::string> &args, RayConfig &cfg) {
            std::cout << "USAGE:" << std::endl;
            std::cout << "\t./raytracer [OPTIONS] <SCENE_FILE>" << std::endl;
            std::cout << "OPTIONS:" << std::endl;
            for (auto &arg : _arguments) {
                std::stringstream ss(arg.getCmd());
                ss << std::format("{:<2}", arg.getCmd());
                if (!arg.getLongCmd().empty())
                    ss << ", " << std::format("{:<20}", arg.getLongCmd());
                std::cout << "\t" << ss.str() << arg.getDescription() << std::endl;
            }
            std::cout << "DESCRIPTION:" << std::endl;
            std::cout << "\tRaytracer is a program that generates images using ray-casting." << std::endl;
            exit(0);
        });
        _arguments.push_back(help);
        RayConfig cfg;
        if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help"))
            help.execute(cfg);
        cfg.setSceneFile(av[ac - 1]);
        for (int i = 1; i < ac - 1; i++) {
            bool found = false;
            for (auto &arg : _arguments) {
                if (arg.getCmd() != av[i] && arg.getLongCmd() != av[i])
                    continue;
                std::vector<std::string> args;
                if (ac < i + arg.getNbArgs() + 1)
                    throw Error("Invalid count of argument for " + arg.getCmd());
                for (int j = 0; j < arg.getNbArgs(); j++)
                    args.emplace_back(av[i + j + 1]);
                i += arg.getNbArgs();
                arg.setArgs(args);
                arg.execute(cfg);
                found = true;
            }
            if (!found)
                throw Error("Unknown argument: " + std::string(av[i]));
        }
        return cfg;
    }

    void Arguments::addArgument(const Argument &arg)
    {
        _arguments.push_back(arg);
    }

    void Arguments::addArgument(const std::string &cmd, const std::string &longCmd, const std::string &description, int nbArgs,
                                const std::function<void(const std::vector<std::string> &, RayConfig &)> &callback)
    {
        _arguments.emplace_back(cmd, longCmd, description, nbArgs, callback);
    }
} // RayTracer
