target_dx()

add_definitions(-D_UNICODE)
add_executable(dxgi_test_sa
    sasa.cpp
)

add_dependencies(dxgi_test_sa dxsdk dxgi)
target_link_libraries(dxgi_test_sa psdk dxguid cppstl)
set_module_type(dxgi_test_sa win32cui)
