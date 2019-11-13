# Samples

The samples in this directory are all misbehaving programs that you
must confine successfully.

# sub1.c

This C file has several problems.

If you call it like this:

```
./sub1
```

It prints out a help message and segfaults immediately.

If you provide arguments like this:

```
./sub1 1 2 3 4 0
```

It enters an infinite loop.

It only terminates correctly when you enter an argument that is 0.

```
./sub1 0
```

# sub2.c

This program is supposed to count the number of digits in the file
passed as the first argument.

However, if no file is passed, it reads from standard input. If no
input is provided, this prevents the program from making further
progress.

```
./sub2 file
```

Will count the number of digits in file. However,

```
./sub2
```

Will cause `sub2` to read from standard input, and wait indefinitely
for input without using the CPU. You can press `CTRL+D` to close
standard input, which will cause it to stop normally.
