add_executable(euryopa WIN32
    buildingpipe.cpp
    buildingpipe_d3d9.cpp
    buildingpipe_gl3.cpp
    camera.cpp
    camera.h
    cdimage.cpp
    Clouds.cpp
    collision.cpp
    collision.h
    colourcodepipe.cpp
    colstore.cpp
    debugrender.cpp
    euryopa.cpp
    euryopa.h
    fileloader.cpp
    gui.cpp
    iplstore.cpp
    main.cpp
    neoWorld_d3d9.cpp
    neoWorld_gl3.cpp
    objectdef.cpp
    objectinst.cpp
    Pad.cpp
    Pad.h
    postfx.cpp
    PtrList.h
    PtrNode.cpp
    PtrNode.h
    Rect.h
    renderer.cpp
    Sprite.cpp
    Sprite.h
    templates.h
    timecycle.cpp
    timecycle.h
    txdstore.cpp
    WaterLevel.cpp
    zones.cpp
    minilzo/minilzo.c
    )

target_link_libraries(euryopa
    PRIVATE
        librwgta
        librw_skeleton_imgui
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS euryopa
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
