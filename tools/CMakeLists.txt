add_subdirectory(coltest)

add_subdirectory(convdff)

add_subdirectory(convtxd)

if(LIBRW_PLATFORM_D3D9)
    add_subdirectory(d3d9test)
endif()

if(NOT LIBRW_PLATFORM_NULL AND NOT LIBRW_PLATFORM_PS2)
    add_subdirectory(euryopa)
endif()

if(LIBRW_PLATFORM_GL3)
    #add_subdirectory(gl3test)
endif()

if(NOT LIBRW_PLATFORM_NULL AND NOT LIBRW_PLATFORM_PS2)
    add_subdirectory(gtaclumpview)
endif()

if(NOT LIBRW_PLATFORM_NULL AND NOT LIBRW_PLATFORM_PS2)
    add_subdirectory(IIItest)
endif()

add_subdirectory(radaredit)

add_subdirectory(storiesconv)

if(LIBRW_PLATFORM_D3D9)
    add_subdirectory(storiesview)
endif()
