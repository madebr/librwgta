add_executable(convtxd
    convtxd.cpp
    )

target_link_libraries(convtxd
    PUBLIC
        librwgta
    )


if(LIBRWGTA_INSTALL)
    install(TARGETS convtxd
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
