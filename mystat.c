// Jeremy Cuthbert
// CS333 - Jesse Chaney
// mystat.c

// The purpose of this file is to display the inode meta data
//for each file given on the command line. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

// used for alignment for print formatting
#define LABEL_WIDTH 28
// used for buffer size for formatted time strings
#define TIME_BUFF_SIZE 128
// used for buffer for symbolic link resolution
#define PATH_BUFF_SIZE 1024

// Helper Function Prototypes:
void print_label_str(const char *label, const char *value);
void print_label_int(const char *label, long value);
void print_label_str_int(const char *label, const char *strVal, const char *parenLabel,
			 long numVal);
void print_label_mode(const char *label, const char *modeStr, int modeOctal);
		
// Main method
int main(int argc, char *argv[]) {
  
  return EXIT_SUCCESS;
}

// String output format helper function
void print_label_str(const char *label, const char *value) {
  printf("%-*s%s\n", LABEL_WIDTH, label, value);
}

// Numeric output format helper function
void print_label_int(const char *label, long value) {
  printf("%-*s%ld\n", LABEL_WIDTH, label, value);
}

// Output format containing parenthesis for extra information
void print_label_str_int(const char *label, const char *strVal, const char *parenLabel,
			 long numVal) {
  printf("%-*s%s (%s = %ld)\n", LABEL_WIDTH, label, strVal, parenLabel, numVal);
}

// Mode output format helper function
void print_label_mode(const char *label, const char *modeStr, int modeOctal) {
  printf("%-*s%s (%o in octal)\n", LABEL_WIDTH, label, modeStr, modeOctal);
}

