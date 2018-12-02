set(CMAKE_SYSTEM_NAME Generic)
set(CHANTAGE_PREFIX "chantage-")
set(CMAKE_C_COMPILER "${CHANTAGE_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${CHANTAGE_PREFIX}g++")
set(CHANTAGE_FLAGS "-EL -mabi=eabi -march=mips2 -ffreestanding -nostdlib")
set(CMAKE_C_FLAGS "${CHANTAGE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CHANTAGE_FLAGS}")
set(CMAKE_ASM_FLAGS "${CHANTAGE_FLAGS}")

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
        "${CHANTAGE_PREFIX}psp-prxgen"
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
