target_dx()

add_definitions(-D_UNICODE)
add_executable(dxgi_my_tests
    main.cpp
    myprivatedata.cpp
    test_adapter.cpp
    test_dxgiobject.cpp
    test_factory.cpp
    test_output.cpp
)

add_dependencies(dxgi_my_tests dxsdk dxgi)
target_link_libraries(dxgi_my_tests psdk dxguid cppstl)
set_module_type(dxgi_my_tests win32cui)
