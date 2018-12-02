cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake")

option(INSTALL_PPF "Bundle the chantage PPF" OFF)

project(chantage C ASM)
include_directories(src include)
add_subdirectory(src)
add_subdirectory(example)

# Generate mods.txt
file(WRITE "${CMAKE_BINARY_DIR}/mods.txt" "")
foreach(mod ${CHANTAGE_MODS})
    file(APPEND "${CMAKE_BINARY_DIR}/mods.txt" "${mod}\n")
endforeach()

install(
    FILES
    "${CMAKE_BINARY_DIR}/mods.txt"
    DESTINATION
    "${CHANTAGE_PSP_PREFIX}"
)

if (INSTALL_PPF)
    install(
        FILES
        "${CMAKE_SOURCE_DIR}/chantage.ppf"
        DESTINATION
        "."
    )
endif()
