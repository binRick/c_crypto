/***********************************/
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL    LOG_TRACE
#endif
/***********************************/
#include <stdio.h>
/***********************************/
#include "../include/module.h"
/***********************************/
/***********************************/
/***********************************/
/***********************************/
const char *DEFAULT_KEY = "0123456789abcdef";
/***********************************/

/****************************************************************************************************/
#define PRIVATE_AES_MODULE_PROPERTIES \
  void *private;                      \
  aes_key128_t key;                   \
  char         *k;                    \
  aes_ctx_t    aes;                   \
  uint8_t      *cipher, *plain;       \
  size_t       cipher_len, plain_len; \
/****************************************************************************************************/
#define PUBLIC_AES_MODULE_PROPERTIES                                                                 \
  bool (*setkey)(char *);                                                                            \
  void (*setrandomkey)();                                                                            \
  char *(*getkey)();                                                                                 \
  size_t (*getkeylen)();                                                                             \
  void (*decrypt)();                                                                                 \
  uint8_t *(*encrypt)(aes_ctx_t * aes_ctx, const uint8_t *plain, size_t plain_len, size_t *enc_len); \
/****************************************************************************************************/


///////////////////////////////////
// `crypto_module` module definition
///////////////////////////////////
module(crypto_module) {
  defaults(crypto_module, CLIB_MODULE);
  PRIVATE_AES_MODULE_PROPERTIES
    PUBLIC_AES_MODULE_PROPERTIES
};
///////////////////////////////////

///////////////////////////////////
// `crypto_module` module prototypes
///////////////////////////////////
static int  crypto_module_init(module(crypto_module) * exports);
static void crypto_module_deinit(module(crypto_module) * exports);
///////////////////////////////////

///////////////////////////////////
// `crypto_module` module exports
///////////////////////////////////
exports(crypto_module) {
  .init   = crypto_module_init,
  .deinit = crypto_module_deinit,
};
///////////////////////////////////

///////////////////////////////////
// `private` module definition
///////////////////////////////////
module(private) {
  define(private, CLIB_MODULE);

  PUBLIC_AES_MODULE_PROPERTIES
};


static bool crypto_module_private_setkey(char *key){
  log_trace("crypto_module_private_setkey:%s", key);
  bool res = true;

  return(res);
}


static char * crypto_module_private_getkey(){
  log_trace("crypto_module_private_getkey");
  char *res = "OK";

  return(strdup(res));
}

// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .getkey = crypto_module_private_getkey,
  .setkey = crypto_module_private_setkey,
};


static bool crypto_module_setkey(char *key){
  log_trace("crypto_module_setkey:%s", key);
  return(require(private)->setkey(key));
}


static char * crypto_module_getkey(){
  log_trace("crypto_module_getkey");
  return(require(private)->getkey());
}


// `crypto_module` module initializer
static int crypto_module_init(module(crypto_module) *exports) {
  void debug_private(){
    if (0 != exports->private) {
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_YELLOW "init> NON PRIVATE MODE" AC_RESETALL);
    }else{
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_BLUE "init> PRIVATE MODE" AC_RESETALL);
    }
  }

/****************************************/
  debug_private();
/****************************************/
  exports->getkey  = crypto_module_getkey;
  exports->setkey  = crypto_module_setkey;
  exports->private = require(private);

  require(private)->setkey(DEFAULT_KEY);
  log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_MAGENTA "private key:%s", AC_RESETALL, exports->getkey());
/****************************************/
  debug_private();
/****************************************/


  return(0);
}


// `crypto_module` module deinitializer
static void crypto_module_deinit(module(crypto_module) *exports) {
  log_trace("crypto_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

