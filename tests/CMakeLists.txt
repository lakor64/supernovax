add_subdirectory(dxdiag)
add_subdirectory(d3dcomp)
add_subdirectory(ddraw)

if (DLL_EXPORT_VERSION GREATER_EQUAL 0x600)
    add_subdirectory(dxgi)
    add_subdirectory(d3d10)
endif()
