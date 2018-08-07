add_executable(gl3test
    camera.cpp
    camera.h
    common.cpp
    gldemo.h
    input.h
    main.cpp
    )

target_link_libraries(gl3test
    PRIVATE
        librwgta
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS gl3test
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
