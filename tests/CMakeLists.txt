add_subdirectory(dxdiag)
add_subdirectory(d3dcomp)

if (DLL_EXPORT_VERSION GREATER_EQUAL 0x600)
    add_subdirectory(dxgi)
endif()
