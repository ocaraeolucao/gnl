*This project has been created as part of the 42 curriculum by luvieira.*

## Description
The `get_next_line` (GNL) project is a custom C function that reads a line from a file descriptor (fd). Repeated calls to this function allow you to read a text file one line at a time, until the End Of File (EOF) is reached. 

This project introduces core concepts of C programming, such as **Static Variables**, **File Descriptors**, and **Dynamic Memory Allocation**, while strictly enforcing the prevention of memory leaks.

## Instructions
### Integration into your project
To compile the library, you need a standard C compiler (such as `gcc` or `cc`).

Clone the repository or copy the files: get_next_line.c, get_next_line_utils.c, and get_next_line.h.

Include the header in your C file: 

`#include "get_next_line.h"`

### Compilation

The project must be compiled with the -D BUFFER_SIZE=n flag, which defines the byte size read by the read() function in each iteration.

`gcc -Wall -Wextra -Werror -D BUFFER_SIZE=n <files>.c -o your_program`

### Usage Example

Create an C file called 'main.c' and include this on the scope:

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;
    int     readed_lines;

    fd = open("test.txt", O_RDONLY);
    
    if (fd == -1)
    {
        printf("Error readind the file.\n");
        return (1);
    }

    readed_lines = 1;
    
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
            
        printf("Line %d: %s", readed_lines, line);
        
        free(line); 
        readed_lines++;
    }

    printf("\n--- End of the file ---\n");
    
    close(fd);
    return (0);
}

Then compile the project linking the created file:

`gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o your_program`

Then include an 'test.txt' file on the root of the project.

## Resources

### Classic References

The C Programming Language (Second Edition) by Brian W. Kernighan and Dennis M. Ritchie.

(https://www.w3schools.com/) - Classic programming and tutorial reference.

(https://github.com/ocaraeolucao/libft) - Useful functions to create this project.

### AI Usage

Task: [e.g., Code review, conceptual explanation, debugging assistance, README formatting].

Project Parts: [e.g., Explaining the concept of static function, file descriptor and dynamic memory allocation; generating the initial structure for this README file;].

## Algorithm Explanation & Justification

### The Challenge
The core problem get_next_line solves is the unpredictability of read(). When we call read(fd, buffer, BUFFER_SIZE), it fetches chunks of bytes blindly. A single read chunk might contain:

Exactly one line.

Only a fraction of a line.

Multiple lines at once.

If it reads multiple lines, the function must return the first line immediately, but somehow "remember" the remaining characters for the next time get_next_line is called.

### Selected Algorithm: The "Read, Extract, and Save" Approach
To solve this efficiently, the algorithm relies on a Static Pointer (static char *backup) and follows a strict 3-step pipeline.

* **Read and Accumulate (The Loop)**
The function initializes a temporary buffer using malloc based on the BUFFER_SIZE. It enters a loop that calls read().

After each successful read, the newly read bytes are concatenated (ft_strjoin) with whatever was already stored in the backup static variable.

The loop continues until a newline character (\n) is found inside backup, or until read() returns 0 (EOF).

Justification: This ensures we only perform system calls when necessary. We accumulate just enough data to find at least one complete line.

* **Extract the Line**
Once the loop breaks (meaning we have at least one \n or reached EOF), we isolate the line to be returned.

We iterate through the backup string until we hit the \n.

We malloc a new string of that exact length (plus one for the \n and one for the null-terminator \0).

We copy the characters into this new string. This string is our final line.

Justification: Memory efficiency. We return exactly what was requested, no more, no less, ensuring the caller gets a perfectly formatted string.

* **Update the Static Variable (The Leftovers)**
This is the most crucial step. Since we extracted the first line, we must save the rest of the string for future calls.

We create a new string containing everything in backup that came after the \n.

We free the old backup (to prevent memory leaks).

We point backup to this new "leftovers" string.

Justification: The static variable acts as a persistent state. By saving the remainder, the next time get_next_line is called, it first checks this backup before ever needing to call read() again. This prevents data loss across function calls.

### Edge Cases Handled
**Allocation Failures**: If malloc fails at any point, all temporary buffers and the static variable are immediately freed to prevent memory leaks, and the function returns NULL.

**File Deletion/FD modification**: If read() returns -1 (indicating an error or an invalid fd), the static variable is cleared and freed.

**Empty Files / End of File**: Handled gracefully. If backup is empty and read returns 0, the function cleanly frees memory and returns NULL.