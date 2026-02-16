boost_ut = dependency(
  'boost_ut',
  method: 'pkg-config',
)

tuple_test_exe = executable(
  'tuple_test',
  'tuple_test.cpp',
  dependencies: boost_ut,
  link_with: tuple,
)
test('tuple_test', tuple_test_exe)

color_test_exe = executable(
  'color_test',
  'color_test.cpp',
  dependencies: boost_ut,
  link_with: color,
)
test('color_test', color_test_exe)

canvas_test_exe = executable(
  'canvas_test',
  'canvas_test.cpp',
  dependencies: boost_ut,
  link_with: canvas,
)
test('canvas_test', canvas_test_exe)

matrix_test_exe = executable(
  'matrix_test',
  'matrix_test.cpp',
  dependencies: boost_ut,
  link_with: matrix,
)
test('matrix_test', matrix_test_exe)

matrix_transformations_test_exe = executable(
  'matrix_transformations_test',
  'matrix_transformations_test.cpp',
  dependencies: boost_ut,
  link_with: matrix_transformations,
)
test('matrix_transformations_test', matrix_transformations_test_exe)

ray_sphere_intersections_test_exe = executable(
  'ray_sphere_intersections_test',
  'ray_sphere_intersections_test.cpp',
  dependencies: boost_ut,
  link_with: ray_sphere_intersections,
)
test('ray_sphere_intersections_test', ray_sphere_intersections_test_exe)

light_and_shading_test_exe = executable(
  'light_and_shading_test',
  'light_and_shading_test.cpp',
  dependencies: boost_ut,
  link_with: [
    light_and_shading,
    ray_sphere_intersections,
  ],
)
test('light_and_shading_test', light_and_shading_test_exe)
