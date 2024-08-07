## !! pff exclusive module !!

if (WIN32)
  # cmake has CMAKE_RC_COMPILER, but no message compiler
  if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
    set(SYS_CRT_ROOT "$ENV{ProgramFiles\(x86\)}/Windows Kits")
    if ("${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" MATCHES "10")
        set(SYS_CRT_ROOT "${SYS_CRT_ROOT}/10/")
        set(MATCH_SDK10 TRUE)
    endif()

    set(MC_ROOT "${SYS_CRT_ROOT}/bin/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}/${ARCH}")
  endif()
  find_program(CMAKE_MC_COMPILER mc.exe HINTS "${MC_ROOT}")
  if(NOT CMAKE_MC_COMPILER)
    message(FATAL_ERROR "Message compiler not found")
  endif()
  message(STATUS "Found message compiler: ${CMAKE_MC_COMPILER}")
  mark_as_advanced(CMAKE_MC_COMPILER)
endif()

function(add_cd_file)
# no cd out, this is not reactos!!
endfunction()

function(get_vs_path)
    find_program(_vswhere_tool 
    NAMES vswhere 
    PATHS "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/Installer")
    if (NOT ${vswhere})
    message(FATAL_ERROR "Could not locate vswhere.exe - unable to source vc redistributable")
    endif()

    execute_process(
    COMMAND "${_vswhere_tool}" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    OUTPUT_VARIABLE _vs_install_loc_out
    RESULT_VARIABLE _vs_where_exitcode
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    file(TO_CMAKE_PATH "${_vs_install_loc_out}" _vs_install_loc)
    set(VS_INST_PATH "${_vs_install_loc}" PARENT_SCOPE)
endfunction()

function(get_vs_crt_path)
    get_vs_path()
    
    message(STATUS "MSVC version: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
    message(STATUS "VS install path: ${VS_INST_PATH}")
    message(STATUS "MSVC toolchain: ${CMAKE_VS_PLATFORM_TOOLSET}")
    
    set(VS_AUX_CFG "${VS_INST_PATH}/VC/Auxiliary/Build/Microsoft.VCToolsVersion.${CMAKE_VS_PLATFORM_TOOLSET}.default.txt")
    if (NOT EXISTS "${VS_AUX_CFG}")
        message(FATAL_ERROR "Cannot find configuration file ${VS_AUX_CFG}")
    endif()

    file(READ "${VS_AUX_CFG}" VS_CRT_VERSION)
    string(STRIP "${VS_CRT_VERSION}" VS_CRT_VERSION)

    set(VS_CRT_ROOT "${VS_INST_PATH}/VC/Tools/MSVC/${VS_CRT_VERSION}")
    set(VS_CRT_INC "${VS_CRT_ROOT}/include" PARENT_SCOPE)
    set(VS_CRT_LIBDIR "${VS_CRT_ROOT}/lib/${ARCH}" PARENT_SCOPE)
endfunction()

function(get_winsdk)
    set(SYS_CRT_ROOT "$ENV{ProgramFiles\(x86\)}/Windows Kits")
    if ("${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" MATCHES "10")
        set(SYS_CRT_ROOT "${SYS_CRT_ROOT}/10/")
        set(MATCH_SDK10 TRUE)
    endif()

    set(WINSDK_ROOT "${SYS_CRT_ROOT}")

endfunction()

function(get_system_includes)
    if (NOT MSVC)
        message(FATAL_ERROR "idk??")
    endif()

    get_vs_crt_path()



    if (MATCH_SDK10)
        set(SYS_CRT_INC_ROOT "${SYS_CRT_ROOT}/Include/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
        set(SYS_CRT_INC "${SYS_CRT_INC_ROOT}/ucrt;${SYS_CRT_INC_ROOT}/shared;${SYS_CRT_INC_ROOT}/um;${VS_CRT_INC}" PARENT_SCOPE)
        set(SYS_CRT_LIB_ROOT "${SYS_CRT_ROOT}/Lib/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}/${ARCH}")
        set(SYS_CRT_LIBDIR "${SYS_CRT_LIB_ROOT}/um;${SYS_CRT_LIB_ROOT}/ucrt;${VS_CRT_LIBDIR}" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Unsupported SDK: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
    endif()
endfunction()

function(get_host_includes)
    if (NOT WIN32 OR NOT MSVC)
        message(FATAL_ERROR "idk!!!")
    endif()

    set(HOST_CRT_INC "${SYS_CRT_INC}" PARENT_SCOPE)
    set(HOST_CRT_LIBDIR "${SYS_CRT_LIBDIR}" PARENT_SCOPE)
    set(HOST_STANDARD_LIBRARIES 
        # win32
        kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
        # msvc /mt
        libvcruntime.lib libucrt.lib libcmt.lib libcpmt.lib
    PARENT_SCOPE)

    # /MD
    #set(HOST_STANDARD_LIBRARIES_DEBUG vcruntimed.lib ucrtd.lib msvcrtd.lib msvcprtd.lib PARENT_SCOPE)
    #set(HOST_STANDARD_LIBRARIES_RELEASE vcruntime.lib ucrt.lib msvcrt.lib msvcprt.lib PARENT_SCOPE)
endfunction()


function(add_host_tool MODNAME SRC)
    add_executable(${MODNAME} ${SRC})
    set_module_type(${MODNAME} win32cui)
    # host deps on host tool
    target_link_directories(${MODNAME} PRIVATE ${HOST_CRT_LIBDIR})
    target_include_directories(${MODNAME} PRIVATE ${HOST_CRT_INC})
    target_link_libraries(${MODNAME} PRIVATE 
        ${HOST_STANDARD_LIBRARIES}
        #debug ${HOST_STANDARD_LIBRARIES_DEBUG}
        #optimized ${HOST_STANDARD_LIBRARIES_RELEASE}
    )
    target_compile_definitions(${MODNAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
    set_target_properties(${MODNAME} PROPERTIES
        OUTPUT_NAME "${MODNAME}"
        RUNTIME_OUTPUT_DIRECTORY "${HOST_OUT_PATH}"
    )
endfunction()

function(add_fake_targets)
    add_library(psdk INTERFACE)
    target_link_directories(psdk INTERFACE ${SYS_CRT_LIBDIR})
    target_include_directories(psdk INTERFACE ${SYS_CRT_INC})
    target_compile_definitions(psdk INTERFACE -D_CRT_SECURE_NO_WARNINGS)
    target_link_libraries(psdk INTERFACE
        #debug vcruntimed.lib ucrtd.lib msvcrtd.lib
        #release vcruntime.lib ucrt.lib msvcrt.lib
        libcmt.lib libvcruntime.lib libucrt.lib
    )

    add_library(xdk ALIAS psdk)
    add_library(dxsdk ALIAS psdk)
endfunction()

function(get_native_tool_path file)
    set(NATIVE_TOOL_EXE "cmake" -D TARGET_FILE=${file} -D HOST_OUT_PATH="${HOST_OUT_PATH}" -P "${REACTOS_SOURCE_DIR}/sdk/cmake/run_host.cmake" -- PARENT_SCOPE)
endfunction()
