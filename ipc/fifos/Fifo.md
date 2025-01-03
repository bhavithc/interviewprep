### FIFO - Type (Byte stream)

- FIPOs are unidirectional (half duplex) similar to pipes
- Information can be exchanged between unrelated process
- Data exchange is always in byte stream
- We need to create three program 
  - one of creating fifo (fifo.c) - this can also be done using command mkfifo <myfifo>
  - one for writing to fifo file (writfifo.c)
  - one for reading from fifo file (readerfifo.c)
- When fifo file is create it start with `p` when `ls -la`\
  `prw-rw-r-- 1 bhavith bhavith     0 Dec 25 11:48 myfifo`\
  here `p` stands for fifo file 
- When we write data to fifo, the data goes and sit in kernel buffer and size of the kernel buffer is usually 64KB, but it is determined or changed by file `/proc/sys/fs/pipe-max-size`
```
bhavith@bhavith:~/Bhavith/learn/ipc/fifos$ cat /proc/sys/fs/pipe-max-size
1048576
```
- When the reader does not reads it, then its stays in kernel buffer which can removed only by reading 
  - using program `reader`
  - using command `cat myfifo`
  - using command `cat myfifo > /dev/null`


#### Difference between normal file and fifo 
| # | Normal file | fifo file |
|-|-|-|
|Persistency | data saved in file | data saved in kernel buffer, therefore after writing we cannot see the size of file increasing | 
|persistency | data saved even after read | data removed after read | 
|Access | mutliple process can access concurrently | one writer and reader is required | 
|behavior | acts like file | acts like pipe |
|creation | open, fopen | mkfifo | 
|file type | regular file S_IFREG (metadata) | special type S_IFIFO (metadata)|  

syntax:
```
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char* pathName, mode_t mode);
```
pathName - FIFO make special file with name pathName\
mode - FIFO's permission (modified by umask) (mode & ~umask)\
return 0 on success or -1 on failure 

example:
```
//refer: fifo.c
// reader and writer is same as normal reader and writer
```
| IPC Mechanism | Namespace (to identify the IPC object) | Handle used to refer to object in program | Accesiblity | Persistence |
|-|-|-|-|-|
| (Name pipe) FIFO | pathname | file descriptor | permission mask (unrelated process) | process |

