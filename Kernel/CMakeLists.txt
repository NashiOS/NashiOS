set(ASM_SOURCES
        Boot.S)

set(CXX_SOURCES
        Main.cpp)

add_executable(Kernel ${ASM_SOURCES} ${CXX_SOURCES})
target_link_libraries(Kernel PRIVATE gcc)
target_compile_options(Kernel PRIVATE -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti)
target_link_options(Kernel PRIVATE -ffreestanding -O2 -nostdlib)
target_link_options(Kernel PRIVATE LINKER:-T ${CMAKE_CURRENT_SOURCE_DIR}/Linker.ld)
install(TARGETS Kernel DESTINATION boot)
