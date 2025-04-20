#include <stdio.h>  // Standard input/output library for functions like printf
#include <mpi.h>    // Message Passing Interface library for parallel programming

int main(int argc, char **argv)
{
	int ierr;  // Integer variable to store error codes returned by MPI functions

	// Initialize the MPI environment
	// This function must be called by all MPI processes before any other MPI calls.
	// It takes the command-line arguments passed to the program.
	ierr = MPI_Init(&argc, &argv);

	// Print "Hello world" from each MPI process
	// Each process running this code will execute this line and print the message.
	printf("Hello world\n");

	// Finalize the MPI environment
	// This function cleans up the MPI resources and should be the last MPI call in the program.
	ierr = MPI_Finalize();

	return 0;  // Indicate successful program execution
}

/*
Explanation:

This is a basic "Hello world" program written using the Message Passing Interface (MPI) library. MPI is a standardized and widely used message-passing system designed for parallel computing. It allows multiple processes to communicate and coordinate their work to solve a problem in parallel.

What does this code do?

1.  **Includes Header Files:**
    * `stdio.h`: Includes standard input/output functions, specifically `printf` used for printing to the console.
    * `mpi.h`: Includes the necessary definitions and functions for using the MPI library.

2.  **`main` Function:**
    * The `main` function is the entry point of the C program. It takes two arguments:
        * `argc`: The number of command-line arguments.
        * `argv`: An array of strings containing the command-line arguments.

3.  **`int ierr;`:**
    * Declares an integer variable `ierr` which is commonly used in MPI programs to store the return codes of MPI functions. This helps in error checking (though this example doesn't explicitly check the return codes).

4.  **`ierr = MPI_Init(&argc, &argv);`:**
    * This is the crucial step that initializes the MPI environment.
    * It sets up the communication infrastructure needed for the MPI processes to interact.
    * It takes pointers to `argc` and `argv`, allowing MPI to potentially process command-line arguments specific to the MPI implementation.

5.  **`printf("Hello world\n");`:**
    * This is a standard C function that prints the string "Hello world" followed by a newline character to the standard output (usually the console).
    * When this MPI program is run with multiple processes, each process will execute this `printf` statement, resulting in multiple "Hello world" messages being printed (one from each process).

6.  **`ierr = MPI_Finalize();`:**
    * This function cleans up the MPI environment. It releases any resources that were allocated during the `MPI_Init` call.
    * It's essential to call `MPI_Finalize` before the program exits to ensure proper shutdown of the MPI communication system.

7.  **`return 0;`:**
    * Indicates that the `main` function has executed successfully.

In essence, when you run this MPI program using a command like `mpirun -np 4 ./hello`, where `mpirun` is the MPI launcher and `-np 4` specifies that you want to run the program on 4 processes, you will see the output: