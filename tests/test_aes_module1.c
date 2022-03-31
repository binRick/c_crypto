/*******************/
#include <stdio.h>
#include <string.h>
/*******************/
#define MODULE_TEST_ENABLED    true
#define MODULE_EXEC_ENABLED    false
#define MODULE_TEST_GET_KEY    true
#define MODULE_TEST_SET_KEY    true
#define MODULE_TEST_AES_KEY    "0123456789abcde1"
#define MODULE_LOG_LEVEL       LOG_TRACE
/*******************/
#include "include/module.h"
/*******************/
#include "log/log.c"
/*******************/
#include "src/aes_module.c"
/*******************/
#define DEFAULT_CRYPTO_AES_KEY    "0123456789abcdef"
/*******************/
#define LOG                       log_debug
#define LOG_AES_STYLE             AC_RESETALL AC_REVERSED AC_BLUE AC_BOLD
/*******************/
#define set_aes_key               cm_crypto->setkey
#define get_aes_key               cm_crypto->getkey
/*******************/
#define PRINT_AES_KEY()    {                                           \
    char *k = get_aes_key();                                           \
    LOG(LOG_AES_STYLE "%db Current Key:%s" AC_RESETALL, strlen(k), k); \
}                                                                      \
/*******************/
void cm_print_key(){
  PRINT_AES_KEY();
}


void cm_set_key(char *s){
  int res = set_aes_key(s);  LOG(LOG_AES_STYLE "AES Key Set from %db to %db string: %d" AC_RESETALL, strlen(s), strlen(get_aes_key()), res);
}
/*******************/
#define SET_AES_KEY(NEW_KEY)      { \
    cm_set_key(NEW_KEY);            \
}                                   \
/*******************/
#define IF_TEST_EXEC(IF, EXEC)    { \
    if (IF) { EXEC(); }             \
}                                   \
/*******************/
#define POST_MODULE \
  post();           \
/*******************/
#define PRE_MODULE \
  pre();           \
/*******************/
/*******************/
#define MODULE_TEST_SET_KEY_HANDLER()    { \
    SET_AES_KEY(MODULE_TEST_AES_KEY);      \
}                                          \
/*******************/
#define TEST_MODULE                                                \
  if (MODULE_TEST_ENABLED) {                                       \
    test();                                                        \
    IF_TEST_EXEC(MODULE_EXEC_ENABLED, exec)                        \
    IF_TEST_EXEC(MODULE_TEST_SET_KEY, MODULE_TEST_SET_KEY_HANDLER) \
    IF_TEST_EXEC(MODULE_TEST_GET_KEY, PRINT_AES_KEY)               \
  }                                                                \
/*******************/
////////////////////////////////////////////////////////////////////
//         char * GET_AES_KEY();
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//         int SET_AES_KEY(char *s);
////////////////////////////////////////////////////////////////////
/*******************/
#define MODULE_HOOK                    \
  PRINT_AES_KEY();                     \
  SET_AES_KEY(DEFAULT_CRYPTO_AES_KEY); \
  PRINT_AES_KEY();                     \
/*******************/
#define MODULE_LIFECYCLE \
  PRE_MODULE             \
  MODULE_HOOK            \
  TEST_MODULE            \
  POST_MODULE            \
/*******************/
void init(){
  log_set_level(MODULE_LOG_LEVEL);
}


/*******************/


int main(void) {
  init();
  MODULE_LIFECYCLE
  return(0);
}
/*******************/
