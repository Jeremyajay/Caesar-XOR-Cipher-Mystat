// Jeremy Cuthbert
// CS333 - Jesse Chaney
// cae-xor.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define OPTIONS "edc:x:hD"

int main(int argc, char *argv[])
{
  char *cae_string = NULL;
  char *xor_string = NULL;
  bool encrypt = true; // change this value based on the command line (-e or -d)

  {
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS) != -1) {
      switch (opt) {
      case 'e':
	
	break;
      case 'd':

	break;
      case 'c':

	break;
      case 'x':

	break;
      case 'h':

	break;
      case 'D':

	break;
      default:
	fprintf(stderr, "unknown option %c\n", optopt);
	exit(EXIT_FAILURE);
	break;
      }
    }
  }
  
  return EXIT_SUCCESS;
}
