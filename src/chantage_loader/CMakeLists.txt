file(GLOB_RECURSE SOURCES "*.c" "*.S")
add_executable(chantage_loader_elf ${SOURCES})
target_link_libraries(chantage_loader_elf libprx libchantage)
set_target_properties(
    chantage_loader_elf
    PROPERTIES
    LINK_FLAGS
    "-lgcc -T${CMAKE_SOURCE_DIR}/src/link.ld -Wl,--adjust-vma=0x09000000"
    OUTPUT_NAME
    "chantage_loader.elf"
)

add_custom_command(
    OUTPUT
    "chantage_loader.bin"
    DEPENDS
    chantage_loader_elf
    COMMAND
    "mips-unknown-elf-objcopy"
    "-S"
    "-O"
    "binary"
    "--adjust-vma=0x09000000"
    "$<TARGET_FILE:chantage_loader_elf>"
    "chantage_loader.bin"
    WORKING_DIRECTORY
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    VERBATIM
)

add_custom_target(chantage_loader ALL
    DEPENDS
    "chantage_loader.bin"
    WORKING_DIRECTORY
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    VERBATIM
)
