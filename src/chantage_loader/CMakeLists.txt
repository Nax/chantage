file(GLOB_RECURSE SOURCES "*.c" "*.S")
add_executable(chantage_loader_elf ${SOURCES})
target_link_libraries(chantage_loader_elf libprx libchantage)
set_target_properties(
    chantage_loader_elf
    PROPERTIES
    LINK_FLAGS
    "-lgcc -T${CMAKE_SOURCE_DIR}/src/link_loader.ld"
    OUTPUT_NAME
    "chantage_loader.elf"
)

add_custom_command(
    OUTPUT
    "chantage_loader.bin"
    DEPENDS
    chantage_loader_elf
    COMMAND
    "${CHANTAGE_PREFIX}objcopy"
    "-S"
    "-O"
    "binary"
    "$<TARGET_FILE:chantage_loader_elf>"
    "chantage_loader.bin"
    WORKING_DIRECTORY
    "${CHANTAGE_BUILD_BIN}"
    VERBATIM
)

add_custom_target(chantage_loader ALL
    DEPENDS
    "chantage_loader.bin"
    WORKING_DIRECTORY
    "${CHANTAGE_BUILD_BIN}"
    VERBATIM
)

install(
    FILES
    "${CHANTAGE_BUILD_BIN}/chantage_loader.bin"
    DESTINATION
    "${CHANTAGE_PSP_PREFIX}"
)


