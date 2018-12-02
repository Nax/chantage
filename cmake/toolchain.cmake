set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_INSTALL_PREFIX "")

set(CHANTAGE_BUILD_BIN "${CMAKE_BINARY_DIR}/bin")
set(CHANTAGE_BUILD_LIB "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CHANTAGE_BUILD_LIB}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CHANTAGE_BUILD_LIB}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CHANTAGE_BUILD_BIN}")

set(CHANTAGE_PREFIX "chantage-")
set(CHANTAGE_PSP_PREFIX "PSP/COMMON/ULUS10297/")
set(CMAKE_C_COMPILER "${CHANTAGE_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${CHANTAGE_PREFIX}g++")
set(CHANTAGE_FLAGS "-EL -mabi=eabi -march=mips2 -ffreestanding -nostdlib")
set(CMAKE_C_FLAGS "${CHANTAGE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CHANTAGE_FLAGS}")
set(CMAKE_ASM_FLAGS "${CHANTAGE_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_ASM_FLAGS_RELEASE "-Os")

set(CHANTAGE_MODS "" CACHE INTERNAL "")

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
        "${CHANTAGE_BUILD_BIN}"
        VERBATIM
    )

    set(CHANTAGE_MODS "${CHANTAGE_MODS};${_name}.prx" CACHE INTERNAL "")

    add_custom_target(
        ${_name} ALL
        DEPENDS
        "${_name}.prx"
        WORKING_DIRECTORY
        "${CHANTAGE_BUILD_BIN}"
        VERBATIM
    )

    install(
        FILES
        "${CHANTAGE_BUILD_BIN}/${_name}.prx"
        DESTINATION
        "${CHANTAGE_PSP_PREFIX}/mods/"
    )
endmacro()
