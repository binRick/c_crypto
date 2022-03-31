/*******************/
#include <stdio.h>
#include <stdlib.h>
/*******************/
#include "include/module_imports.h"
/*******************/
#include "src/deps.c"
#define VERSION    "v1.0.0"
/*******************/
int        requests    = 5000;
int        concurrency = 10;
const char *url        = ":3000";
/*******************/


void dev(){
  dbg(123, % d);
}


int main(int argc, const char **argv) {
  flag_int(&requests, "requests", "Number of total requests");
  flag_int(&concurrency, "concurrency", "Number of concurrent requests");
  flag_str(&url, "url", "Target url");
  flag_parse(argc, argv, VERSION);

  log_info("     requests: %d", requests);
  log_info("  concurrency: %d", concurrency);
  log_info("          url: %s", url);
  dbg(url, % s);
  dbg(requests, % d);

  log_debug("OK");
  dev();
  return(0);
}
