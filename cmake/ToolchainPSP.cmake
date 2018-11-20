set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER "mips-unknown-elf-gcc")
set(_psp_flags "-EL -mabi=eabi -march=mips2 -ffreestanding -nostdlib")
set(CMAKE_C_FLAGS "${_psp_flags}")
set(CMAKE_CXX_FLAGS "${_psp_flags}")
set(CMAKE_ASM_FLAGS "${_psp_flags}")

set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_ASM_FLAGS_RELEASE "-Os")

macro(add_mod _name)
    set(_name_elf "${_name}_elf")
    add_executable(${_name_elf} ${ARGN})
    set_target_properties(
        ${_name_elf}
        PROPERTIES
        OUTPUT_NAME "${_name}.elf"
        LINK_FLAGS "-Wl,-q -T${CMAKE_SOURCE_DIR}/src/link.ld"
    )
    target_link_libraries(${_name_elf} libchantage gcc)
    add_custom_command(
        OUTPUT
        "${_name}.prx"
        DEPENDS
        ${_name_elf}
        COMMAND
        "psp-prxgen"
        "$<TARGET_FILE:${_name_elf}>"
        "${_name}.prx"
        WORKING_DIRECTORY
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        VERBATIM
    )

    add_custom_target(
        ${_name} ALL
        DEPENDS
        "${_name}.prx"
        WORKING_DIRECTORY
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        VERBATIM
    )
endmacro()
