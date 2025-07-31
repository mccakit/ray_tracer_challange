add_library(tuple STATIC)
target_sources(tuple PUBLIC FILE_SET CXX_MODULES FILES tuple.cpp)

add_library(color STATIC)
target_sources(color PUBLIC FILE_SET CXX_MODULES FILES color.cpp)

add_library(canvas STATIC)
target_sources(canvas PUBLIC FILE_SET CXX_MODULES FILES canvas.cpp)
target_link_libraries(canvas PRIVATE color)

add_library(matrix STATIC)
target_sources(matrix PUBLIC FILE_SET CXX_MODULES FILES matrix.cpp)
target_link_libraries(matrix PRIVATE tuple)

add_library(matrix_transformations STATIC)
target_sources(matrix_transformations PUBLIC FILE_SET CXX_MODULES FILES matrix_transformations.cpp)
target_link_libraries(matrix_transformations PRIVATE matrix)
