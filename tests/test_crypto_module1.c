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
#include "src/crypto_module.c"
/*******************/


void init(){
  log_set_level(MODULE_LOG_LEVEL);
}


void module_hook(){
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
