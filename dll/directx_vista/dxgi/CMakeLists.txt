target_dx()

spec2def(dxgi.dll dxgi.spec ADD_IMPORTLIB)

remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x601)
add_definitions(-D_USRDLL)

add_library(dxgi MODULE
    d3dkmtstubs.cpp
    deviceptr.h
    dllmain.cpp
    dllmain.h
    dllimports.h
    dxgiadapter.cpp
    dxgiadapter.h
    dxgifactory.cpp
    dxgifactory.h
    dxgioutput.cpp
    dxgioutput.h
    dxgiswapchain.cpp
    dxgiswapchain.h
    dxgi.rc
    utils.cpp
    utils.h
    thunkloader.h
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi.def
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi_stubs.c
)

set_module_type(dxgi win32dll UNICODE)
target_link_libraries(dxgi uuid atl_classes cppstl Version dxgishared)
add_pch(dxgi pch.h SOURCE)
add_importlibs(dxgi gdi32 rpcrt4 shlwapi user32 comdlg32 msvcrt ntdll)
add_dependencies(dxgi dxsdk)
set_target_properties(dxgi PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
