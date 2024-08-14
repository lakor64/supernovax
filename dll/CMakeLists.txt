if (PFF)
    add_subdirectory(fakewine)
endif()

add_subdirectory(directx)

if (DLL_EXPORT_VERSION GREATER_EQUAL 0x600)
    add_subdirectory(directx_vista)
endif()
