spec2def(dxgidebug.dll dxgidebug.spec ADD_IMPORTLIB)

remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x601)
add_definitions(-D_USRDLL)

add_library(dxgidebug SHARED
    dllmain.cpp
    dxgidebug.cpp
    dxgiinfoqueue.cpp
    dxgidebug.rc
    ${CMAKE_CURRENT_BINARY_DIR}/dxgidebug.def
)

target_link_libraries(dxgidebug atl_classes uuid)
set_module_type(dxgidebug win32dll UNICODE)
add_pch(dxgidebug pch.h SOURCE)
