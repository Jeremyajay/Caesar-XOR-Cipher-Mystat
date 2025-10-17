// Jeremy Cuthbert
// CS333 - Jesse Chaney
// cae-xor.c

// The purpose of this assignment is to implement the Caesar-like and XOR
// cipher to encrypt/decrypt any message passed in by the user. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// Macro for all options user can use on command line
#define OPTIONS "edc:x:hD"

int main(int argc, char *argv[])
{
  char *cae_string = NULL;
  char *xor_string = NULL;
  bool encrypt = true; // change this value based on the command line (-e or -d)

  // This reads/parses the command line input and will perform the respective
  // action based on the option(s) provided by the user via stdin.
  {
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS) != -1) {
      switch (opt) {
	// encrypt (default)
      case 'e':
	
	break;
	// decrypt
      case 'd':

	break;
	// caeser encryption
      case 'c':

	break;
	// xor encryption
      case 'x':

	break;
	// Help about command line options
      case 'h':

	break;
	// Diagnostics about the process (optional)
      case 'D':

	break;
	// Handles incorrect/unknown input on command line
      default:
	fprintf(stderr, "unknown option %c\n", optopt);
	exit(EXIT_FAILURE);
	break;
      }
    }
  }
  
  return EXIT_SUCCESS;
}
