0000 0000 <= 1 byte


1...: custom

0...: prefab
|
+-- 01.. ...: negative
+-- 00.. ...: positive
|
+-- 0?1. ...: the register is the buffer
+-- 0?0. ...: the register is a normal register
|
+-- 0??1 ...: the value is a register (2 bytes)
+-- 0??0 ...: the value is litteral
|
+-- ... 0...: normal values
|   |
|   +-- .000: null (reset)
|   +-- .001: read until \0
|   +-- .010: number (4 bytes) 
|   +-- .011: double (8 bytes)
|   +-- .1..: boolean
|       |
|       +-- ..00: false
|       +-- ..01: true
|   
|
+-- ... 1...: custom values
    |
    +-- .000: buffer value
    +-- .001: register value
    +-- .010: register ref
    |
    +-- .100: table
    +-- .101: status
    +-- .110: function