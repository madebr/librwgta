add_executable(d3d9test WIN32
    camera.cpp
    camera.h
    d3dInit.cpp
    )

target_link_libraries(d3d9test
    PUBLIC
        librwgta
        winmm
    )


if(LIBRWGTA_INSTALL)
    install(TARGETS d3d9test
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
