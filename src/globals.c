#include <stdio.h>
#include <string.h>

/*******************/
module(crypto_module) * cm_crypto;


/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  cm_crypto = require(crypto_module);
}


/*******************/
void test(void) {
}


/*******************/


/*******************/
void exec(void){
  log_info("crypto exec>");
}


/*******************/


/*******************/
void post(void) {
  log_debug("crypto unload>");
  clib_module_free(cm_crypto);
}


/*******************/


/*******************/
