### POSIX Semaphore

- Allow processes and threads to synchornize access to shared resources
- There are two types
  - Named semaphore: represented by name (sem_open), unrelated process can use this name to access semaphore
  - Unamed semaphore: location in a memory is used to represent semaphore, this location must be known to both parties, so typically this memory is present in shared memory in case of two process or heap/global variable in case of thread 
- Posix semaphore is an integer whose value is not permitted to fall below 0. if process attempt to decrease it gets an error

#### Core functions  
- `sem_open`: open or create a semaphore and return handle
- `sem_post(sem)`: increment the semaphore's value
- `sem_wait(sem)`: decrement the semaphore's value
- `sem_getvalue()`: get current value of semaphore
- `sem_close()`: removes the association with opened semaphore
- `sem_unlink()`: removes the semaphore and mark for deletion when all process have closed

### Debug

- increment 
- decrement (further decrement blocks the sem_wait until sem_post)
- `ls /dev/shm` it creates a file like `/dev/shm/sem.<filename>` ex: if name of semaphore is `bhavith` then file looks like `/dev/shm/sem.bhavith` it purely depends on os implementation 
