

spec2def(dxgi.dll dxgi.spec ADD_IMPORTLIB)

remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x601)

add_definitions(-D_USRDLL)
include_directories(BEFORE ${REACTOS_SOURCE_DIR}/win32ss_vista/include)

add_library(dxgi MODULE
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
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi.def
    ${CMAKE_CURRENT_BINARY_DIR}/dxgi_stubs.c
)

set_module_type(dxgi win32dll UNICODE)
target_link_libraries(dxgi dxguid uuid atl_classes cppstl)
add_pch(dxgi pch.h SOURCE)
add_cd_file(TARGET dxgi DESTINATION reactos/system32 FOR all)
add_importlibs(dxgi gdi32 user32 comdlg32 msvcrt ntdll)
