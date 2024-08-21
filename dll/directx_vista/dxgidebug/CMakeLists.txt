spec2def(dxgidebug.dll dxgidebug.spec ADD_IMPORTLIB)
target_dx()

remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x601)
add_definitions(-D_USRDLL)

add_library(dxgidebug SHARED
    dllmain.cpp
    dxgidebug.cpp
    dxgidebug.h
    dxgiinfoqueue.cpp
    dxgiinfoqueue.h
    pch.h
    dxgidebug.rc
    ${CMAKE_CURRENT_BINARY_DIR}/dxgidebug.def
)

target_link_libraries(dxgidebug atl_classes uuid dxgishared)
set_module_type(dxgidebug win32dll UNICODE)
add_pch(dxgidebug pch.h SOURCE)
set_target_properties(dxgidebug PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
