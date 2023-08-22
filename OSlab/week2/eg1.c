// A Directory-Scanning Program
// Start with the appropriate headers and then a function, printdir , which prints out the
// current directory. It will recurse for subdirectories using the depth parameter for
// indentation.


#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void printdir(char *dir, int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr,"cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);

		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but ignore . and .. */
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			printf("%*s%s/\n",depth,"",entry->d_name);

			/* Recurse at a new indent level */
			printdir(entry->d_name,depth+2);
		}
		else printf("%*s%s\n",depth,"",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

int main(){
	printdir("/home/Student/Documents",3);
	return 0;
}



// struct dirent {
//     ino_t          d_ino;       /* inode number */
//     off_t          d_off;       /* offset to the next dirent */
//     unsigned short d_reclen;    /* length of this record */
//     unsigned char  d_type;      /* type of file; not supported
//                                    by all file system types */
//     char           d_name[256]; /* filename */
// };


// The POSIX library header <sys/stat.h>, found on all POSIX-compliant and Unix-like operating systems, declares the stat(), fstat(), and lstat() routines:
//  int stat(const char *filename, struct stat *buf);
//  int lstat(const char *filename, struct stat *buf);
//  int fstat(int filedesc, struct stat *buf);

// struct stat{
// 	 dev_t       st_dev;     /* ID of device containing file */
// 	 ino_t       st_ino;     /* inode number */
// 	 mode_t      st_mode;    /* protection */
// 	 nlink_t     st_nlink;   /* number of hard links */
// 	 uid_t       st_uid;     /* user ID of owner */
// 	 gid_t       st_gid;     /* group ID of owner */
// 	 dev_t       st_rdev;    /* device ID (if special file) */
// 	 off_t       st_size;    /* total size, in bytes */
// 	 time_t      st_atime;   /* time of last access */
// 	 time_t      st_mtime;   /* time of last modification */
// 	 time_t      st_ctime;   /* time of last status change */
// 	 blksize_t   st_blksize; /* blocksize for filesystem I/O */
// 	 blkcnt_t    st_blocks;  /* number of blocks allocated */
// }

// lstat() is a library function that retrieves the status of a file. 
// It is identical to stat(), except when the file is a symbolic link, 
// in which case information about the link itself is returned instead of the linked-to file. 

