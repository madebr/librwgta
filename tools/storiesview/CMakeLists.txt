if(LIBRW_PLATFORM_D3D9)
    find_package(ZLIB REQUIRED)
endif()

set(STORIESVIEW_SOURCES
    buildingpipe.cpp
    camera.cpp
    camera.h
    collision.cpp
    colourcodepipe.cpp
    debugrender.cpp
    gui.cpp
    main.cpp
    misc.cpp
    ModelInfo.cpp
    Pad.cpp
    Pad.h
    Pools.cpp
    render.cpp
    storiesview.h
    templates.h
    TexListStore.cpp
    TexListStore.h
    vcs_links.inc
    WaterLevel.cpp
    worldext.cpp
    worldstream.cpp
    zfile.cpp

    "${PROJECT_SOURCE_DIR}/tools/storiesconv/hash.cpp"
    "${PROJECT_SOURCE_DIR}/tools/storiesconv/relocchunk.cpp"
    "${PROJECT_SOURCE_DIR}/tools/storiesconv/rsl.cpp"
    "${PROJECT_SOURCE_DIR}/tools/storiesconv/rslconv.cpp"
    )

add_executable(lcsview WIN32
    ${STORIESVIEW_SOURCES}
    )

target_include_directories(lcsview
    PRIVATE
        "${PROJECT_SOURCE_DIR}/tools/storiesconv"
    )

target_compile_definitions(lcsview
    PRIVATE
        LCS
    )

target_link_libraries(lcsview
    PRIVATE
        librw_skeleton_imgui
        librwgta
        ZLIB::ZLIB
    )

add_executable(vcsview WIN32
    ${STORIESVIEW_SOURCES}
    )

target_include_directories(vcsview
    PRIVATE
        "${PROJECT_SOURCE_DIR}/tools/storiesconv"
    )

target_compile_definitions(vcsview
    PRIVATE
        VCS
    )

target_link_libraries(vcsview
    PRIVATE
        librw_skeleton_imgui
        librwgta
        ZLIB::ZLIB
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS lcsview vcsview
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
