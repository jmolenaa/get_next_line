# Get Next Line

This project involves programming a function called `get_next_line` in C, which reads a line from a file descriptor.  
The function is designed to be highly convenient and employs the concept of static variables in C programming.

## Functionality

The function reads lines from a file descriptor one at a time, and returns the read line as the output. When it encounters the end of the file it will return a NULL pointer.  
It reads BUFFER_SIZE bytes at a time, the default is 10, but it can be changed during compilation by using the -D flag.  
In case of any errors it will return a NULL pointer and set errno to the appropiate error.  
The function doesn't handle opening or closing the file descriptor, it's up to the user to handle this.  
The function can read from standard input if the appropriate file descriptor is passed to it.  
The bonus part allows for reading from multiple file descriptors simultaneously.  

### Usage

Add the two .c files from one of the GNL versions to your compilation and include the header file. Call 'get_next_line' to use the function.  
The function is also added to my [Codam_libft](https://github.com/jmolenaa/Codam_libft)

### My implementation

I've created three versions of the function that use different ways of storing what was already read.  

##### GNL_join - joins what has been read with everything that has been read so far.
##### GNL_doublearray - stores all buffers read in an array and then concatenates them once a newline or EOF has been read.
##### GNL_lists - stores all buffers read in a list and then concatenates them once a newline or EOF has been read.
