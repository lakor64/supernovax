if (WIN32)
    set(TARGET_HOST_SUFFIX ".exe")
else()
    set(TARGET_HOST_SUFFIX "")
endif()

set(HOST_FILENAME "${TARGET_FILE}${TARGET_HOST_SUFFIX}")
set(TARGETS "Debug;Release;RelWithDebInfo;MinSizeRel;;")
set(TOOL_FOUND 0)

foreach(P IN ITEMS ${TARGETS})
    set(HOST_BASEDIR "${HOST_OUT_PATH}/${P}")
    if (EXISTS "${HOST_BASEDIR}/${HOST_FILENAME}")
        set(NATIVE_TOOL_PATH "${HOST_BASEDIR}/${HOST_FILENAME}")
        break()
    endif()
endforeach()

if (NOT DEFINED NATIVE_TOOL_PATH)
    message(FATAL_ERROR "Cannot find tool ${HOST_FILENAME}")
endif()

foreach(i RANGE 0 ${CMAKE_ARGC} 1)
    if ("${CMAKE_ARGV${i}}" STREQUAL "--")
        set(DOUBLEDASH_INDEX ${i})
        break()
    endif()
endforeach(i)

set(APP_ARGS )

if (DEFINED DOUBLEDASH_INDEX)
    math(EXPR DOUBLEDASH_INDEX "${DOUBLEDASH_INDEX} + 1" OUTPUT_FORMAT DECIMAL)

    foreach(i RANGE ${DOUBLEDASH_INDEX} ${CMAKE_ARGC} 1)
        set(APP_ARGS "${APP_ARGS};${CMAKE_ARGV${i}}")
    endforeach()
endif()

execute_process(
    COMMAND "${NATIVE_TOOL_PATH}" ${APP_ARGS}
)
