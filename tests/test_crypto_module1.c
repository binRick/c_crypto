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
  module_pre();
  if (MODULE_EXEC_ENABLED) {
    module_post();
  }
  module_hook();
  module_post();
}


int main(void) {
  init();
  module_lifecycle();
  return(0);
}
/*******************/
