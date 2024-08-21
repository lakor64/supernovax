target_dx()

list(APPEND SOURCE

)


add_executable(fxc ${SOURCE} fxc.rc)
set_module_type(fxc win32cui UNICODE)
add_dependencies(fxc dxsdk)
