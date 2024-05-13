#include "systemcalls.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

   // Call the system function with hte provided command
   int status = system(cmd);

   // Check if the system() call completed successfully
   if (status == 0) {
       // System call completed successfully
       return true;
   }else {
       // System call returned a failure
       return false;
   } 

}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    // Fork a new process
    pid_t pid = fork();

    if (pid == -1){
        // Fork failed
        perror("fork");
        return false;
    } else if (pid == 0) {
        // Child process
        execv(command[0], command);
        // If execv returns, it means an error occured
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        // Child process exited successfully
	return true;
	} else {
	// Child process exited with an error
	return false;
	}
    }

    va_end(args);

}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    // Open the output file in write mode andc obtain its file descriptor
    int output_fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (output_fd == -1){
	perror("open");
        return false;
    }

    // Duplicate the file descriptor of the output file to STDOUT_FILENO (standard output)
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
	perror("dup2");
	close(output_fd);
	return false;
    }

    // Close the original file descriptor of the output file
    close(output_fd);
 
    // Call execv to execute the specified command with its arguments
    execv(command[0], command);

    // If execv returns, it means an error occured
    perror("execv");
    return false;

    va_end(args);

}
