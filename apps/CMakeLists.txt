add_executable(main main.cpp)
target_link_libraries(
    main
    PRIVATE
        tuple
        color
        matrix
        matrix_transformations
        ray_sphere_intersections
        canvas
)
