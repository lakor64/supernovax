

spec2def(dxgi.dll dxgi.spec ADD_IMPORTLIB)

remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x601)

add_definitions(-D_USRDLL)
include_directories(BEFORE ${REACTOS_SOURCE_DIR}/win32ss_vista/include)

add_library(dxgi MODULE
    d3dkmtstubs.cpp
    dllmain.cpp
    dxgiadapter.cpp
    dxgidevice.cpp
    dxgifactory.cpp
    dxgikeyedmutex.cpp
    dxgioutput.cpp
    dxgiresource.cpp
    dxgisurface.cpp
    dxgiswapchain.cpp
    dxgi.rc
    guids.cpp
    utils.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi.def
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi_stubs.c
)

set_module_type(dxgi win32dll UNICODE)
target_link_libraries(dxgi dxguid uuid atl_classes cppstl Version)
add_pch(dxgi pch.h SOURCE)
add_importlibs(dxgi gdi32 rpcrt4 shlwapi user32 comdlg32 msvcrt ntdll)
