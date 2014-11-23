// Print hello world in screen

svid_init(800, 600, 32)
scpu_reg_write(0, 0)
scpu_reg_write(2, 0)
scpu_reg_write(1, scpu_div(600, 2))
vm_mem_write(0, 65)
vm_mem_write(1, 66)
vm_mem_write(2, 67)
vm_mem_write(3, 68)
vm_mem_write(4, 69)
vm_mem_write(5, 70)
vm_mem_write(6, 71)
vm_mem_write(7, 72)
vm_mem_write(8, 73)
vm_mem_write(9, 74)
vm_mem_write(10, 75)
vm_mem_write(11, 76)

scpu_reg_write(3, 320)

loop:
svid_put_pixel(scpu_reg_read(3),15, 55555555)
scpu_reg_write(3, scpu_add(scpu_reg_read(3), 1))
scpu_jne(scpu_cmp(scpu_reg_read(3), 600), loop)
