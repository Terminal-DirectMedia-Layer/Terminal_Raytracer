#include "core/argument/Arguments.hpp"

#include "core/env/scene/Scene.hpp"

#include "core/config/RayConfig.hpp"

#include <string>
#include <vector>
#include <iostream>

#include <cstdlib>

namespace RayTracer
{
    static Arguments initArgs()
    {
        Arguments args;

        args.addArgument("-P", "--plugins-path", "Set the plugins' path", 1,
            [](const std::vector<std::string> &args, RayConfig &cfg) {
                cfg.setPluginsPath(args[0]);
            });
        args.addArgument("-D", "--displays-path", "Set the displays' path", 1,
            [](const std::vector<std::string> &args, RayConfig &cfg) {
                cfg.setDisplaysPath(args[0]);
            });
        args.addArgument("-d", "--display-library", "Set the display library", 1,
            [](const std::vector<std::string> &args, RayConfig &cfg) {
                cfg.setDisplayLibrary(args[0]);
            });
        args.addArgument("-j", "--job-count", "Set the number of jobs/threads to use", 1,
            [](const std::vector<std::string> &args, RayConfig &cfg) {
                int jobCount = std::stoi(args[0]);

                if (jobCount <= 0)
                    throw Arguments::Error("Job count must be greater than 0");

                cfg.setJobCount(jobCount);
            });
        args.addArgument("-f", "--fast", "Enable fast mode", 0,
            [](const std::vector<std::string> &args, RayConfig &cfg) {
                cfg.setFast(true);
            });

        return args;
    }
};

int main(int argc, char *argv[])
{
    RayTracer::RayTracer &rt = RayTracer::RT();
    
    rt.load();

    try {
        RayTracer::Arguments args = RayTracer::initArgs();
        RayTracer::RayConfig config = args.parseArguments(argc, argv);

        if (!config.displayLibrary().empty())
            rt.setDisplayLibrary(config.displayLibrary());

        std::shared_ptr<RayTracer::SceneNode> sceneNode = config.loadScene();
        RayTracer::Scene scene(sceneNode, config.jobCount(), config.fast());

        scene.render();
    } catch (const RayTracer::Arguments::Error &ex) {
        std::cerr << ex.what() << std::endl;
        return 84;
    } catch (const RayTracer::RayConfig::Error &ex) {
        std::cerr << ex.what() << std::endl;
        return 84;
    } catch (const RayTracer::Factory<RayTracer::Object>::Error &ex) {
        std::cerr << ex.what() << std::endl;
        return 84;
    }

    return EXIT_SUCCESS;
}
