/*
** EPITECH PROJECT, 2024
** RayConfig
** File description:
** file for RayConfig functions
*/

#include "core/config/RayConfig.hpp"
#include "core/RayTracer.hpp"

namespace RayTracer
{
    const std::string &RayConfig::pluginsPath() const
    {
        return _pluginsPath;
    }

    const std::string &RayConfig::displaysPath() const
    {
        return _displaysPath;
    }

    int RayConfig::jobCount() const
    {
        return _jobCount;
    }

    bool RayConfig::fast() const
    {
        return _fast;
    }

    const std::string &RayConfig::sceneFile() const
    {
        return _sceneFile;
    }

    const std::string &RayConfig::displayLibrary() const
    {
        return _displayLibrary;
    }

    void RayConfig::setSceneFile(const std::string &sceneFile)
    {
        if (!std::filesystem::is_regular_file(sceneFile))
            throw Error(std::format("File {} does not exist", sceneFile));

        _sceneFile = sceneFile;
    }

    void RayConfig::setDisplayLibrary(const std::string &displayLibrary)
    {
        _displayLibrary = displayLibrary;
    }

    void RayConfig::setPluginsPath(const std::string &pluginPath)
    {
        if (!std::filesystem::is_directory(pluginPath))
            throw Error(std::format("Plugins path '{}' does not exist", pluginPath));

        _pluginsPath = pluginPath;
    }

    void RayConfig::setDisplaysPath(const std::string &displaysPath)
    {
        if (!std::filesystem::is_directory(displaysPath))
            throw Error(std::format("Displays path '{}' does not exist", displaysPath));

        _displaysPath = displaysPath;
    }
    
    void RayConfig::setJobCount(int jobCount)
    {
        if (jobCount <= 0)
            throw Error("Job count must be greater than 0");

        _jobCount = jobCount;
    }

    void RayConfig::setFast(bool fast)
    {
        _fast = fast;
    }

    std::shared_ptr<SceneNode> RayConfig::loadScene()
    {
        if (_sceneFile.empty())
            throw Error("Scene file not set");

        return loadScene(_sceneFile);
    }

    std::shared_ptr<SceneNode> RayConfig::loadScene(const std::string &sceneFile)
    {
        std::shared_ptr<SceneNode> sceneNode = std::make_shared<SceneNode>();
        libconfig::Config cfg;

        try {
            cfg.readFile(sceneFile.c_str());
        } catch (const libconfig::FileIOException &e) {
            throw Error(std::format("I/O error while reading file: {}", e.what()));
        } catch (const libconfig::ParseException &e) {
            throw Error(std::format("Parse error at {}:{} - {}", e.getFile(), e.getLine(), e.getError()));
        }

        libconfig::Setting &root = cfg.getRoot();
        if (!root.exists("scene"))
            throw Error("Scene not found");
        libconfig::Setting &scene = root["scene"];
        sceneNode->children = loadNodes(scene);
        return sceneNode;
    }

    std::shared_ptr<Node> RayConfig::loadNode(libconfig::Setting &setting)
    {
        RayTracer &rayTracer = RT();

        if (!setting.exists("type"))
            throw RayConfig::Error("Node type not found");
        std::string type = setting["type"];

        if (type == "scene") {
            std::string sceneFile;
            if (!setting.lookupValue("file", sceneFile))
                throw RayConfig::Error("Scene file not found");
            return loadScene(sceneFile);
        }

        if (!setting.exists("properties"))
            throw RayConfig::Error("Node properties not found");

        
        if (type == "transform") {
            std::shared_ptr<TransformNode> transformNode = std::make_shared<TransformNode>(setting["properties"]);
            transformNode->children = loadNodes(setting["children"]);
            return transformNode;
        }
        
        std::shared_ptr<ObjectNode> objectNode = std::make_shared<ObjectNode>();
        objectNode->object = rayTracer.getObjectFactory().createObject(type, setting["properties"]);
        
        return objectNode;
    }

    std::vector<std::shared_ptr<Node>> RayConfig::loadNodes(libconfig::Setting &setting)
    {
        std::vector<std::shared_ptr<Node>> nodes;
        for (int i = 0; i < setting.getLength(); i++)
            nodes.push_back(loadNode(setting[i]));
        return nodes;
    }
} // RayTracer
