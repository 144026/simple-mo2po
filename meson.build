project('simple-mo2po', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3'])

subdir('src')
subdir('trans')

exe = executable('mo2po',
  srcs,
  install : true)

test('basic', exe, args: [mo_file, 'out.po'])
