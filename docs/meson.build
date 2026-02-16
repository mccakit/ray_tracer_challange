doxygen = find_program('doxygen')
sphinx  = find_program('sphinx-build')

run_target('doc',
  command : [
    find_program('sh'), '-c',
    'cd "@0@" && "@1@" Doxyfile > /dev/null 2>&1 && cd "@2@" && "@3@" source build > /dev/null 2>&1'.format(
      meson.current_source_dir() / 'doxygen', doxygen.full_path(),
      meson.current_source_dir() / 'sphinx',  sphinx.full_path()
    )
  ]
)
