cmake_minimum_required(VERSION 3.8)

project(librwgta C CXX)

option(LIBRWGTA_TOOLS "Build librwgta tools" OFF)
option(LIBRWGTA_INSTALL "Install librwgta files" OFF)

if(LIBRWGTA_INSTALL)
    include(GNUInstallDirs)
    set(LIBRWGTA_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/librwgta")
endif()

if(NOT TARGET librw)
    find_package(librw REQUIRED)
    message(STATUS "LIBRW_PLATFORM = ${LIBRW_PLATFORM} (choices=${LIBRW_PLATFORMS})")
endif()

add_subdirectory(src)

if(LIBRWGTA_TOOLS)
    add_subdirectory(tools)
endif()

if(LIBRWGTA_INSTALL)
    include(CMakePackageConfigHelpers)
    configure_package_config_file(librwgta-config.cmake.in librwgta-config.cmake
        INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}"
        )
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/librwgta-config.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        )
    install(
        EXPORT librwgta-targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}"
        )

    include(CMakeCPack.cmake)
endif()
