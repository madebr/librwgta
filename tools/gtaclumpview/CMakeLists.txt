add_executable(gtaclumpview WIN32
    camera.cpp
    camera.h
    main.cpp
    )

target_link_libraries(gtaclumpview
    PRIVATE
        librwgta
        librw_skeleton
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS gtaclumpview
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
