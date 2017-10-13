#include "common.h"

typedef struct pull_options {
  const char *remote;
  const char *branch;
} pull_options;

static int parse_options(pull_options *opt, int argc, char *argv[]);

int main(int argc, char *argv[]) {
  pull_options opt;
  int last_arg;

  // We need to initialize libgit2
  git_libgit2_init();

  last_arg = parse_options(&opt, argc, argv);

  printf("Remote: %s\n", opt.remote);
  printf("Branch: %s\n", opt.branch);

  // Shut her down!
  git_libgit2_shutdown();

  return 0;
}

/** Print a usage message for the program. */
static void usage(const char *message, const char *arg)
{
	if (message && arg)
		fprintf(stderr, "%s: %s\n", message, arg);
	else if (message)
		fprintf(stderr, "%s\n", message);
	fprintf(stderr, "usage: pull [<options>] [<repository> [<refspec>…​]]\n");
	exit(1);
}

/** Parse some pull command line options. */
static int parse_options(pull_options *opt, int argc, char **argv)
{
  struct args_info args = ARGS_INFO_INIT;

  opt->remote = NULL;
  opt->branch = NULL;

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		const char *a = argv[args.pos];

		if (a[0] != '-') {
			if (!opt->remote)
        opt->remote = a;
      else
        opt->branch = a;
    } else {
      usage("Unsupported argument", a);
    }
	}

	return args.pos;
}

