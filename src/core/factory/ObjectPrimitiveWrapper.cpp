/*
** EPITECH PROJECT, 2024
** ObjectMaterialWrapper
** File description:
** file for ObjectMaterialWrapper functions
*/

#include "core/factory/ObjectPrimitiveWrapper.hpp"
#include "core/RayTracer.hpp"

#include "core/env/object/Object.hpp"
#include <memory>

namespace RayTracer
{
    Factory<Object>::FactoryBuilder ObjectPrimitiveWrapper::createFactory(const FactoryWrapperBuilder &primitiveFactory)
    {
        return [primitiveFactory](libconfig::Setting &setting) -> std::shared_ptr<Object> {
            RayTracer &rayTracer = RT();
            std::vector<std::shared_ptr<IMaterial>> materials;

            if (setting.exists("materials")) {
                libconfig::Setting &materialsSetting = setting["materials"];
                for (int i = 0; i < materialsSetting.getLength(); i++) {
                    libconfig::Setting &materialSetting = materialsSetting[i];
                    std::string materialName;
                    if (!materialSetting.lookupValue("type", materialName))
                        throw Factory<Object>::Error("Material type not found");
                    try {
                        materials.push_back(rayTracer.getMaterialFactory().
                                createObject(materialName, materialSetting.exists("properties") ?
                                                           materialSetting["properties"] : materialSetting));
                    } catch (Factory<IMaterial>::Error &e) {
                        throw Factory<Object>::Error(e.what());
                    }
                }
            }
            std::string surfaceData;
            if (!setting.exists("surface"))
                throw Factory<Object>::Error("Surface not found");
            libconfig::Setting &surfaceSetting = setting["surface"];
            if (!surfaceSetting.lookupValue("type", surfaceData))
                throw Factory<Object>::Error("Surface type not found");
            std::shared_ptr<ISurface> surface;
            try {
                surface = rayTracer.getSurfaceFactory().createObject(surfaceData,
                            surfaceSetting.exists("properties") ?
                            surfaceSetting["properties"] : surfaceSetting);
            } catch (Factory<ISurface>::Error &e) {
                throw Factory<Object>::Error(e.what());
            }
            return primitiveFactory(setting, materials, surface);
        };
    }
} // RayTracer
