#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

//stack-----------------------------------------------

//void func() {
//    int arr[4096];
//    printf("Stack address: %p\n", (void*)arr);
//    sleep(1);
//    func();
//}

//heap------------------------------------------------------

//void func() {
//    for (int i = 0; i < 10; i++) {
//        int* ptr = malloc(sizeof(int) * 1024 * 500);
//        printf("Heap address: %p\n", ptr);
//        sleep(1);
////        free(ptr);
//    }
//}

//mmap ANONYMOUS-------------------------------------------------

void func() {
    size_t size = 10 * sysconf(_SC_PAGESIZE);
    int fd = open("example.dat", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, size);
    char* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    printf("Mapped shared memory address: %p\n", addr);
    strcpy((char*)addr, "Hello");
    addr[0] = 'X';
    sleep(7);
    munmap(addr, size);
    close(fd);
}

//mmap change rights---------------------------------------------------------

//void segfault_handler(int signum) {
//    printf("Caught SIGSEGV (Segmentation Fault)!\n");
//    exit(EXIT_FAILURE);
//}
//
//void func() {
//    signal(SIGSEGV, segfault_handler);
//    size_t size = 10 * sysconf(_SC_PAGESIZE);
//    void *mapped_memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//    printf("Mapped memory address: %p\n", mapped_memory);
//    mprotect(mapped_memory, size, PROT_WRITE);
//    int value = *((int *)mapped_memory);
//    mprotect(mapped_memory, size, PROT_READ);
//    *((int *)mapped_memory) = 42;
//    munmap(mapped_memory, size);
//}

//mmap detach the page----------------------------------------------------------

//void func() {
//    size_t size = 10 * sysconf(_SC_PAGESIZE);
//    void *mapped_memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//    printf("Mapped memory address: %p\n", mapped_memory);
//    sleep(5);
//    void *region_to_unmap = (char *) mapped_memory + 4 * sysconf(_SC_PAGESIZE);
//    size_t unmap_size = 3 * sysconf(_SC_PAGESIZE);
//    munmap(region_to_unmap, unmap_size);
//    printf("detach the page completed\n");
//    sleep(15);
//}

int main() {
    printf("PID: %d\n", getpid());
    sleep(15);
    func();
    return 0;
}