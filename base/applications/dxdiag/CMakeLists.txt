target_dx()

set(GUI_SRC
    gui/display.c
    gui/gui.c
    gui/help.c
    gui/input.c
    gui/music.c
    gui/network.c
    gui/sound.c
    gui/system.c
    gui/gui.h
)

set(INFO_SRC
    info/info_display.c
    info/info_system.c
    info/information.c
    info/information.h
)

set(XML_SRC
    xml/output_xml.c
    xml/output_xml.h
    xml/xml_display.c
    xml/xml_system.c
    xml/xml_files.c
    xml/xml_input.c
    xml/xml_music.c
    xml/xml_sound.c
    xml/xml_network.c
    xml/xml_video.c
    xml/xml_notes.c
    xml/xml_debug.c
    xml/xml_sysdev.c
    xml/xml_logical.c
)

set(TXT_SRC
    txt/output_txt.c
)

list(APPEND SOURCE
    precomp.h
    dxdiag_private.h
    resource.h
    main.c
    output.c
    output.h
)

source_group("info" FILES ${INFO_SRC})
source_group("txt" FILES ${TXT_SRC})
source_group("xml" FILES ${XML_SRC})
source_group("gui" FILES ${GUI_SRC})

add_rc_deps(dxdiag.rc ${CMAKE_CURRENT_SOURCE_DIR}/res/dxdiag.ico)
add_executable(dxdiag ${SOURCE} ${GUI_SRC} ${XML_SRC} ${TXT_SRC} ${INFO_SRC} dxdiag.rc)
set_module_type(dxdiag win32gui UNICODE)
target_link_libraries(dxdiag dxguid psdk msxml6 comctl32)
add_importlibs(dxdiag fakewine)
add_dependencies(dxdiag dxsdk)
add_pch(dxdiag precomp.h SOURCE)
