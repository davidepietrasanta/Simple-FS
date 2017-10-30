# Simple-FS
A virtual implementation of some of the function of a file System
Coded as the final assignment of the API (Principles of Algorithm Design). SimpleFS is a virtual hierarchic filesystem that simulate some of the basic functions of a real file system.

Purpose:

It is able to keep track of files and folders and support various functions. It work by reading a command-journal from stdin and return on the stdout the outcome of the operations.

It operate under asymptotic time and memory complexity limits imposed by the challenge.

The project in implemented in C99 with only the standard library (libc) and the base runtime.

You can find the full assignment text in Italian [Here](https://github.com/davidepietrasanta/Simple-FS/blob/master/Progetto%202017%20-%20FileSystem.pdf)

More Info:
- Input has to be as  INSTRUCTION /PATH (  create /p/o  )
- Chose "avvio()" if you want to send input from kayboard
- Chose "avvio_file()" if you wanto to send input from file. Remember to change the path in fp

Instructions:
- create -> create a file
- create_dir -> create a directory
- delete -> delete a file or a directory without any son
- delete_r -> delete a file or a directory and all his/her sons
- find -> find files and directories and order them by name
- read -> read the content of a file
- write -> write into a file
- stampa, ls & printf -> print the FS's tree
- exit -> end the program

