// Print hello world in screen

svid_init(1024, 768, 32)
scpu_reg_write(0, 0)
scpu_reg_write(1, 65)

write_alpha:
vm_mem_write(scpu_reg_read(0), scpu_reg_read(1))
scpu_reg_write(0, scpu_add(scpu_reg_read(0), 1))
scpu_reg_write(1, scpu_add(scpu_reg_read(1), 1))
scpu_jne(scpu_cmp(scpu_reg_read(1), 127), write_alpha)

scpu_reg_write(3, 0)
scpu_reg_write(2, 10)

loop:
svid_put_char(scpu_reg_read(2), 10, 10, vm_mem_read(scpu_reg_read(3), 0), 55555555)
scpu_reg_write(3, scpu_add(scpu_reg_read(3), 1))
scpu_reg_write(2, scpu_add(scpu_reg_read(2), 10))
scpu_jne(scpu_cmp(scpu_reg_read(3), 62), loop)
