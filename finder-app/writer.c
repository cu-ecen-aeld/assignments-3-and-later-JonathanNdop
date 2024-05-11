#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main (int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Incorrect number of arguments. Usage: writer <file> <string>");
        exit(1);
    }

    // Open the file for writing
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Unable to open file %s for writing", argv[1]);
        exit(1);
    }

    // Write the string to the file
    fprintf(file, "%s", argv[2]);

    // Close the file
    fclose(file);


    // Log the operation
    syslog(LOG_DEBUG, "Writting \"%s\" to %s", argv[2], argv[1]);

    return 0;

}
