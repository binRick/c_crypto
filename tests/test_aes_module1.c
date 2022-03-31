/*******************/
#include "include/aes_defaults.h"
#include <stdio.h>
#include <string.h>
/*******************/
#include "include/module.h"
/*******************/
#include "src/aes_functions.c"
#include "src/aes_macros.c"
#include "src/aes_module.c"
#include "src/aes_vars.c"


/*******************/
int main(void) {
  log_set_level(MODULE_LOG_LEVEL);
  MODULE_LIFECYCLE
  return(0);
}
/*******************/
