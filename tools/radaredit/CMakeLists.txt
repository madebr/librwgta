add_executable(radaredit
    radaredit.cpp
    )

target_link_libraries(radaredit
    PUBLIC
        librwgta
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS radaredit
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
