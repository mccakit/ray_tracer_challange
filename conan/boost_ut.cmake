
add_library(ut_module STATIC IMPORTED)
set_target_properties(ut_module PROPERTIES
  IMPORTED_LOCATION "/home/mccakit/dev/conan/p/b/boost91691c87c78f7/p/lib/ut_module.a"
  INTERFACE_COMPILE_OPTIONS "-fprebuilt-module-path=/home/mccakit/dev/conan/p/b/boost91691c87c78f7/p/lib/cxx/bmi"
)
