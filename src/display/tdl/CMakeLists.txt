include(FetchContent)

FetchContent_Declare(
    TDL
    SOURCE_DIR  "${CMAKE_SOURCE_DIR}/3rd/TDL_Terminal-DirectMedia-Library"
    BINARY_DIR  "${CMAKE_BINARY_DIR}/3rd/tdl-build"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/3rd/tdl-prefix"
)

FetchContent_MakeAvailable(TDL)
target_link_libraries(tdl PRIVATE TDL::TDL)