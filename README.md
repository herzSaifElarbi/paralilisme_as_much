# paralilisme_as_much
## PThreads
### basics
- #### def:
lightweight procss sharing memory with other process in same process
- #### pros:
context switching is fast and easy
- #### cons:
race conditionning, memory corruption
### exec:
gcc your_code.c -o output -lpthread
./output
### codes:
- Creating and Joining Threads => create_join_threads.c:
    - pthread_t : threads id
    - pthread_create : start a thread
    - pthread_join : wait for thread complet(tasana 7atan yawsal thread, hna na7ko thred principale)
- Synchronization with Mutexes => synch_mutex.c:
    - pthread_mutex_lock(jaya ki l bab t7abasha),pthread_mutex_unlock : to control who has access
    - PTHREAD_MUTEX_INITIALIZER: init mutex
- Using Condition Variables => cond_var.c:
    - pthread_cond_wait(yasana event 7atan yasra), pthread_cond_signal(tnawadh thread raged): wait for a signal, second notify waiter(but doesn't unlock mutex)
- Thread Cancellation and Cleanup => thread_cancel_cleanup.c:
    - pthread_testcancel: cancelation points
    - pthread_cleanup_push, pthread_cleanup_pop: for cleanip
- Detaching Threads => detach_thread.c:
    - pthread_detach: rsc reclamation

## OpenMP
### basics
- #### def:

- #### pros:

- #### cons:

### exec:
gcc -fopenmp program.c -o program
./output
### codes:
- hello.c:
    - #pragma omp parallel : team of threads each thread excute enclosed block
    - omp_get_thread_num(): traja3 thread id
- 
### remarques:
lscpu | grep -i avx => verify 
mparun => specifie nombre de noeud
apx => tji m3aha 9al
#pragma omp parallel for : Splits the loop across multiple CPU threads.
#pragma omp simd : Uses SIMD vector instructions on a single thread.(AVX)
#pragma omp target teams distribute parallel for map(...) : Sends the loop to the GPU, runs with thousands of threads.