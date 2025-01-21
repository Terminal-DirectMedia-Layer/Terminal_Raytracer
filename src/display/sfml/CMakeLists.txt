find_package(SFML REQUIRED COMPONENTS system window graphics)

target_link_libraries(sfml PRIVATE sfml-graphics sfml-window sfml-system)
