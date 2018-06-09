add_executable(coltest
    coltest.cpp
    )

target_link_libraries(coltest
    PUBLIC
        librwgta
    )

if(LIBRWGTA_INSTALL)
    install(TARGETS coltest
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
