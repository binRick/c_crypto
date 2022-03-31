/*******************/
#include <stdio.h>
#include <string.h>
/*******************/
#define MODULE_TEST_ENABLED    false
#define MODULE_EXEC_ENABLED    false
#define MODULE_LOG_LEVEL       LOG_TRACE
/*******************/
#include "include/module.h"
/*******************/
#include "log/log.c"
/*******************/
#include "src/aes_module.c"
/*******************/


void init(){
  log_set_level(MODULE_LOG_LEVEL);
}


void module_hook(){
  char *cur_key; bool ok;


  void    do_setkey(char *s){
    ok = cm_crypto->setkey(s);
    log_info("key set:%d", ok);
  }


  void    do_getkey(){
    cur_key = cm_crypto->getkey();
    log_info("cur key:%s", cur_key);
  }

  do_getkey();
  do_setkey("0123456789abcdef");
  do_getkey();
} /* module_hook */


/*******************/
void module_lifecycle(){
  pre();
  if (MODULE_TEST_ENABLED) {
    test();
  }
  if (MODULE_EXEC_ENABLED) {
    exec();
  }
  module_hook();
  post();
}


int main(void) {
  init();
  module_lifecycle();
  return(0);
}
/*******************/
