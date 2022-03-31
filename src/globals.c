#include <stdio.h>
#include <string.h>

/*******************/
module(crypto_module) * cm_crypto;


/*******************/


/*******************/
void module_pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  cm_crypto = require(crypto_module);
}


/*******************/


/*******************/
void module_post(void) {
  log_debug("crypto unload>");
  clib_module_free(cm_crypto);
}


/*******************/


/*******************/
