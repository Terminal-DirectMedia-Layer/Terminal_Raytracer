file(GLOB_RECURSE RAYTRACER_CORE_SOURCE_FILES ${RAYTRACER_CORE_DIR}/*.cpp)

find_library(CONFIGPP_LIBRARY config++ REQUIRED)
find_package(OpenMP REQUIRED)
find_package(PNG REQUIRED)

add_executable(raytracer
    ${RAYTRACER_INCLUDE_FILES}
    ${RAYTRACER_CORE_SOURCE_FILES}
)

target_link_libraries(raytracer
    PUBLIC 
        ${CONFIGPP_LIBRARY}
        OpenMP::OpenMP_CXX
        PNG::PNG
)
target_link_options(raytracer PRIVATE "-rdynamic")

set_target_properties(
    raytracer
    PROPERTIES
        OUTPUT_NAME "raytracer"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
