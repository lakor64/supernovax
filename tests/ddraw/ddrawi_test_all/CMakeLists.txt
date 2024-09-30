add_definitions(-D_USRDLL -D_FORCENAMELESSUNION)

add_library(ddraw_test_all MODULE
    ddrawi_oncreate.cpp
    drawi_coop_hwnd.cpp
    main.cpp
    pch.h
    print_ddrawi.cpp
)

set_module_type(ddraw_test_all win32dll UNICODE)
add_dependencies(ddraw_test_all dxsdk ddraw)
target_link_libraries(ddraw_test_all cppstl atl_classes dxguid psdk)
set_target_properties(ddraw_test_all PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
