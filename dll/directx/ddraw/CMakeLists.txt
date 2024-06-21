spec2def(ddraw.dll ddraw.spec ADD_IMPORTLIB)

add_definitions(-D_USRDLL)

add_library(ddraw MODULE
    directdraw.cpp
    ddrawenum.cpp
    directdrawclipper.cpp
    directdrawcolorcontrol.cpp
    directdrawgammacontrol.cpp
    directdrawpalette.cpp
    directdrawsurface.cpp
    directdrawvideoport.cpp
	iddvideoportcontainer.cpp
    dllmain.cpp
    ddraw.rc
    ${CMAKE_CURRENT_BINARY_DIR}/ddraw.def
)

set_module_type(ddraw win32dll UNICODE)
target_link_libraries(ddraw ddrawhel atl_classes cppstl dxutils dxguid)
add_pch(ddraw pch.h SOURCE)
add_cd_file(TARGET ddraw DESTINATION reactos/system32 FOR all)
add_importlibs(ddraw gdi32 msvcrt)
