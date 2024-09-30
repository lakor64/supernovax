add_definitions(-D_USRDLL -D_FORCENAMELESSUNION)

add_library(ddraw_enum MODULE
    ddenum.cpp
    ddenum.rc
)

set_module_type(ddraw_enum win32dll UNICODE)
add_dependencies(ddraw_enum dxsdk ddraw)
target_link_libraries(ddraw_enum cppstl atl_classes dxguid psdk)
set_target_properties(ddraw_enum PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
