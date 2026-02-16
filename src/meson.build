tuple = static_library(
  'tuple',
  'tuple.cpp',
)

color = static_library(
  'color',
  'color.cpp',
)

canvas = static_library(
  'canvas',
  'canvas.cpp',
  link_with: color,
)

matrix = static_library(
  'matrix',
  'matrix.cpp',
  link_with: tuple,
)

matrix_transformations = static_library(
  'matrix_transformations',
  'matrix_transformations.cpp',
  link_with: matrix,
)

light_and_shading = static_library(
  'light_and_shading',
  'light_and_shading.cpp',
  link_with: [
    color,
    tuple,
    matrix,
    matrix_transformations,
  ],
)

ray_sphere_intersections = static_library(
  'ray_sphere_intersections',
  'ray_sphere_intersections.cpp',
  link_with: [
    light_and_shading,
    matrix,
    matrix_transformations,
  ],
)
