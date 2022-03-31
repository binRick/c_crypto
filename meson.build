#//***********************************************************/
project(
    'c_crypto',          ['c'],         version : '0.0.1',         
    default_options : ['warning_level=2','c_std=gnu99'],
)
#//***********************************************************/
host_system = host_machine.system()

cc = meson.get_compiler('c')
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)

#//***********************************************************/
test_deps = []
#//***********************************************************/
incdir = include_directories(
  './include', 
  './deps', 
  '../',
  '../metalang99/include',
  '../ok',
)
#//***********************************************************/
test_flag2 = executable('test_flag2', [ 
    'src/crypto.c', 
    'tests/test_flag2.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_flag1 = executable('test_flag1', [ 
    'src/crypto.c', 
    'tests/test_flag1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_list1 = executable('test_list1', [ 
    'src/crypto.c', 
    'tests/test_list1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_aes1 = executable('test_aes1', [ 
    'src/crypto.c', 
    'tests/test_aes1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_aes_module1 = executable('test_aes_module1', [ 
    'src/crypto.c', 
    'tests/test_aes_module1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_crypto_module1 = executable('test_crypto_module1', [ 
    'src/crypto.c', 
    'tests/test_crypto_module1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
tests = [
  ['test crypto module 1', test_crypto_module1, 'test-crypto-module1.log'],
  ['test crypto aes 1', test_aes1, 'test-aes1.log'],
  ['test aes module 1', test_aes_module1, 'test-aes-module1.log'],
  ['test list module 1', test_list1, 'test-list-module1.log'],
  ['test flag module 1', test_flag1, 'test-flag-module1.log'],
]
flag_tests = [
  ['test flag module 2 echo', test_flag2, ['echo']],
  ['test flag module 2 sleep', test_flag2, ['sleep']],
  ['test flag module 2 echo', test_flag2, ['echo']],
  ['test flag module 2 sleep', test_flag2, ['sleep','--concurrency','2']],
  ['test flag module 2 echo', test_flag2, ['echo','--requests','3']],
  ['flag2 echo help', test_flag2, [
    'echo',
    '-h',
  ]],
  ['flag2 sleep help', test_flag2, [
    'sleep',
    '-h',
  ]],
  ['flag command echo arg -n 12345', test_flag2, [
    'echo','-n','12345',
  ]],
  ['flag command echo 12345', test_flag2, [
    'echo','12345',
  ]],
  ['flag command sleep 5', test_flag2, [
    'sleep','5',
  ]],
  ['flag2 -h', test_flag2, [
    '-h',
  ]],
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
test(i[0], passh, args: ['-L', i[2], i[1] ], env: test_env)
endforeach
#//***********************************************************/
foreach i : flag_tests
test(i[0], i[1], args: i[2], env: test_env)
endforeach
#//***********************************************************/


