## !! pff exclusive module !!
#
# SYS_VISUALSTUDIO_PATH: Visual Studio installation directory
# SYS_WINDOWSDK_VERSION: Windows SDK real version
# SYS_MSVC_TOOLCHAIN: Real MSVC toolchain (without _xp)
# SYS_IS_XP: True if the target is XP
# SYS_IS_PSDK_V10: True if the target uses SDK 10+
# SYS_MSVC_CRT_ROOT: MSVC CRT root dir
# SYS_MSVC_CRT_INC: MSVC CRT include dir
# SYS_MSVC_CRT_LIBDIR: MSVC CRT lib dir
# SYS_PSDK_ROOT: Windows SDK root
# SYS_PSDK_INC: Platform SDK include dir
# SYS_PSDK_LIBDIR: Platform SDK library dir
# SYS_PSDK_BINDIR: Platform SDK binary dir
# SYS_PSDK_TARGET: Platform SDK target
# SYS_DXSDK_ROOT: DX SDK root
# SYS_DXSDK_NEEDED: Requires an external DX SDK
# CMAKE_VS_PLATFORM_TOOLSET: MSVC toolchain
# CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION: Windows SDK version from cmake
#

if (NOT WIN32 OR NOT MSVC)
    message(FATAL_ERROR "Platform not supported by fakeros!")
endif()

# VisualStudio bootstrap
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
set(SYS_VISUALSTUDIO_PATH "${_vs_install_loc}" CACHE STRING "Visual Studio directory" FORCE)
mark_as_advanced(SYS_VISUALSTUDIO_PATH)

# Toolchain setup for xp
string(FIND "${CMAKE_VS_PLATFORM_TOOLSET}" "_xp" HAVE_XP)
if (NOT "${HAVE_XP}" STREQUAL "-1")
    string(SUBSTRING "${CMAKE_VS_PLATFORM_TOOLSET}" 0 ${HAVE_XP} MY_VS_TOOLSET)
    set(SYS_IS_XP TRUE CACHE BOOL "XP toolchain option")
else()
    set(MY_VS_TOOLSET "${CMAKE_VS_PLATFORM_TOOLSET}")
    set(SYS_IS_XP 0 CACHE BOOL "XP toolchain option")
endif()
mark_as_advanced(SYS_IS_XP)

set(SYS_MSVC_TOOLCHAIN "${MY_VS_TOOLSET}" CACHE STRING "MSVC toolchain" FORCE)
mark_as_advanced(SYS_MSVC_TOOLCHAIN)

set(VS_AUX_CFG "${SYS_VISUALSTUDIO_PATH}/VC/Auxiliary/Build/Microsoft.VCToolsVersion.${MY_VS_TOOLSET}.default.txt")
if (NOT EXISTS "${VS_AUX_CFG}")
    message(FATAL_ERROR "Cannot find configuration file ${VS_AUX_CFG}")
endif()

# MSVC CRT bootstrap
file(READ "${VS_AUX_CFG}" VS_CRT_VERSION)
string(STRIP "${VS_CRT_VERSION}" VS_CRT_VERSION)

set(SYS_MSVC_CRT_ROOT "${SYS_VISUALSTUDIO_PATH}/VC/Tools/MSVC/${VS_CRT_VERSION}" CACHE STRING "MSVC CRT root directory" FORCE)
mark_as_advanced(SYS_MSVC_CRT_ROOT)

if (NOT EXISTS "${SYS_MSVC_CRT_ROOT}")
    message(FATAL_ERROR "Cannot find MSVC CRT root directory")
endif()

set(SYS_MSVC_CRT_INC "${SYS_MSVC_CRT_ROOT}/include" CACHE STRING "MSVC CRT includes directory" FORCE)
mark_as_advanced(SYS_MSVC_CRT_INC)
set(SYS_MSVC_CRT_LIBDIR "${SYS_MSVC_CRT_ROOT}/lib/${WINARCH}" CACHE STRING "MSVC CRT library directory" FORCE)
mark_as_advanced(SYS_MSVC_CRT_LIBDIR)

