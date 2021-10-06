# Libft Project

Libft is a self-written library which contains the most important functions of the C Standard Library (libc). It also contains some other useful functions.

## Description

The function names have the following structure: ft + _ + C Library Function Name. To find information about a function, use the manpages together with the C Library Function Name. All function are compiled with the following options: -Wall -Wextra -Werror. Also the -fsanitize=address (AddressSanitizer) flag is used to ensure no memmory errors are present in the functions. E.g. the AdressSanitizer finds heap, stack and buffer overflows, memmory leaks etc. A _test.c_ script is included which tests most of the functions with different inputs.  

A lot of functions are not part of the C Standard Library. These functions do the following:

* **ft\_substr**:  Allocates (with malloc(3)) and returns a substring from the string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.
* **ft\_strjoin**: Allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of ’s1’ and ’s2’.
* **ft\_strtrim**: Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.
* **ft\_split**: Allocates (with malloc(3)) and returns an array of strings obtained by splitting ’s’ using the character ’c’ as a delimiter. The array ends with a NULL pointer.
* **ft\_itoa**: Allocates (with malloc(3)) and returns a string representing the integer received as an argument.
* **ft\_strmapi**: Applies the function ’f’ to each character of the string ’s’ to create a new string (with malloc(3)) resulting from successive applications of ’f’.
* **ft\_putchar\_fd**: Outputs the character ’c’ to the given file descriptor.
* **ft\_putstr\_fd**: Outputs the string ’s’ to the given file descriptor.
* **ft\_putendl\_fd**: Outputs the string ’s’ to the given file descriptor, followed by a newline.
* **ft\_putnbr\_fd**: Outputs the integer ’n’ to the given file descriptor.

The following functions can be used to create, add and remove elements from a linked list.

* **ft\_lstnew**: Allocates (with malloc(3)) and returns a new element. The variable ’content’ is initialized with the value of the parameter ’content’. The variable ’next’ is initialized to NULL.
* **ft\_lstadd\_front**: Adds the element ’new’ at the beginning of the list.
* **ft\_lstsize**: Counts the number of elements in a list.
* **ft\_lstlast**: Returns the last element of the list.
* **ft\_lstadd_back**: Adds the element ’new’ at the end of the list.
* **ft\_lstdelone**: Takes as a parameter an element and frees the memory of the element’s content using the function ’del’ given as a parameter and free the element. The memory of ’next’ is not freed.
* **ft\_lstclear**: Deletes and frees the given element and every successor of that element, using the function ’del’ and free(3). Finally, the pointer to the list is set to NULL.
* **ft\_lstiter**: Iterates the list ’lst’ and applies the function ’f’ to the content of each element.
* **ft\_lstmap**: Iterates the list ’lst’ and applies the function ’f’ to the content of each element. Creates a new list resulting of the successive applications of the function ’f’. The ’del’ function is used to delete the content of an element if needed.

## Usage

Clone this repository and run 'make' in the command line. This will create the library libft.a with all functions excluding the Linked List functions. To add the Linked List function run 'make bonus'. 
