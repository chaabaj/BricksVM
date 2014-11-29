// Print hello world in screen

svid_init(1024, 768, 32)
scpu_reg_write(0, 0)
scpu_reg_write(1, 65)

vm_mem_write(0, 'H')
vm_mem_write(1, 'e')
vm_mem_write(2, 'l')
vm_mem_write(3, 'l')
vm_mem_write(4, 'o')
vm_mem_write(5, ' ')
vm_mem_write(6, 'w')
vm_mem_write(7, 'o')
vm_mem_write(8, 'r')
vm_mem_write(9, 'l')
vm_mem_write(10, 'd')
vm_mem_write(11, '!')
vm_mem_write(12, 0)

vm_mem_write(13, 50)
vm_mem_write(14, 0)
vm_mem_write(15, 0)
vm_mem_write(16, 0)

init_loop:
scpu_reg_write(0, 0)
scpu_reg_write(1, 10)

put_string:
vm_print(scpu_reg_read(0))
svid_put_char(scpu_reg_read(1), 10, vm_mem_read(scpu_reg_read(0), 0), 10, 0xFFFFFF)
scpu_reg_write(0, scpu_add(scpu_reg_read(0), 1))
scpu_reg_write(1, scpu_add(scpu_reg_read(1), 10))
scpu_jne(scpu_cmp(vm_mem_read(scpu_reg_read(0), 0), 0), put_string)


svid_put_number(60, 60, vm_mem_read(13, 2), 10, 0xFFFFFF)

