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
    "${CHANTAGE_PREFIX}psp-prxgen"
    "$<TARGET_FILE:chantage_elf>"
    "chantage.prx"
    WORKING_DIRECTORY
    "${CHANTAGE_BUILD_BIN}"
    VERBATIM
)

add_custom_target(chantage ALL
    DEPENDS
    "chantage.prx"
    WORKING_DIRECTORY
    "${CHANTAGE_BUILD_BIN}"
    VERBATIM
)

install(
    FILES
    "${CHANTAGE_BUILD_BIN}/chantage.prx"
    DESTINATION
    "${CHANTAGE_PSP_PREFIX}"
)