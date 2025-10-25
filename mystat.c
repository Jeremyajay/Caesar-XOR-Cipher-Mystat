// Jeremy Cuthbert
// cuthbert@pdx.edu
// CS333 - Jesse Chaney
// mystat.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define TIME_BUFF_SIZE 128
#define LINK_BUFF_SIZE 512

/* Function prototype */
void build_permission_string(mode_t mode, char *perms);

int main(int argc, char *argv[]) {
    int i;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [file...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat sb;
        struct passwd *user;
        struct group *grp;
        char perms[11];
        char time_buf[TIME_BUFF_SIZE];
        struct tm *tm_info;

        /* Use lstat to get info about the link itself, not what it points to */
        if (lstat(filename, &sb) < 0) {
            fprintf(stderr, "Error accessing %s: %s\n", filename, strerror(errno));
            continue;
        }

        /* Print filename - NO leading spaces */
        printf("File: %s\n", filename);

        /* Print file type */
        printf("  File type:                ");
        if (S_ISLNK(sb.st_mode)) {
            char link_target[LINK_BUFF_SIZE];
            ssize_t len;
            struct stat target_stat;
            
            len = readlink(filename, link_target, sizeof(link_target) - 1);
            if (len >= 0) {
                link_target[len] = '\0';
                /* Check if the target exists */
                if (stat(filename, &target_stat) < 0) {
                    printf("Symbolic link - with dangling destination\n");
                } else {
                    printf("Symbolic link -> %s\n", link_target);
                }
            } else {
                printf("Symbolic link\n");
            }
        } else if (S_ISREG(sb.st_mode)) {
            printf("regular file\n");
        } else if (S_ISDIR(sb.st_mode)) {
            printf("directory\n");
        } else if (S_ISCHR(sb.st_mode)) {
            printf("character device\n");
        } else if (S_ISBLK(sb.st_mode)) {
            printf("block device\n");
        } else if (S_ISFIFO(sb.st_mode)) {
            printf("FIFO/pipe\n");
        } else if (S_ISSOCK(sb.st_mode)) {
            printf("socket\n");
        } else {
            printf("unknown\n");
        }

        /* Device ID - just decimal */
        printf("  Device ID number:         %lu\n", (unsigned long)sb.st_dev);

        /* I-node number */
        printf("  I-node number:            %lu\n", (unsigned long)sb.st_ino);

        /* Mode - symbolic and octal with proper spacing */
        build_permission_string(sb.st_mode, perms);
        printf("  Mode:                     %-18s(%03o in octal)\n", 
               perms, 
               sb.st_mode & 0777);

        /* Link count */
        printf("  Link count:               %lu\n", (unsigned long)sb.st_nlink);

        /* Owner ID with proper spacing */
        user = getpwuid(sb.st_uid);
        if (user != NULL) {
            printf("  Owner Id:                 %-18s(UID = %d)\n", 
                   user->pw_name, sb.st_uid);
        } else {
            printf("  Owner Id:                 %-18s(UID = %d)\n", 
                   "UNKNOWN", sb.st_uid);
        }

        /* Group ID with proper spacing */
        grp = getgrgid(sb.st_gid);
        if (grp != NULL) {
            printf("  Group Id:                 %-18s(GID = %d)\n", 
                   grp->gr_name, sb.st_gid);
        } else {
            printf("  Group Id:                 %-18s(GID = %d)\n", 
                   "UNKNOWN", sb.st_gid);
        }

        /* I/O block size */
        printf("  Preferred I/O block size: %ld bytes\n", (long)sb.st_blksize);

        /* File size */
        printf("  File size:                %ld bytes\n", (long)sb.st_size);

        /* Blocks allocated */
        printf("  Blocks allocated:         %ld\n", (long)sb.st_blocks);

        /* Time values - seconds since epoch with proper spacing */
        printf("  Last file access:         %10ld (seconds since the epoch)\n", 
               (long)sb.st_atime);
        printf("  Last file modification:   %10ld (seconds since the epoch)\n", 
               (long)sb.st_mtime);
        printf("  Last status change:       %10ld (seconds since the epoch)\n", 
               (long)sb.st_ctime);

        /* Time values - local time */
        tm_info = localtime(&sb.st_atime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last file access:         %s (local)\n", time_buf);

        tm_info = localtime(&sb.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last file modification:   %s (local)\n", time_buf);

        tm_info = localtime(&sb.st_ctime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last status change:       %s (local)\n", time_buf);

        /* Time values - GMT */
        tm_info = gmtime(&sb.st_atime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last file access:         %s (GMT)\n", time_buf);

        tm_info = gmtime(&sb.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last file modification:   %s (GMT)\n", time_buf);

        tm_info = gmtime(&sb.st_ctime);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", tm_info);
        printf("  Last status change:       %s (GMT)\n", time_buf);
    }

    return EXIT_SUCCESS;
}

/* Function to build the permission string */
void build_permission_string(mode_t mode, char *perms) {
    perms[0] = S_ISDIR(mode)  ? 'd' :
               S_ISLNK(mode)  ? 'l' :
               S_ISCHR(mode)  ? 'c' :
               S_ISBLK(mode)  ? 'b' :
               S_ISFIFO(mode) ? 'p' :
               S_ISSOCK(mode) ? 's' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
}
