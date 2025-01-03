### Pipe - Type (Byte stream)

- Pipe are unidirectional (half duplex)
- Create a pipe before fork
- For bidirectional use two pipes 
- 0 is read end
- 1 is write end 

syntax:
```
int pipe(int fd[2]);
```
return 0 on success or -1 on failure 

example:
```
int fd[2] = {-1, -1};
if (pipe(fd) < 0) {
    perror("Failed\n");
} else {
    printf("success\n");
}
```
| IPC Mechanism | Namespace (to identify the IPC object) | Handle used to refer to object in program | Accesiblity | Persistence |
|-|-|-|-|-|
| (Unamed) pipe | No name | file desctriptor | related process only | process |

> `popen()` and `pclose()`

syntax:
```
FILE* popen(const char* cmdString, const char* type);
```
type:
    "r" - File pointer connected to standard input
    "w" - File pointer connected to standard output
    
return file pointer on success or -1 on failure 

```
int pclose(FILE* fp);
```
return termination status on success or -1 on failure

The standard I/O library provides us two functions `popen` and `pclose` which help in creating a pipe, forking a child process, closing the unused ends of pipe, executing the shell to run a command and waiting for the command to terminated.

