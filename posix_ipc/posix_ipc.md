# POSIX.1b IPC

| interface | Message queues | Semaphores  | Shared memory |
|-|-|-|-|
|Header file | <mqueue.h> | <semaphore.h> | <sys/mman.h> | 
|Object handle | `mqd_t` | `sem_t*` | `int(file descriptor)`|
|Create/open | mq_open() | sem_open() | shm_open() + mmap() | 
|Close | mq_close() | sem_close() | munmap() | 
|Unlink | mq_unlink() | sem_unlink() | shm_unlink()|
|Perform IPC | mq_send(), mq_receive() | sem_post(), sem_wait(), sem_getvalue()| operate on locations in shared memory|
|Miscellaneous operations | mq_setattribute()  - set attributes, mq_getattribute() - get attributes, mq_notify() - request notification | sem_init() - initialize unnamed semaphore, sem_destroy() - destroy unnamed semaphore | (none)

- All the above is called **IPC object** and each should have some name to identify
  - Create an object and return handle
  - Open an object and return handle
- Program must be linked with `-lrt` realtime library
