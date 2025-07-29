add_executable(tuple_test tuple_test.cpp)
target_link_libraries(tuple_test PRIVATE tuple Boost::ut_module)
add_test(NAME tuple_test COMMAND tuple_test)
