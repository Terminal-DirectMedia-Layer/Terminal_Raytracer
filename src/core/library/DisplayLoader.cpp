#include "core/library/DisplayLoader.hpp"
#include "core/library/DisplayLibrary.hpp"

namespace RayTracer
{
    void DisplayLoader::load()
    {
        if (!std::filesystem::exists(this->_path))
            throw Error(std::format("Invalid display directory path: '{}'", this->_path));

        for (const auto &entry : std::filesystem::directory_iterator(this->_path)) {
            if (!entry.is_regular_file())
                continue;
            
            std::filesystem::path libraryPath = entry.path();

            if (libraryPath.has_extension() &&
                libraryPath.extension().string() == ".so") {
                std::string libraryName = libraryPath.stem().string();

                if (libraryName.rfind("lib", 0) == 0)
                    libraryName = libraryName.substr(3);
                this->_displayLibraries.emplace(libraryName, libraryPath);
            }
        }

        if (this->_displayLibraries.empty())
            throw Error("No display libraries loaded, cannot continue");
    }

    void DisplayLoader::use(const std::string &name)
    {
        DisplayLibraryHive::iterator it = this->_displayLibraries.find(name);

        if (it == this->_displayLibraries.cend())
            throw Error(std::format("Display library '{}' does not exist", name));
        if (this->_activeDisplayLibrary)
            this->_activeDisplayLibrary.reset();
        this->_activeDisplayLibrary = std::make_unique<DisplayLibrary>(it->second);
    }

    DisplayLibrary & DisplayLoader::active() const
    {
        if (!this->_activeDisplayLibrary)
            throw Error("No active display library, cannot continue");

        return *this->_activeDisplayLibrary;
    }
};
