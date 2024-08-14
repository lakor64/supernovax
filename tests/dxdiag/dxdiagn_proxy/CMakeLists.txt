spec2def(dxdiagn_proxy.dll dxdiagn.spec ADD_IMPORTLIB)

add_definitions(-D_USRDLL -D_FORCENAMELESSUNION)

add_library(dxdiagn_proxy MODULE
    proxy.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/dxdiagn_proxy.def
)

set_module_type(dxdiagn_proxy win32dll UNICODE)
target_link_libraries(dxdiagn_proxy cppstl atl_classes dxguid dxsdk psdk)
set_target_properties(dxdiagn_proxy PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
