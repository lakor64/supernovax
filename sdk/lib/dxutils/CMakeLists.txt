add_library(dxutils STATIC
    helper.cpp
    whql.cpp
)
target_include_directories(dxutils PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(dxutils PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
