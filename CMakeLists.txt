cmake_minimum_required(VERSION 3.22)
project(NashiOS ASM CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME NashiOS)
set(CMAKE_SYSTEM_PROCESSOR ${NASHIOS_PROCESSOR})

set(CMAKE_SYSROOT ${CMAKE_BINARY_DIR}/Sysroot)
set(CMAKE_STAGING_PREFIX ${CMAKE_SYSROOT})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SYSROOT})
set(CMAKE_INSTALL_DATAROOTDIR ${CMAKE_SYSROOT}/usr/share)

set(TOOLCHAIN_PATH ${CMAKE_SOURCE_DIR}/Binary/Toolchain/${NASHIOS_ARCHITECTURE}/Cross/bin)
SET(TOOLCHAIN_TARGET ${NASHIOS_ARCHITECTURE}-elf)
set(TOOLCHAIN_PREFIX ${TOOLCHAIN_PATH}/${TOOLCHAIN_TARGET})

set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}-ld)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}-gcc-ar)
set(CMAKE_NM ${TOOLCHAIN_PREFIX}-gcc-nm)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}-gcc-ranlib)
set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}-strip)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

add_compile_options(-Wall -Wextra)

add_custom_target(toolchain
    COMMAND "SOURCE_DIR=${CMAKE_SOURCE_DIR}" "ARCH=${NASHIOS_ARCHITECTURE}" "TARGET=${TOOLCHAIN_TARGET}" ${CMAKE_SOURCE_DIR}/Scripts/SetupToolchain.sh
    USES_TERMINAL)

add_custom_target(run
    COMMAND ${CMAKE_SOURCE_DIR}/Scripts/Run.sh
    USES_TERMINAL)

function(nashios_install_headers target_name)
    file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp")
    foreach (header ${headers})
        get_filename_component(subdirectory ${header} DIRECTORY)
        install(FILES ${header} DESTINATION usr/include/${target_name}/${subdirectory})
    endforeach ()
endfunction()

function(nashios_install_sources)
    cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR BASE_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE relative_dir)
    file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.hpp")
    foreach (source ${sources})
        get_filename_component(subdirectory ${source} DIRECTORY)
        install(FILES ${source} DESTINATION usr/src/NashiOS/${relative_dir}/${subdirectory} OPTIONAL)
    endforeach ()
endfunction()

include_directories(.)

add_subdirectory(Kernel)
