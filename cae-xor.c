// Jeremy Cuthbert
// CS333 - Jesse Chaney
// cae-xor.c

// The purpose of this file is to implement the Caesar-like and XOR
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
  char *cae_cipher = NULL;
  char *xor_cipher = NULL;
  bool encrypt = true; // change this value based on the command line (-e or -d)

  // This reads/parses the command line input and will perform the respective
  // action based on the option(s) provided by the user via stdin.
  {
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
      switch (opt) {
	// encrypt (default)
      case 'e':
	encrypt = true;
	break;
	// decrypt
      case 'd':
	encrypt = false;
	break;
	// caeser encryption
      case 'c':
	cae_cipher = optarg;
	break;
	// xor encryption
      case 'x':
	xor-cipher = optarg;
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
   char input[1024];
   size_t cae_len = strlen(cae_cipher);
   size_t xor_len = strlen(xor_cipher);
   
   return EXIT_SUCCESS;
}
