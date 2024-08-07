spec2def(fakewine.dll fakewine.spec ADD_IMPORTLIB)

add_definitions(-D_USRDLL)

add_library(fakewine MODULE debug.c)
set_module_type(fakewine win32dll UNICODE)
target_link_libraries(fakewine PRIVATE psdk user32)
