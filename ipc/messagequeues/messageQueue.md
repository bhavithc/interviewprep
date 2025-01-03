### System V message queue - Type (message)

- It is similar to pipe but without complexity of opening or closing the pipes
- Exchange data between two unrelates process
- Advantage over pipe is message queue is independent of both the sending and receving processes, this avoid difficulty that occur synchronizing the opening and closing of named pipes
- The priority of the messages can be sent or received can be set 
- When queue is created it will remain there unless or until we remove it using msgctl with IPC_RMID
- if we leave, then we can reuse the queue
- Key can be either static or dynamic 
  - static key is like hardcoding 1234 in both sender and recevier
  - dynamic key is by generating using file path and project id\
    example: project id: A, filepath: /tmp/msgqueue\
    then use ftok -> file to token function \
    `key = ftok(path, id)` -> `key = ftok("/tmp/msgqueue", `A`);`

syntax:

```
int msgget(key_t key, int msgflg);
return +ve nr (msgId) on success or -1 on failure
- key: unique number
- msgflag: IPC_CREAT | 0664
```

```
int msgctl(int msgId, int cmd, struct msgid_ds* buf);
return 0 on success and -1 on failure
- msgId: message id 
- cmd: 
```

```
int msgrcv(int msgId, void* msg, size_t msg_size, long int msgtype, int msgflg);
returns number of bytes placed in the receive buffer on success or -1 on failure
- msgId: message id 
- msg: message pointer
- msg_size: size of the buffer
- msgType:
    - 0     : first message in the queue is received
    - > 0   : first message with the same message type in the queue is received
    - < 0   : first message with same value of less than the absolute value of msgType is received
```

```
int msgsnd(int msgId, const void* msg, size_t msg_size, int mgflg);
return 0 on success or -1 on failure 
```

example:
```
```

| IPC Mechanism | Namespace (to identify the IPC object) | Handle used to refer to object in program | Accesiblity | Persistence |
|-|-|-|-|-|
| SysV message queue | SysV IPC key | SysV IPC identifier | permission mask  | kernel |
| POSIX message queue | POSIX IPC path | mqd_t (MQ descriptor) | permission mask | kernel |


### How can we debug the message queue 

There are two types of message queues 
- SysV message queue
- POSIX message queue 

**for SysV ipc execute**

print all ipcs 
```
$ ipcs -a
```

print only message queue
```
$ ipcs -q
```

programatically if you want to print, then use msgctl

**for POSIX ips**
```
ls /dev/mqueue
```

## Clearning message queque 

### sys v 
```
$ ipcrm -q <msgid>
```
or 

programatically using msgctl with `IPC_RMID`

### Posix 
programatically using `mq_unlink(queue_name)`


