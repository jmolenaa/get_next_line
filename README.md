The goal of this project was to write a function that takes a file descriptor and returns a pointer to a string containing the first line of the file. Consecutive calls to the function return the next lines form the file.\
The function also works for multiple open file descriptors and it can read from standard input.\
Remember that the pointer returned is allocated on the heap so free when neccesary.\
I've created three versions of the funciton that use different ways of reading the line.\
Strjoin uses a standard joining of read buffers to create the returned pointer.\
Strdoublearray stores all buffers read in an array and then concatenates them at the end.\
Strlist uses a list to store all buffers read and then concatenates them.\
Compile the get_next_line.c and get_next_line_utils.c with any other program and call get_next_line(fd) to use the function.
