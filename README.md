<h1 align="center">FVM</h1>

A C Virtual machine who interprets a custom machine language (maybe for a future project...)

<br>

## Requierments

The requirements are:

`make` + `gcc`, or you can only use `docker`

<br>

Working on :
- windows
- linux

<br>

## Build

### Docker ( 👎 not cool people )

Run the `docker/run-win.bat` or `docker/run-linux.sh` file, followed by the args (see bellow)

For example on linux:
```sh
> sh docker/run-linux.sh bin/hello
```

On windows:
```sh
> docker\run-linux.bat bin\hello
```

<br>

### Manually ( 💪 cool people )


First, clone the repository
```sh
> git clone https://github.com/paulogarithm/fvm
```

To compile, do :
```sh
> make
```

<br>

## How to use

You can use the fvm executable with your file:
```sh
> ./fvm bin/hello
```

<br>

Working Opcodes, more details in `docs/new-opcodes.spec`.
```
00     HALT       Stops the program
01     LOAD       Load a value in a register
```

For example, when you do
```sh
> ./fvm ./bin/hello
10
```
You can check why it can do that with hexdump
```sh
> hexdump -C ./bin/hello
00000000  01 00 00 02 00 00 00 0a  00                       |.........|
00000009
```
So we will cut it to understand how does it work :

```t
01              is the opcode for LOAD
00 00           is the register
02              is the byt (coding byte)
00 00 00 0a     is the number 10
00              is the opcode for HALT
```
The number (for now and for debugging) will always display the register 0
