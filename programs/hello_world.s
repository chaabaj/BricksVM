// Print hello world in screen

svid_init(800, 600, 32)
scpu_reg_write(0, 0)
scpu_reg_write(2, 0)
scpu_reg_write(1, scpu_div(600, 2))
vm_mem_write(0, 'h')
vm_mem_write(1, 'e')
vm_mem_write(2, 'l')
vm_mem_write(3, 'l')
vm_mem_write(4, 'l')
vm_mem_write(5, 'o')
vm_mem_write(6, ' ')
vm_mem_write(7, 'w')
vm_mem_write(8, 'o')
vm_mem_write(9, 'r')
vm_mem_write(10, 'l')
vm_mem_write(11, 'd')


hello_world:
svid_put_char(0, scpu_reg_read(1), vm_mem_read(scpu_reg_read(2), 0), 16, 0xFFFFFF)
scpu_reg_write(0, scpu_add(scpu_read(0), 16))
scpu_reg_write(2, scpu_add(scpu_reg_read(2), 1))
scpu_cmp(11, scpu_reg_read(2))
scpu_jne hello_world
