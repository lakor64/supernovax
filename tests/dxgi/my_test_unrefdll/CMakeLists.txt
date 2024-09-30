target_dx()

add_definitions(-D_UNICODE)
add_executable(dxgi_test_unrefdll
    main.cpp
)

add_dependencies(dxgi_test_unrefdll dxsdk dxgi)
target_link_libraries(dxgi_test_unrefdll psdk dxguid cppstl)
set_module_type(dxgi_test_unrefdll win32cui)
