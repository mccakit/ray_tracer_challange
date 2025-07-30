add_custom_target(
    doc
    ALL
    COMMAND doxygen ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile
    COMMAND sphinx-build ${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source ${CMAKE_CURRENT_SOURCE_DIR}//sphinx/build
)
