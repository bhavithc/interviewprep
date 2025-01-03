## Communications
```
/
└── Communication
    ├── data transfer
    │   ├── byte stream
    │   │   ├── pipe
    │   │   ├── fifo
    │   │   └── stream socket
    │   ├── pseudoterminal
    │   └── message
    │       ├── System V message queue
    │       ├── POSIX message queue
    │       └── datagram socket
    └── shared memory
            ├── System V shared memory
            ├── POSIX shared memory
            └── memory mapping
                ├── anonymous mapping
                └── mapped file
```

## Signal 
```
/
└── signal
    ├── standard signal
    └── realtime signal
```

## Synchronization
```
/
└── synchronization
    ├── semaphore
    │   ├── System V semaphore
    │   └── POSIX semaphore
    │       ├── named
    │       └── unamed
    ├── file lock
    │   ├── "record" lock (fcntl())
    │   └── file lock (flock())
    ├── mutex (threads)
    └── conditional variable (threads)
```

ASCII codes are generated using https://www.text-tree-generator.com/
