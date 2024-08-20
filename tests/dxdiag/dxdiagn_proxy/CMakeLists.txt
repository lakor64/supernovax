spec2def(dxdiagn_proxy.dll dxdiagn.spec ADD_IMPORTLIB)

add_definitions(-D_USRDLL -D_FORCENAMELESSUNION)

add_library(dxdiagn_proxy MODULE
    proxy.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/dxdiagn_proxy.def
)

add_idl_headers(dxdiagn_proxy_idl proxy.idl)
add_iid_library(dxdiagn_proxy_iid proxy.idl)

set_module_type(dxdiagn_proxy win32dll UNICODE)
add_dependencies(dxdiagn_proxy dxdiagn_proxy_idl dxsdk)
target_link_libraries(dxdiagn_proxy dxdiagn_proxy_iid cppstl atl_classes dxguid psdk)
set_target_properties(dxdiagn_proxy PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
