#In this file we're mainly configuring all the headers to use the right values
configure_file("${OLYMPUS_SOURCE_DIR}/inc/olympus.hpp.in" "${OLYMPUS_SOURCE_DIR}/inc/olympus.hpp")
configure_file("${OLYMPUS_SOURCE_DIR}/inc/render/shaders.hpp.in" "${OLYMPUS_SOURCE_DIR}/inc/render/shaders.hpp")