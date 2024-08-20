include_directories(BEFORE ${CMAKE_CURRENT_LIST_DIR})

set(NORMAL_SRC
    # pff
    dxdiag.idl
    dxdiagternl.idl
    dxgidwm.idl
    dxgidwm1_2.idl
    dxgipartner.idl
    dxgiternl.idl
    dxgixaml.idl
    lockowner.idl
    usecounted.idl

    # mingw-w64
    dxgi.idl
    dxgi1_2.idl
    dxgi1_3.idl
    dxgi1_4.idl
    dxgi1_5.idl
    dxgi1_6.idl
	#d3d10.idl
	#d3d10_1.idl
	#d3d10effect.idl
	#d3d10sdklayers.idl
	#d3d10shader.idl
	#d3d11.idl
	#d3d11_1.idl
	#d3d11_2.idl
	#d3d11_3.idl
	#d3d11_4.idl
	#d3d11on12.idl

    # DX headers
    dxgicommon.idl
    dxgiformat.idl
    #d3dcommon.idl
    #d3d12.idl
    #d3d12compatibility.idl
    #d3d12sdklayers.idl
    #d3d12video.idl
)

set(IDLONLY_SRC
    dxgidebug.idl
    dxgitype.idl
)

add_idl_headers(dxsdk ${NORMAL_SRC} ${IDLONLY_SRC})
add_iid_library(dxguid ${NORMAL_SRC})
