cmake_minimum_required(VERSION 3.17.0)
project(pff)

include(CMakeDependentOption)

add_definitions(-D__PFF__)
set(PFF TRUE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_SKIP_PREPROCESSED_SOURCE_RULES TRUE)
set(CMAKE_SKIP_ASSEMBLY_SOURCE_RULES TRUE)
set(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

## PFF SPECIFIC CODE ------------------------

option(ENABLE_TESTS "Enable pff tests" ON)
set(REACTOS_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(REACTOS_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(HOST_OUT_PATH "${REACTOS_BINARY_DIR}/bin-tools")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${REACTOS_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${REACTOS_BINARY_DIR}/bin")

# fake modules
include(sdk/cmake/fake_ros.cmake)

if (NOT DEFINED DLL_EXPORT_VERSION)
    if (SYS_IS_XP)
        set(DLL_EXPORT_VERSION "0x501" CACHE STRING "" FORCE)
    else()
        set(DLL_EXPORT_VERSION "0x601" CACHE STRING "" FORCE)
    endif()
endif()

# check that the ARCH (target architecture) variable is defined
if(NOT ARCH)
    # imagine unironically using ARM64/ARM (bro I'm poor)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH "amd64" CACHE STRING "" FORCE)
    else()
        set(ARCH "x86" CACHE STRING "" FORCE)
    endif()
endif()

## END OF PFF SPECIFIC CODE -----------------------------

# Now the ARCH variable will be in lowercase.
# It is needed because STREQUAL comparison
# is case-sensitive.
# See http://cmake.3232098.n2.nabble.com/Case-insensitive-string-compare-td7580269.html
# for more information.
string(TOLOWER ${ARCH} ARCH)

# set possible values for cmake GUI
set_property(CACHE ARCH PROPERTY STRINGS "i386" "amd64" "arm" "arm64")

# Alternative WinNT-compatible architecture string
if(ARCH STREQUAL "i386")
    set(WINARCH "x86")
else()
    set(WINARCH ${ARCH})
endif()

# set CMAKE_BUILD_TYPE if not set
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to Debug as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
                 "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Versioning
include(sdk/include/reactos/version.cmake)

# Compile options
include(sdk/cmake/config.cmake)

# Compiler flags handling
include(sdk/cmake/compilerflags.cmake)

add_definitions(
    -D__REACTOS__
    # swprintf without count argument is used in most of the codebase
    -D_CRT_NON_CONFORMING_SWPRINTFS
)

# There doesn't seem to be a standard for __FILE__ being relative or absolute, so detect it at runtime.
file(RELATIVE_PATH _PATH_PREFIX ${REACTOS_BINARY_DIR} ${REACTOS_SOURCE_DIR})
if (NOT MSVC AND ((CMAKE_C_COMPILER_ID STREQUAL "GNU") AND (CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "8.0.0")
               OR (CMAKE_C_COMPILER_ID STREQUAL "Clang") AND (CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0")))
    # Thankfully, GCC has this
    add_compile_options(-ffile-prefix-map=${REACTOS_SOURCE_DIR}=)
    add_compile_options(-ffile-prefix-map=${_PATH_PREFIX}=)
else()
    string(LENGTH ${_PATH_PREFIX} _PATH_PREFIX_LENGTH)
    string(LENGTH ${REACTOS_SOURCE_DIR} REACTOS_SOURCE_DIR_LENGTH)
    math(EXPR REACTOS_SOURCE_DIR_LENGTH "${REACTOS_SOURCE_DIR_LENGTH} + 1")
    add_compile_definitions("$<$<COMPILE_LANGUAGE:C,CXX>:__RELFILE__=&__FILE__[__FILE__[0] == '.' ? ${_PATH_PREFIX_LENGTH} : ${REACTOS_SOURCE_DIR_LENGTH}]>")
endif()

if(MSVC_IDE)
    add_compile_options("/MP")
endif()

## pff does not crosscompile!
set(TOOLS_FOLDER ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DTARGET_${ARCH})

if(MSVC)
    if(ARCH STREQUAL "i386")
        add_definitions(/D_X86_ /D__i386__ /DWIN32 /D_WINDOWS)
    elseif(ARCH STREQUAL "amd64")
        add_definitions(-D_AMD64_ -D__x86_64__ /DWIN32 -D_WINDOWS)
    endif()
    if(MSVC_VERSION GREATER 1699)
        add_definitions(/D_ALLOW_KEYWORD_MACROS)
    endif()
endif()
add_subdirectory(sdk/include/host)

# bootstrap reactos-like env (damn this build system...)

# We don't need CMake importlib handling.
unset(CMAKE_IMPORT_LIBRARY_SUFFIX)

# Print build type(s)
if(CMAKE_CONFIGURATION_TYPES)
    # Multi-config generators, like Visual Studio (MSBuild).
    message("-- Configuration types: ${CMAKE_CONFIGURATION_TYPES}")
else()
    # Single-configuration generators, like Ninja.
    message("-- Build type: ${CMAKE_BUILD_TYPE}")
endif()

# Always add /MT in VS CMAKE_GENERATOR and define _SBCS otherwise VS thinks it's a multi-byte or whatever project
if (MSVC_IDE)
    add_compile_options("/MT")
    add_compile_definitions(_SBCS)
endif()


# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)

# Add our own target properties
# General module definitions
define_property(TARGET PROPERTY REACTOS_MODULE_TYPE
    BRIEF_DOCS "The type of this module"
    FULL_DOCS [[
The type of this module.
One of "nativecui", "nativedll", "kernelmodedriver", "wdmdriver", "kerneldll", "win32cui", "win32gui", "win32dll", "win32ocx", "cpl" or "module"]])

# C++
define_property(TARGET PROPERTY WITH_CXX_EXCEPTIONS
    BRIEF_DOCS "Enable C++ exceptions on this target"
    FULL_DOCS [[
Enables C++ exception handling.
Enable this if the module uses try/catch or throw. You might also need this if you use a standard operator new (the one without nothrow).]])
define_property(TARGET PROPERTY WITH_CXX_RTTI
    BRIEF_DOCS "Enable C++ RTTI on this target"
    FULL_DOCS [[
Enables run-time type information.
Enable this if the module uses typeid or dynamic_cast. You will probably need to link yith cpprt as well, if you are not already using STL.]])


if(DBG)
    add_definitions(-DDBG=1 -D_SEH_ENABLE_TRACE)
else()
    add_definitions(-DDBG=0)
endif()

# Version Options
add_definitions(-DWINVER=0x502
                -D_WIN32_IE=0x600
                -D_WIN32_WINNT=0x502
                -D_WIN32_WINDOWS=0x502
                -D_SETUPAPI_VER=0x502
                -DMINGW_HAS_SECURE_API=1
                -DDLL_EXPORT_VERSION=${DLL_EXPORT_VERSION})

if(ARCH STREQUAL "i386")
    # clang-cl defines this one for itself
    if(NOT (MSVC AND CMAKE_C_COMPILER_ID STREQUAL "Clang"))
        add_definitions(-D_M_IX86)
    endif()
    add_definitions(-D_X86_ -D__i386__ -Di386)
    if(SARCH STREQUAL "xbox")
        add_definitions(-DSARCH_XBOX)
    elseif(SARCH STREQUAL "pc98")
        add_definitions(-DSARCH_PC98)
    endif()
elseif(ARCH STREQUAL "amd64")
    # clang-cl defines this one for itself
    if (NOT (MSVC AND CMAKE_C_COMPILER_ID STREQUAL "Clang"))
        add_compile_definitions(_M_AMD64)
    endif()
    add_definitions(-D_AMD64_ -D__x86_64__ -D_WIN64)
elseif(ARCH STREQUAL "arm")
    # _M_ARM is already defined by toolchain
    add_definitions(-D_ARM_ -D__arm__ -DWIN32)
    if(SARCH STREQUAL "omap3-zoom2")
        add_definitions(-D_ZOOM2_)
    endif()
elseif(ARCH STREQUAL "arm64")
    # GNU tools refer to arm64 as aarch64
    add_definitions(-D_ARM64_ -D__arm64__ -D__aarch64__ -D_WIN64)
endif()

# Other
add_definitions(-D_NEW_DELETE_OPERATORS_)
if(ARCH STREQUAL "i386")
    add_definitions(-DUSE_COMPILER_EXCEPTIONS -D_USE_32BIT_TIME_T)
elseif(ARCH STREQUAL "amd64")
    add_compile_definitions(USE_COMPILER_EXCEPTIONS)
elseif(ARCH STREQUAL "arm")
    add_compile_definitions(USE_COMPILER_EXCEPTIONS)
elseif(ARCH STREQUAL "arm64")
    add_compile_definitions(USE_COMPILER_EXCEPTIONS)
endif()

# Activate support for assembly source files
if (MSVC)
enable_language(ASM_MASM)
else()
enable_language(ASM)
endif()

# Activate language support for resource files
enable_language(RC)

# Localization definitions
include(sdk/cmake/localization.cmake)
set(I18N_DEFS "")
# This will set I18N_DEFS for later use
set_i18n_language(${I18N_LANG})

# Compiler specific definitions and macros
if(MSVC)
include(sdk/cmake/msvc.cmake)
else()
include(sdk/cmake/gcc.cmake)
endif()

# Generic macros
include(sdk/cmake/CMakeMacros.cmake)

# IDL macros for widl/midl

if (MSVC)
    include(sdk/cmake/midl-support.cmake)
else()
    include(sdk/cmake/widl-support.cmake)
endif()


include_directories(
    sdk/include
    ${REACTOS_BINARY_DIR}/sdk/include
    ${REACTOS_BINARY_DIR}/sdk/include/reactos
    ${REACTOS_BINARY_DIR}/sdk/include/reactos/mc
    sdk/include/reactos
    sdk/include/reactos/libs)

if(ARCH STREQUAL "arm")
    include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/arm)
endif()

## pff specific code

# get all host includes for host tools
get_host_includes()
# now we have ${HOST_CRT_INC} and ${HOST_CRT_LIBDIR}

# really bootstrap sdk/tools in a way that's not cancer
add_subdirectory(sdk/tools)

add_fake_targets()

## end of pff specific code

add_dependency_header()

include_directories(${SYS_PSDK_INC} ${SYS_MSVC_CRT_INC})
link_directories(${SYS_PSDK_LIBDIR} ${SYS_MSVC_CRT_LIBDIR})

#add_subdirectory(sdk/include/reactos/wine) # manually import wine!
add_subdirectory(sdk/include/reactos/mc)

if(ARCH MATCHES "64$")
    include(sdk/cmake/baseaddress64.cmake)  
elseif(NO_ROSSYM)
    include(sdk/cmake/baseaddress_dwarf.cmake)
elseif(MSVC)
    include(sdk/cmake/baseaddress_msvc.cmake)
else()
    include(sdk/cmake/baseaddress.cmake)
endif()

# For MSVC builds, this puts all debug symbols file in the same directory.
if(MSVC)
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${REACTOS_BINARY_DIR}/msvc_pdb")
elseif(SEPARATE_DBG)
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${REACTOS_BINARY_DIR}/symbols")
endif()

add_subdirectory(sdk/include/dxsdk)
add_subdirectory(sdk/lib)
add_subdirectory(dll)
add_subdirectory(base)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()
