add_executable(demo
    src/main.cpp
)

target_link_libraries(demo
    engine
)

target_include_directories(demo
    PRIVATE ${CMAKE_SOURCE_DIR}
)