if (NOT EXISTS "${SYS_MSVC_CRT_ROOT}/atlmfc")
    message(FATAL_ERROR "ATL/MFC not installed for this toolchain")
endif()

# Windows PSDK bootstrap

set(SYS_PSDK_ROOT "$ENV{ProgramFiles\(x86\)}/Windows Kits")
set(SYS_DXSDK_NEEDED 0 CACHE BOOL "Need separate DX SDK" FORCE)

if (SYS_IS_XP)
    # you need corecrt v10 for proper compile with v141_xp
    set(SYS_PSDK_ROOT_10 "${SYS_PSDK_ROOT}/10")
    # set real psdk root
    set(SYS_PSDK_ROOT "$ENV{ProgramFiles\(x86\)}/Microsoft SDKs/Windows/v7.1A")
    set(SYS_IS_PSDK_V10 0 CACHE BOOL "Platform SDK for NT10+" FORCE)

    if (NOT EXISTS "${SYS_PSDK_ROOT_10}")
        message(FATAL_ERROR "Cannot find Platform SDK for Windows 10")
    endif()

    set(SYS_DXSDK_NEEDED TRUE CACHE BOOL "Need separate DX SDK" FORCE)

    set(SYS_DXSDK_ROOT "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK \(June 2010\)")

    if (NOT EXISTS "${SYS_DXSDK_ROOT}")
        message(FATAL_ERROR "Cannot find DX SDK root")
    endif()
elseif ("${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" MATCHES "10")
    set(SYS_PSDK_ROOT "${SYS_PSDK_ROOT}/10")
    set(SYS_IS_PSDK_V10 TRUE CACHE BOOL "Platform SDK for NT10+" FORCE)
endif()

if (NOT EXISTS "${SYS_PSDK_ROOT}")
    message(FATAL_ERROR "Cannot find Platform SDK")
endif()

mark_as_advanced(SYS_DXSDK_ROOT)
mark_as_advanced(SYS_DXSDK_NEEDED)
mark_as_advanced(SYS_IS_PSDK_V10)
set(SYS_PSDK_ROOT "${SYS_PSDK_ROOT}" CACHE STRING "Platform SDK root" FORCE)
mark_as_advanced(SYS_PSDK_ROOT)

