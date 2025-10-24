// Jeremy Cuthbert
// cuthbert@pdx.edu
// CS333 - Jesse Chaney
// cae-xor.c

// The purpose of this file is to implement the Caesar-like and XOR
// cipher to encrypt/decrypt any message passed in by the user. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>

// Macros
#define OPTIONS "edc:x:hD"
#define PRINTABLE_START 32
#define PRINTABLE_END 126
#define PRINTABLE_RANGE 95

int main(int argc, char *argv[])
{
  char *cae_cipher = NULL;
  char *xor_cipher = NULL;
  bool encrypt = true; // change this value based on the command line (-e or -d)
  char buffer[1024];
  size_t cae_len;
  size_t xor_len;
  size_t key_index = 0;
  int shift = 0;
  ssize_t bytes_read;
  ssize_t bytes_written;
  unsigned char key_char;
  
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
	// caesar encryption
      case 'c':
	cae_cipher = optarg;
	break;
	// xor encryption
      case 'x':
	xor_cipher = optarg;
	break;
	// Help about command line options
      case 'h':
	printf("Usage: ./cae-xor [options]\n");
	printf("Options:\n");
	printf("  -e          Encrypt (default)\n");
	printf("  -d          Decrypt\n");
	printf("  -c '<key>'  Caesar cipher key\n");
	printf("  -x '<key>'  XOR cipher key\n");
	printf("  -h          Display this help message\n");
	printf("  -D          Diagnostic output (not implemented)\n");
	exit(EXIT_SUCCESS);
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
 
   if (cae_cipher == NULL) {
     cae_cipher = " ";
   }
   if (xor_cipher == NULL) {
     xor_cipher = "";
   }
   cae_len = strlen(cae_cipher);
   xor_len = strlen(xor_cipher);

   if (xor_len > 0 && strcmp(cae_cipher, " ") == 0) {
     // XOR cipher
     key_index = 0;
     while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
       for (ssize_t i = 0; i < bytes_read; i++) {
	 key_char = xor_cipher[key_index % xor_len];
	 buffer[i] ^= key_char;
	 key_index++;
       }
       bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
       if (bytes_written < 0) {
	 perror("write");
	 exit(EXIT_FAILURE);
       }
     }
   }

   else if (cae_len > 0 && xor_len == 0) {
     // Caesar cipher
     key_index = 0;
     while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
       for (ssize_t i = 0; i < bytes_read; i++) {
	 unsigned char c = buffer[i];

	 // Skips non-printable characters like '\n' -> cipher doesn't apply to these
	 if (c < PRINTABLE_START || c > PRINTABLE_END)
	   continue;

         // Determine shift based on the key (ASCII)
	 key_char = cae_cipher[key_index % cae_len];
	 shift = key_char - PRINTABLE_START;

	 // Apply bit shift
	 if (encrypt) {
	   c = PRINTABLE_START + ((c - PRINTABLE_START + shift) % PRINTABLE_RANGE);
	 } else {
	   c = PRINTABLE_START + ((c - PRINTABLE_START - shift + PRINTABLE_RANGE) % PRINTABLE_RANGE);
	 }
	 buffer[i] = c;
	 key_index++;	 
       }
       
       bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
       if (bytes_written < 0) {
	 perror("write");
	 exit(EXIT_FAILURE);
       }
     }
   }
   
   else if (cae_len > 0 && xor_len > 0) {
     // Both ciphers
     ssize_t cae_index = 0;
     ssize_t xor_index = 0;
     while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
       // Caesar first
       if (encrypt) {
	 for (ssize_t i = 0; i < bytes_read; i++) {
	   unsigned char c = buffer[i];
	   if (c >= PRINTABLE_START && c <= PRINTABLE_END) {
	     key_char = cae_cipher[cae_index % cae_len];
	     shift = key_char - PRINTABLE_START;
	     c = PRINTABLE_START + ((c - PRINTABLE_START + shift) % PRINTABLE_RANGE);
	     buffer[i] = c;
	     cae_index++;
	   }
	 }

	 // XOR cipher next
	 for (ssize_t i = 0; i < bytes_read; i++) {
	   key_char = xor_cipher[xor_index % xor_len]; // Determine shift based on the key (hex)
	   buffer[i] ^= key_char; // Apply bit shift -> also applies to non-printable characters
	   xor_index++;
	 }
       }
       else {
	 // Decrypt XOR first
	 for (ssize_t i = 0; i < bytes_read; i++) {
	   key_char = xor_cipher[xor_index % xor_len];
	   buffer[i] ^= key_char;
	   xor_index++;
	 }

	 // Then decrypt Caesar
	 for (ssize_t i = 0; i < bytes_read; i++) {
	   unsigned char c = buffer[i];
	   if (c >= PRINTABLE_START && c <= PRINTABLE_END) {
	     key_char = cae_cipher[cae_index % cae_len];
	     shift = key_char - PRINTABLE_START;
	     c = PRINTABLE_START + ((c - PRINTABLE_START - shift + PRINTABLE_RANGE) % PRINTABLE_RANGE);
	     buffer[i] = c;
	     cae_index++;
	   }
	 }
       }

       bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
       if (bytes_written < 0) {
	 perror("write");
	 exit(EXIT_FAILURE);
       }
     }
   }
 
   return EXIT_SUCCESS;
}
