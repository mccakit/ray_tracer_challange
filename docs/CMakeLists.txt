add_custom_target(
    doc
    ALL
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/doxygen doxygen Doxyfile
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/sphinx sphinx-build source build
)
