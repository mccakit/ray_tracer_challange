import boost.ut;
import ray_sphere_intersections;
import tuple;
import matrix;
import matrix_transformations;

auto main() -> int
{
    using namespace boost::ut;
    "Creating and querying a ray"_test = [] {
        tuple::tuple<4> origin{tuple::point(1, 2, 3)};
        tuple::tuple<4> direction{tuple::vector(4, 5, 6)};
        ray_sphere_intersections::ray ray{origin, direction};
        expect(ray.origin == origin and ray.direction == direction);
    };
    "Computing a point from a distance"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(2, 3, 4), tuple::vector(1, 0, 0)};
        expect(ray.position(0) == tuple::point(2, 3, 4));
        expect(ray.position(1) == tuple::point(3, 3, 4));
        expect(ray.position(-1) == tuple::point(1, 3, 4));
        expect(ray.position(2.5) == tuple::point(4.5, 3, 4));
    };
    "A ray intersects a sphere at two points"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(0, 0, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.intersect(ray)[0].time == 4.0 and sphere.intersect(ray)[1].time == 6.0);
    };
    "A ray intersects a sphere at a tangent"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(0, 1, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.intersect(ray)[0].time == 5.0 and sphere.intersect(ray)[1].time == 5.0);
    };
    "A ray misses a sphere"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(0, 2, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.intersect(ray).size() == 0);
    };
    "A ray originates inside a sphere"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(0, 0, 0), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.intersect(ray)[0].time == -1.0 and sphere.intersect(ray)[1].time == 1.0);
    };
    "A sphere is behind a ray"_test = [] {
        ray_sphere_intersections::ray ray{tuple::point(0, 0, 5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.intersect(ray)[0].time == -6.0 and sphere.intersect(ray)[1].time == -4.0);
    };
    "An intersection encapsulates t and object"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection intersection{3.5, s};
        expect(intersection.time == 3.5);
        expect(intersection.object == s);
    };
    "Aggregating intersections"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection i1{1, s};
        ray_sphere_intersections::intersection i2{2, s};
        auto xs{ray_sphere_intersections::intersections(i1, i2)};
        expect(xs[0].time == 1);
        expect(xs[1].time == 2);
    };
    "Intersect sets the object on the intersection"_test = [] {
        ray_sphere_intersections::ray r{tuple::point(0, 0, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere s{0};
        std::vector<ray_sphere_intersections::intersection> xs = s.intersect(r);
        expect(xs.size() == 2);
        expect(xs[0].object == s);
        expect(xs[1].object == s);
    };
    "The hit, when all intersections have positive t"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection i1{1, s};
        ray_sphere_intersections::intersection i2{2, s};
        auto hit = ray_sphere_intersections::hit(i2, i1);
        expect(hit == i1);
    };
    "The hit, when some intersections have negative t"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection i1{-1, s};
        ray_sphere_intersections::intersection i2{1, s};
        auto hit = ray_sphere_intersections::hit(i2, i1);
        expect(hit == i2);
    };

    "The hit, when all intersections have negative t"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection i1{-2, s};
        ray_sphere_intersections::intersection i2{-1, s};
        auto h = ray_sphere_intersections::hit(i2, i1);
        expect(std::nullopt == h);
    };
    "The hit is always the lowest nonnegative intersection"_test = [] {
        ray_sphere_intersections::sphere s{0};
        ray_sphere_intersections::intersection i1{5, s};
        ray_sphere_intersections::intersection i2{7, s};
        ray_sphere_intersections::intersection i3{-3, s};
        ray_sphere_intersections::intersection i4{2, s};
        std::vector<ray_sphere_intersections::intersection> xs{ray_sphere_intersections::intersections(i1, i2, i3, i4)};
        auto h = ray_sphere_intersections::hit(xs);
        expect(h.has_value());
        expect(h.value() == i4);
    };
    "Translating a ray"_test = [] {
        ray_sphere_intersections::ray ray {tuple::point(1, 2, 3),tuple::vector(0, 1, 0)};
        matrix::matrix<4, 4> m {matrix_transformations::translation(3, 4, 5)};
        auto ray2 {ray.transform(m)};
        expect(ray2.origin == tuple::point(4, 6, 8) and ray2.direction == tuple::vector(0, 1, 0));
    };
    "Scaling a ray"_test = [] {
        ray_sphere_intersections::ray r {tuple::point(1, 2, 3), tuple::vector(0, 1, 0)};
        matrix::matrix<4, 4> m {matrix_transformations::scaling(2, 3, 4)};
        auto r2 = r.transform(m);
        expect(r2.origin == tuple::point(2, 6, 12) && r2.direction == tuple::vector(0, 3, 0));
    };
    "A sphere's default transformation"_test = [] {
        ray_sphere_intersections::sphere s{0};
        expect(s.transform == matrix::identity_matrix());
    };

    "Changing a sphere's transformation"_test = [] {
        ray_sphere_intersections::sphere s{0};
        auto t = matrix_transformations::translation(2, 3, 4);
        s.set_transform(t);
        expect(s.transform == t);
    };
    "Intersecting a scaled sphere with a ray"_test = [] {
        ray_sphere_intersections::ray r{tuple::point(0, 0, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere s{1};
        s.set_transform(matrix_transformations::scaling(2, 2, 2));
        auto xs = s.intersect(r);
        expect(xs.size() == 2);
        expect(xs[0].time == 3);
        expect(xs[1].time == 7);
    };
    "Intersecting a translated sphere with a ray"_test = [] {
        ray_sphere_intersections::ray r{tuple::point(0, 0, -5), tuple::vector(0, 0, 1)};
        ray_sphere_intersections::sphere s{2};
        s.set_transform(matrix_transformations::translation(5, 0, 0));
        auto xs = s.intersect(r);
        expect(xs.size() == 0);
    };


}
