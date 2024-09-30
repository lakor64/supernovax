target_dx()

add_definitions(-D_UNICODE)
add_executable(dxgi_test_gdid3dkmt
    Origine.cpp
)

add_dependencies(dxgi_test_gdid3dkmt dxsdk dxgi)
target_link_libraries(dxgi_test_gdid3dkmt psdk dxguid cppstl)
set_module_type(dxgi_test_gdid3dkmt win32cui)
