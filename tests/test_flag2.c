/*******************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
/*******************/
enum CMD_IDS {
  CMD_ECHO  = 0,
  CMD_SLEEP = 1,
};
/*******************/
#define COMMANDS           \
  { "echo", cmd_echo, },   \
  { "sleep", cmd_sleep, }, \
/*******************/


static void usage(FILE *f) {
  fprintf(f,
          AC_RESETALL AC_MAGENTA "usage: example [-h] "
          AC_RESETALL AC_RED AC_BOLD "<%s|%s>"
          AC_RESETALL AC_MAGENTA " [OPTION]..."
          AC_RESETALL "\n",
          "echo",
          "sleep"
          );
}


static int cmd_sleep(char **argv){
  int             i, option;
  struct optparse options;

  optparse_init(&options, argv);
  while ((option = optparse(&options, "h")) != -1) {
    switch (option) {
    case 'h':
      puts("usage: sleep [-h] [NUMBER]...");
      return(0);

    case '?':
      log_error("%s: %s\n", argv[0], options.errmsg);
      return(1);
    }
  }

  for (i = 0; argv[i]; i++) {
    if (sleep(atoi(argv[i]))) {
      return(1);
    }
  }
  return(0);
}


static int cmd_echo(char **argv){
  int             i, option;
  bool            newline = true;
  struct optparse options;

  optparse_init(&options, argv);
  options.permute = 0;
  while ((option = optparse(&options, "hn")) != -1) {
    switch (option) {
    case 'h':
      puts("usage: echo [-hn] [ARG]...");
      return(0);

    case 'n':
      log_debug("NEWLINE DISABLED");
      newline = false;
      break;
    case '?':
      log_error("%s: %s\n", argv[0], options.errmsg);
      return(1);
    }
  }
  argv += options.optind;

  for (i = 0; argv[i]; i++) {
    log_info(AC_RESETALL AC_BLUE AC_REVERSED AC_BOLD "%s%s" AC_RESETALL, i  ? " " : "", argv[i]);
  }
  if (newline) {
    log_debug("Adding Newline!");
    putchar('\n');
  }else{
    log_debug("Skipping Newline!");
  }

  fflush(stdout);
  return(!!ferror(stdout));
}
/*******************/
static const struct {
  char name[8];
  int  (*cmd)(char **);
} cmds[] = {
  COMMANDS
};


/*******************/


int parse_opts(int argc, const char **argv) {
  flag_int(&requests, "requests", "Number of total requests");
  flag_int(&concurrency, "concurrency", "Number of concurrent requests");
  flag_str(&url, "url", "Target url");
  flag_parse(argc, argv, VERSION);

  log_info("     requests: %d", requests);
  log_info("  concurrency: %d", concurrency);
  log_info("          url: %s", url);

  dbg(url, % s);
  dbg(requests, % d);
  dbg(concurrency, % d);

  log_debug("OK");
  return(0);
}


int main(int argc, char **argv){
  log_info("OK");
  dbg(argc, % d);
  int             i, option;
  char            **subargv;
  struct optparse options;

  int             ncmds = sizeof(cmds) / sizeof(*cmds);

  (void)argc;
  optparse_init(&options, argv);
  options.permute = 0;
  while ((option = optparse(&options, "h")) != -1) {
    switch (option) {
    case 'h':
      usage(stdout);
      return(0);

    case '?':
      usage(stderr);
      log_error("%s: %s\n", argv[0], options.errmsg);
      return(1);
    }
  }

  subargv = argv + options.optind;
  if (!subargv[0]) {
    log_error("%s: missing subcommand\n", argv[0]);
    usage(stderr);
    return(1);
  }

  for (i = 0; i < ncmds; i++) {
    if (!strcmp(cmds[i].name, subargv[0])) {
      int res = cmds[i].cmd(subargv);
      log_debug("res:%d|name:%s|i:%d", res, cmds[i].name, i);
      log_debug("OK");
      dbg(argc, % d);
      return(parse_opts(argc, argv));
    }
  }
  log_error("%s: invalid subcommand: %s\n", argv[0], subargv[0]);
} /* main */
