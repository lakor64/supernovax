
list(APPEND SOURCE
    system.c
    display.c
    gui.c
    sound.c
    music.c
    input.c
    network.c
    help.c
    precomp.h
    dxdiag_private.h
    information.c
    output.c
    output_txt.c
    output_xml.c
    resource.h
    main.c
)



add_rc_deps(dxdiag.rc ${CMAKE_CURRENT_SOURCE_DIR}/res/dxdiag.ico)
add_executable(dxdiag ${SOURCE} dxdiag.rc)
set_module_type(dxdiag win32gui UNICODE)
target_link_libraries(dxdiag dxguid)

if (PFF)
    target_link_libraries(dxdiag psdk msxml6 comctl32)
    add_importlibs(dxdiag fakewine)
else()
    add_importlibs(dxdiag user32 advapi32 comctl32 version winmm msvcrt kernel32 ntdll)
endif()

add_pch(dxdiag precomp.h SOURCE)
add_cd_file(TARGET dxdiag DESTINATION reactos/system32 FOR all)
