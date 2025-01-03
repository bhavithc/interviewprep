### Semaphore - Type (synchronization)

- semaphore is a special variable on which only two operations are allowed
  - wait 
  - signal
- P(semaphore variable) for wait
- V(semaphore variable) for signal

two operations are then defined as follows 
|||
|-|-|
|P(sv) | If sv is greater than zero, decrement sv. If sv is zero, suspend execution of process |
|V(sv) | if some other process has been suspended waiting for sv, make it resume execution. if no process is suspended waiting for sv, increment sv|

- All Linux semaphore functions operate on arrays of general semaphores rather than a single semaphore. In complex cases, where a process needs to lock multiple resources, the abbility to operate on an array of semaphores is very big advantage 


syntax:
```
int semget(key_t key, int nsems, int flag);
return: semId on success or -1 on failure 
- key: key for two process
- nsems: number of semaphore required
- flag: flag
    - lower 9 bits: permission of the semaphore to be created
    - lower 9 bits ORed with value IPC_CREAT to create new semaphore
        - if IPC_CREAT is used for an existing semaphore, this flag is just ignored.
    - lower 9 bits ORed with value IPC_EXCL and IPC_CREAR to ensure new semaphore is being created - semget function reutn error is the semaphore already exists
```

```
int semop(int semid, struct sembuf* sem_ops, size_t nops);
return: 0 on success and -1 on failure
- semId: semaphore id
- sem_ops: pointer to array of struct, each of will have at least three members

struct sembuf {
    short sem_num; // -semaphore number, which is usually 0,
    short sem_op; // value by which semaphore should be changed, -1 or +1 in case of binary semaphore
    short sem_flg; // flag set to SEM_UNDO
};
```
```
int semclt (int semid, int semnum, int cmd, ...);
return: 0 on success and -1 on failure
- semid: semaphore id obtained from semget
- semnum: semaphore number (it is 0 for the first and only semaphore)
- cmd: action to take and the next paramrter is a union semun
union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
}
cmd can be:
- IPC_STAT
- IPC_SET
- IPC_RMID
```

example:
```

```
| IPC Mechanism | Namespace (to identify the IPC object) | Handle used to refer to object in program | Accesiblity | Persistence |
|-|-|-|-|-|
| SysV semaphore | SysV IPC key | Sys V IP identifier | permission mask | kernel |
| POSIX named semaphore | POSIX IPC pathname | sem_t* (semaphore pointer) | permission mask | kernel |
| POSIX unnamed semaphore | no name | sem_t* (semaphore pointer) | permission of underlying memory | depends |

