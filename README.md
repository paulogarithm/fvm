<h1 align="center">FVM</h1>

A C Virtual machine who interprets a custom machine language (maybe for a future project...)

To compile, do :
```sh
$ make
```

Then you can use the fvm with your file:
```sh
$ ./fvm bin/hello
```

<br>

Working Opcodes, more details in `docs/new-opcodes.spec`.
```
00     HALT       Stops the program
01     LD         Load a value in a register
```
