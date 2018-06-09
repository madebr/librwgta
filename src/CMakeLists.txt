add_library(librwgta
    collisions.cpp
    collisions.h
    gtaplg.cpp
    rsps2.cpp
    rsxbox.cpp
    rwgta.h
    )

target_include_directories(librwgta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

target_link_libraries(librwgta
    PUBLIC
        librw
    )

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(librwgta
        PRIVATE
            "-Wall"
        )
    if (NOT LIBRW_PLATFORM_PS2)
        target_compile_options(librwgta
            PRIVATE
                "-Wextra"
                "-Wdouble-promotion"
                "-Wpedantic"
            )
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(librwgta
        INTERFACE
            /wd4996 /wd4244
        )
endif()

set_target_properties(librwgta
    PROPERTIES
        C_STANDDARD 99
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 98
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        PREFIX ""
    )

if(LIBRWGTA_INSTALL)
    target_include_directories(librwgta
        INTERFACE
            $<INSTALL_INTERFACE:${LIBRWGTA_INSTALL_INCLUDEDIR}>
        )

    install(
        FILES
            rwgta.h
        DESTINATION "${LIBRWGTA_INSTALL_INCLUDEDIR}"
        )
    install(
        TARGETS librwgta
        EXPORT librwgta-targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
endif()
