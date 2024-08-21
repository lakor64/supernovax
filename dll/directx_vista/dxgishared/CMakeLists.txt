target_dx()

add_library(dxgishared STATIC
    dxgidevice.cpp
    dxgidevice.h
    dxgidevicesubobject.h
    dxgikeyedmutex.cpp
    dxgikeyedmutex.h
    dxgiobject.h
    dxgiresource.cpp
    dxgiresource.h
    dxgishared.h
    dxgisurface.cpp
    dxgisurface.h
    dxgithunks.h
    dxgitypes.h
    dxgiusecounted.h
    lockedowner.h
)
target_link_libraries(dxgishared PUBLIC cppstl atl_classes dxguid)
target_include_directories(dxgishared PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_dependencies(dxgishared dxsdk)
set_target_properties(dxgishared PROPERTIES WITH_CXX_EXCEPTIONS TRUE)
