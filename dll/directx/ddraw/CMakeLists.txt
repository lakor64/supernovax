target_dx()
spec2def(ddraw.dll ddraw.spec ADD_IMPORTLIB)

add_definitions(-D_USRDLL)

add_library(ddraw MODULE
    directdraw.cpp
    directdraw.h
    ddrawenum.cpp
    directdrawclipper.cpp
    directdrawclipper.h
    directdrawcolorcontrol.cpp
    directdrawcolorcontrol.h
    directdrawgammacontrol.cpp
    directdrawgammacontrol.h
    directdrawpalette.cpp
    directdrawpalette.h
    directdrawsurface.cpp
    directdrawsurface.h
    directdrawvideoport.cpp
    directdrawvideoport.h
	iddvideoportcontainer.cpp
    iddvideoportcontainer.h
    dllimports.h
    dllmain.cpp
    ddraw.rc
    pch.h
    resource.h
    ${CMAKE_CURRENT_BINARY_DIR}/ddraw.def
)

set_module_type(ddraw win32dll UNICODE)
target_link_libraries(ddraw atl_classes cppstl dxutils dxguid)
set_target_properties(ddraw PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
add_pch(ddraw pch.h SOURCE)
add_dependencies(ddraw dxsdk)
