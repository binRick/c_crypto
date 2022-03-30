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


