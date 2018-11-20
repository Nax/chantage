file(GLOB_RECURSE SOURCES "*.c" "*.S")
add_library(libchantage STATIC ${SOURCES})
set_target_properties(libchantage PROPERTIES OUTPUT_NAME "chantage")
