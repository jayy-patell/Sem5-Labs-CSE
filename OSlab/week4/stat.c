//Program that uses stat() to retrieve the size of a file provided on the command line:

/* Filename: stat.c */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
struct stat sb;
int ret;
if (argc < 2) {
fprintf (stderr, "usage: %s <file>\n", argv[0]);
return 1;
}
ret = stat (argv[1], &sb);
if (ret) {
perror ("stat");
return 1;
}
printf ("%s is %ld bytes\n", argv[1], sb.st_size);
return 0;
}


/* 
int stat (const char *path, struct stat *buf);
int fstat (int fd, struct stat *buf);
int lstat (const char *path, struct stat *buf);

Each of these functions returns information about a file.
->stat() returns information about the file denoted by the path, while fstat() returns
information about the file represented by the file descriptor fd.
->lstat() is identical to stat(), except that in the case of a symbolic link, lstat() returns
information about the link itself and not the target file. 
*/


// struct stat {
//     dev_t st_dev; /* ID of device containing file */
//     ino_t st_ino; /* inode number */
//     mode_t st_mode; /* permissions */
//     nlink_t st_nlink; /* number of hard links */
//     uid_t st_uid; /* user ID of owner */
//     gid_t st_gid; /* group ID of owner */
//     dev_t st_rdev; /* device ID (if special file) */
//     off_t st_size; /* total size in bytes */
//     blksize_t st_blksize; /* blocksize for filesystem I/O */
//     blkcnt_t st_blocks; /* number of blocks allocated */
//     time_t st_atime; /* last access time */
//     time_t st_mtime; /* last modification time */
//     time_t st_ctime; /* last status change time */
// };