from pwn import *
p = process("./rand")
payload = "vFFFFFFF0FFF"
p.send(str(payload).encode())

p.interactive()
