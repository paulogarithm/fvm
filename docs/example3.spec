Code                Assembly            Binary

                    @+STDOUT            ...
let a = 3;          LDNUM R0 3          05 00 00 00 00 03
a += 1;             ADDA R0 <num> 1     15 00 04 00 00 00 01

print a;            PUSH R0             ?? 00
                    CALL print          ?? \p \r \i \n \t 00

std.write 1 "a" 1;  PUSHA <num> 1       ?? 04 00 00 00 01
                    PUSHA <toz> "a"     ?? 00 \a 00
                    PUSHA <num> 1       ?? 04 00 00 00 01
                    SYS WRITE           ?? 04

std.exit 3;         PUSHA 4 3           ?? 04 00 00 00 03
                    SYS EXIT            ?? 01
                    HALT                00
