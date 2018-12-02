file(GLOB_RECURSE SOURCES "*.c")
add_executable(chantage_elf ${SOURCES})
target_link_libraries(chantage_elf libchantage libprx gcc)
set_target_properties(
    chantage_elf
    PROPERTIES
    OUTPUT_NAME
    "chantage.elf"
    LINK_FLAGS
    "-Wl,-q -T${CMAKE_SOURCE_DIR}/src/link.ld"
)

add_custom_command(
    OUTPUT
    "chantage.prx"
    DEPENDS
    chantage_elf
    COMMAND
    "psp-prxgen"
    "$<TARGET_FILE:chantage_elf>"
    "chantage.prx"
    WORKING_DIRECTORY
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    VERBATIM
)

add_custom_target(chantage ALL
    DEPENDS
    "chantage.prx"
    WORKING_DIRECTORY
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    VERBATIM
)

install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")