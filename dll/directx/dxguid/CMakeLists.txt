add_definitions(-D_MIDL_USE_GUIDDEF_)
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_idl_headers(dxguid_idl
dxgipartner.idl
dxgidwm.idl
dxdiagternl.idl
dxdiag_private.idl
usecounted.idl
lockowner.idl
dxgixaml.idl
dxgiternl.idl)

add_iid_library(dxguid_iid 
    dxdiag_private.idl
)

add_library(dxguid STATIC 
    guids.c
)

add_dependencies(dxguid dxguid_idl)
target_link_libraries(dxguid PUBLIC dxguid_iid)
target_include_directories(dxguid PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

