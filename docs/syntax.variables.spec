let a = 3
let b = 5
let c = "hello"
let d = true
let e = null

print a         // 3
print a + b     // 8
print b - a     // 2
print a * b     // 15
print a / b     // 0.6
print a ^ b     // 243
print a % b     // 3


a = 3
print a++       // 3
print a         // 4
a = 3
print ++a       // 4

print a & b     // 1 (band)
print a | b     // 7 (bor)
print a ~ b     // 6 (bxor)
print ~ b       // 2 (bnot)

print a and b   // true
print a or b    // true
print a xor b   // false
print not b     // false

print a, b      // 3 5

print a == 3    // true
print a == "3"  // true
print a === "3" // false

print a < b     // true
print a <= b    // true

print a + "hello"   // 3hello
print a + null      // 3
print a + true      // 4
print a + false     // 3

print a * "hello"   // hellohellohello
print a * null      // null
print a * true      // true
print a * false     // false    (false * false = true * false = false)
print 2 * false     // true     (false * false = true)

print 3 - "hello"   // lo
print "hello" - 3   // he


