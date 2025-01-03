### Memory mapping type: shared memory

> Note: Memory mapping is not shared memory, but shared memory is implemented using memory maps 

- `mmap` creates a new memory mapping in a calling process's virtual address space. There are two types of `mmap`
  - File mapping: Two process mapped to some region of the file 
  - anonymous mapping: Two process mapped to some anonymous mapping (virtual file) where contents are initialized to zero
- Mapped area is nothing but a pages 
- `mmap` can occur in two ways
  - when two process map the same region of a file, they share the same pages of physical memory
  - A child process is created by `fork()` inherits copies of its parent mappings, and these mappings refer to the same pages of physical memory as the corresponding mapping in the parent
- Mapping pages are typically not contigous in physical memory, that is the reason we see many mapping entry in `cat /proc/<pid>/maps`

```
/
├── private
│   ├── private file mapping
│   └── private anonymous mapping
└── shared
    ├── shared file mapping
    └── shared anonymous mapping
```

There are four variation of memory map
- private file mapping 
- shared file mapping 
- private anonymous mapping 
- shared anonymour mapping 

In table form
| Visibility of modification | File mapping | Anonymous mapping |
| - | - | - |
| Private | Initializing memory from content of file | Memory allocation | 
| Shared | Memory mapped I/O; sharing memory between process (IPC) | Sharing memory between processes (IPC) |

1. Private file mapping:
   - This is used to initiaze memory from content of the file
   - Example:
     - cat program, just we can map the content of file to virtual address space of process
     - mapping the text segment and data segment of the library, example each process is memory mapped to shared library using memory mapping. This works based on the Copy On Write, ex: a.out is memory mapped to `libc`, `ld-linux-x86` as PROT_READ with MAP_PRIVATE, also a.out can be mapped to other library, as soon as a.out modify the data segment of library seperate page get created private to a.out, i.e. COW kicks in
2. Anonymous file mapping:
   - primary purpose is to allocate new (zero-filled) memory for a process
   - Example: `malloc` employs `mmap` for this purpose when allocating large blocks of memory
**Note: **
- In file mapping `mmap` we need to open the file to get fd and give to `mmap` to map later `fd` can be closed 
- It is advisable to keep it open in case PROT_WRITE with MAP_SHARED is used then writing to memory need file to be opened 
- After write to memory we need `msync` otherwise we may not see the content reflect immediate similar to `fflush` after `fprint`

### Single line comments
- **Private file mapping**: process memory mapping is backed by file, but changes to memory will not reflect to file because as soon as memory is touched, Copy On Write takes place from kernel page by page: eg: mapping shared libraries code/text segment 
- **Private anonymous mapping**: memory is allocated from some where and not backed by file, after fork the parent and child shares the memory but as soon as parent or child access the mapped memory copy on write takes place and data will not be shared: eg: malloc 
- **Shared file mapping**: Mapped memory is backed by file, changes made to the memory will get reflect in file, other process mapped to the same memory can see the changes since it is shared: eg: sysv shared memory with unrelated process
- **Shared anonymous mapping**: Mapped memory is not backed by the file. when process is forked then child shares the same page of the mapped memory. eg: sysv shared memory with related process only 

**syntax**
```
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
return: address on success or MAP_FAILED on failure 
- addr: starting address (recommended to leave as NULL)
- length: length of the memory to be mapped 
- prot: Memory protection
PROT_NONE: The region may not be accessed 
PROT_READ: The content of the region can be read 
PROT_WRITE: The content of the region can be modified 
PROT_EXEC: The content of the region can be executed
Note: memory protection can also be changed using mprotect()
- flag:
MAP_PRIVATE: modification of the contents of the region are not visible to other process employing the same mapping, and, in the case of file mapping, are not carried through underlying file
MAP_SHARED: modification to the content of the region are visible to other process mapping the same region with MAP_SHARED attribute and, in the case of file mapping, are carried through underlying file. Update of file not guarnteed immediate, use msync
MAP_ANONYMOUS:
MAP_FIXED
MAP_LOCKED
...
- fd: file decriptor (file mapped) or -1 (anonymous)
- offset: starting point of the mapping in the file 
```

### Boundary case 

page size:
- 4k - 4096 (default)
- 8k - 8192
- 12k - 

Use case1: `mmap(0, 6000, prot, MAP_SHARED, fd, 0);`
- In above use case 6000 in greater than 4096 (4k page size), since memory is allocated in pages, then it memory region allocated in 8192 not 6000
- |-----------------|-------
- ^           ^     ^     ^  
- 0          5099  8192   |-- accessing outside boundary may lead to SIGSEGV
-             ------
-               |--region is zeroed 

Use case2: `mmap(0, 8192, prot, MAP_SHARED, fd, 0);`
- Here we map the file of file with 2200 bytes
- |-----|-------|-------------|------------~
  0    2199   4095           8191     
-    ^      ^          ^            ^
-    |      |          |            |-- SIGSEGV
-    |      |          |-- SIGBUS (out of file mapping)      
-    |      |--- zeroed 
-    |--- valid access
-    

#### Anonymous mapping

- MAP_PRIVATE anonymous mapping (use /dev/zero): kind of file mapping but not
- MAP_SHARED anonymous mapping (use MAP_SHARED | MAP_ANONYMOUS)