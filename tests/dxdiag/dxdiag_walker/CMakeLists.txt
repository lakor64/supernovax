add_definitions(-D_UNICODE)
add_executable(dxdiag_walker walker.cpp)
add_dependencies(dxdiag_walker dxsdk)
target_link_libraries(dxdiag_walker psdk dxguid cppstl)
set_module_type(dxdiag_walker win32cui)
set_target_properties(dxdiag_walker PROPERTIES 
	WITH_CXX_EXCEPTIONS 1
	WITH_CXX_RTTI 1
)
