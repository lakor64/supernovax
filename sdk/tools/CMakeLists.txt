add_subdirectory(hpp)
add_subdirectory(utf16le)
add_subdirectory(spec2def)

if (NOT MSVC)
    add_subdirectory(widl) # oh god please no I don't want bisonflex those programs should be destroyed
endif()
