file(GLOB_RECURSE SOURCES "*.c" "*.S")
add_library(libprx STATIC ${SOURCES})
target_link_libraries(libprx libchantage)
set_target_properties(libprx PROPERTIES OUTPUT_NAME "prx")
