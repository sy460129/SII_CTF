from pwn import *
from ctypes import *
# p = process("./prob")
p = remote("15.164.30.24", 10001)

len = 46
arr = [[0 for col in range(len + 1)] for row in range(len + 1)]
# print(p.recv())
for i in range(1, len + 1):
    line = ""
    num = (p.recvline()[:-2]).decode()
    tmp = ['0'] + num.split(" ")
    arr[i] = tmp
    # print(arr[i])

for i in range(1, len + 1):
    for j in range(1, len + 1):
        arr[i] = list(map(int, arr[i]))

# for i in range(1, len + 1):
#     print(arr[i])

ans = [[0 for col in range(len + 1)] for row in range(len + 1)]
for i in range(len, 0, -1):
    for j in range(len, 0, -1):
        ans[i][j] = max(arr[i][j-1], arr[i-1][j]) ^ arr[i][j]

p.recvuntil(b"Your input: ")

for i in range(1, len + 1):
    for j in range(1, len + 1):
        p.send(str(ans[i][j]).encode())
        p.send(b" ")

# p.recvuntil(b"SII{")
# flag = (p.recvuntil(b"}")[:-1]).decode()
# success("FLAG: " + flag)
p.interactive()
