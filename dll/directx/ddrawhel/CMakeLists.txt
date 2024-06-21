add_library(ddrawhel STATIC
    ddrawhel.cpp
    helcallbacks.cpp
)
add_dependencies(ddrawhel psdk)
target_compile_definitions(ddrawhel PRIVATE UNICODE _UNICODE)

