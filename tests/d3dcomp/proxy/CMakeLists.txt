target_dx()

add_definitions(-D_UNICODE)
add_executable(d3dcomp_proxy proxy.cpp)
add_dependencies(d3dcomp_proxy dxsdk)
target_link_libraries(d3dcomp_proxy psdk dxguid cppstl)
set_module_type(d3dcomp_proxy win32cui)
set_target_properties(d3dcomp_proxy PROPERTIES 
	WITH_CXX_EXCEPTIONS 1
	WITH_CXX_RTTI 1
)
