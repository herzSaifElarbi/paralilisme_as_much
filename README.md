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
    - pthread_join : wait for thread complet
- Synchronization with Mutexes => synch_mutex.c:
    - pthread_mutex_lock,pthread_mutex_unlock : to control who has access
    - PTHREAD_MUTEX_INITIALIZER: init mutex
- Using Condition Variables => cond_var.c:
    - pthread_cond_wait, pthread_cond_signal: wait for a signal, second notify waiter
- Thread Cancellation and Cleanup => thread_cancel_cleanup.c:
    - pthread_testcancel: cancelation points
    - pthread_cleanup_push, pthread_cleanup_pop: for cleanip 
- Detaching Threads => detach_thread.c:
    - pthread_detach: rsc reclamation