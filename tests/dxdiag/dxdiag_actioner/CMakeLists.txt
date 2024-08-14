add_definitions(-D_UNICODE)
add_executable(dxdiag_actioner actioner.cpp)
target_link_libraries(dxdiag_actioner psdk dxsdk dxguid cppstl)
set_module_type(dxdiag_actioner win32cui)
set_target_properties(dxdiag_actioner PROPERTIES 
	WITH_CXX_EXCEPTIONS 1
	WITH_CXX_RTTI 1
)
