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
01     LOAD       Load a value in a register
```

For example, when you do
```
$ ./fvm ./bin/hello
10
```
You can check why it can do that with hexdump
```
$ hexdump -C ./bin/hello
00000000  01 00 00 02 00 00 00 0a  00                       |.........|
00000009
```
So we will cut it to understand how does it work :

```
01              is the opcode for LOAD
00 00           is the register
02              is the byt (coding byte)
00 00 00 0a     is the number 10
00              is the opcode for HALT
```
The number (for now and for debugging) will always display the register 0
