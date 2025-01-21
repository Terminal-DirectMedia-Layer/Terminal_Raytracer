file(
    GLOB RT_DISPLAY_DIR ${RAYTRACER_DISPLAY_DIR}/*/
    LIST_DIRECTORIES true
)

foreach(object ${RT_DISPLAY_DIR})
    if(NOT IS_DIRECTORY ${object})
        continue()
    endif()

    get_filename_component(library_name ${object} NAME_WE)
    file(
        GLOB_RECURSE library_files ${object}/*.cpp
        LIST_DIRECTORIES false
        EXCLUDE ${object}/external
    )
    list(FILTER library_files EXCLUDE REGEX "${object}/external/.*")

    add_library(${library_name} SHARED ${library_files})
    set_target_properties(
        ${library_name}
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${RAYTRACER_OUTPUT_DISPLAY_DIR}
        OUTPUT_NAME ${library_name}
    )

    message(STATUS "Adding display ${library_name} to compilation (at ${object})")
    if (EXISTS "${object}/CMakeLists.txt")
        add_subdirectory(${object})
    endif()
endforeach()
