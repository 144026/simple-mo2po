project('simple-mo2po', 'c',
  version : '0.3.0',
  default_options : ['warning_level=3'])

subdir('src')

exe = executable('mo2po',
  srcs,
  install : true)

# run tests
subdir('tests')

