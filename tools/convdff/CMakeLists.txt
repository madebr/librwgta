add_executable(convdff
    convdff.cpp
    )

target_link_libraries(convdff
    PUBLIC
        librwgta
    )


if(LIBRWGTA_INSTALL)
    install(TARGETS convdff
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