if (SYS_IS_PSDK_V10) # ucrt
    set(SYS_PSDK_TARGET "0x0601" CACHE STRING "Platform SDK target ID" FORCE)
    set(SYS_PSDK_INC_ROOT "${SYS_PSDK_ROOT}/Include/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
    set(SYS_PSDK_INC "${SYS_PSDK_INC_ROOT}/ucrt;${SYS_PSDK_INC_ROOT}/shared;${SYS_PSDK_INC_ROOT}/um" CACHE STRING "Platform SDK includes directory" FORCE)
    set(SYS_PSDK_LIB_ROOT "${SYS_PSDK_ROOT}/Lib/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}/${WINARCH}")
    set(SYS_PSDK_LIBDIR "${SYS_CRT_LIB_ROOT}/um;${SYS_CRT_LIB_ROOT}/ucrt;${VS_CRT_LIBDIR}" CACHE STRING "Platform SDK library directory" FORCE)
    set(SYS_PSDK_BINDIR "${SYS_PSDK_ROOT}/bin/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}/${WINARCH}" CACHE STRING "Platform SDK bin directory" FORCE) # TODO: THIS SHOULD BE HOST WIDE NOT COMPILATION WIDE
else()
    set(SYS_PSDK_TARGET "0x0501" CACHE STRING "Platform SDK target ID" FORCE)
    set(SYS_PSDK_INC "${SYS_PSDK_ROOT}/Include;${SYS_PSDK_ROOT_10}/Include/${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}/ucrt" CACHE STRING "Platform SDK includes directory" FORCE)

    if ("${ARCH}" STREQUAL "amd64")
        set(SYS_PSDK_LIBDIR "${SYS_PSDK_ROOT}/Lib/x64" CACHE STRING "Platform SDK library directory" FORCE)
        set(SYS_PSDK_BINDIR "${SYS_PSDK_ROOT}/Bin/x64" CACHE STRING "Platform SDK bin directory" FORCE)  # TODO: THIS SHOULD BE HOST WIDE NOT COMPILATION WIDE
    else()
        set(SYS_PSDK_LIBDIR "${SYS_PSDK_ROOT}/Lib" CACHE STRING "Platform SDK library directory" FORCE)
        set(SYS_PSDK_BINDIR "${SYS_PSDK_ROOT}/Bin" CACHE STRING "Platform SDK bin directory" FORCE)  # TODO: THIS SHOULD BE HOST WIDE NOT COMPILATION WIDE
    endif()
endif()

mark_as_advanced(SYS_PSDK_INC)
mark_as_advanced(SYS_PSDK_LIBDIR)
mark_as_advanced(SYS_PSDK_BINDIR)

message(STATUS "VS install path: ${SYS_VISUALSTUDIO_PATH}")
message(STATUS "MSVC version: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
message(STATUS "MSVC toolchain: ${SYS_MSVC_TOOLCHAIN}")
message(STATUS "MSVC CRT path: ${SYS_MSVC_CRT_ROOT}")
message(STATUS "Target NT5.1: ${SYS_IS_XP}")
message(STATUS "PSDK path: ${SYS_PSDK_ROOT}")
message(STATUS "PSDK NT10+: ${SYS_IS_PSDK_V10}")
if (SYS_DXSDK_NEEDED)
    message(STATUS "DXSDK root: ${SYS_DXSDK_ROOT}")
endif()

# Host bootstrap

# mc.exe search
if (WIN32)
  # cmake has CMAKE_RC_COMPILER, but no message compiler
  if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
    set(MC_ROOT "${SYS_PSDK_BINDIR}")
  endif()
  find_program(CMAKE_MC_COMPILER mc.exe HINTS "${MC_ROOT}")
  if(NOT CMAKE_MC_COMPILER)
    message(FATAL_ERROR "Message compiler not found")
  endif()
  message(STATUS "Found message compiler: ${CMAKE_MC_COMPILER}")
  mark_as_advanced(CMAKE_MC_COMPILER)
endif()

function(get_host_includes)
    set(HOST_CRT_INC "${SYS_PSDK_INC};${SYS_MSVC_CRT_INC}" PARENT_SCOPE)
    set(HOST_CRT_LIBDIR "${SYS_PSDK_LIBDIR};${SYS_MSVC_CRT_LIBDIR}" PARENT_SCOPE)
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


function(add_cd_file)
# no cd out, this is not reactos!!
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

    if (NOT SYS_DXSDK_NEEDED)
        add_library(dxsdk ALIAS psdk)
    else()
        add_library(dxsdk INTERFACE)
        #target_link_directories(dxsdk INTERFACE ${SYS_DXSDK_ROOT}/Lib/${WINARCH})
        target_include_directories(dxsdk INTERFACE ${SYS_DXSDK_ROOT}/Include)
    endif()

    add_library(cppstl INTERFACE)
    target_link_libraries(cppstl INTERFACE psdk libcpmt.lib)

    add_library(atl_classes INTERFACE)
    target_include_directories(atl_classes INTERFACE ${SYS_MSVC_CRT_ROOT}/atlmfc/include)
    target_link_directories(atl_classes INTERFACE ${SYS_MSVC_CRT_ROOT}/atlmfc/lib/${WINARCH})
    target_link_libraries(atl_classes INTERFACE atls)
endfunction()

function(get_native_tool_path file)
    set(NATIVE_TOOL_EXE "cmake" -D TARGET_FILE=${file} -D HOST_OUT_PATH="${HOST_OUT_PATH}" -P "${REACTOS_SOURCE_DIR}/sdk/cmake/run_host.cmake" -- PARENT_SCOPE)
endfunction()
