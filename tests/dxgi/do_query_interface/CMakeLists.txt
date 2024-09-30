target_dx()

add_definitions(-D_UNICODE)
add_executable(dxgi_test_queryinterface
    Origine.cpp
)

add_dependencies(dxgi_test_queryinterface dxsdk dxgi)
target_link_libraries(dxgi_test_queryinterface psdk dxguid cppstl)
set_module_type(dxgi_test_queryinterface win32cui)
