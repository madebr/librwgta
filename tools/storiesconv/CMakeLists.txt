set(STORIESCONV_SOURCES
    animation.h
    animgroups_lcs.h
    leedsgta.h
    storiesconv.cpp
    storiesconv.h
    streamworld.h
    hash.cpp
    relocchunk.h
    relocchunk.cpp
    rsl.cpp
    rsl.h
    rslconv.cpp
    )

add_executable(lcsconv
    ${STORIESCONV_SOURCES}
    )

target_compile_definitions(lcsconv
    PRIVATE
        LCS
    )

target_link_libraries(lcsconv
    PRIVATE
        librwgta
    )

set_property(TARGET lcsconv PROPERTY CXX_STANDARD 11)

add_executable(vcsconv
    ${STORIESCONV_SOURCES}
    )

target_compile_definitions(vcsconv
    PRIVATE
        VCS
    )

target_link_libraries(vcsconv
    PRIVATE
        librwgta
    )

set_property(TARGET vcsconv PROPERTY CXX_STANDARD 11)

if(LIBRWGTA_INSTALL)
    install(TARGETS lcsconv vcsconv
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
endif()
