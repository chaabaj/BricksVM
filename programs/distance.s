

svid_init(1024, 768, 32)
scpu_fpreg_write(0, 0)
scpu_fpreg_write(1, 10.5)
scpu_fpreg_write(2, 50.9)
scpu_fpreg_write(3, 60.2)


scpu_fpreg_write(4, scpu_sub(scpu_fpreg_read(0), scpu_fpreg_read(2)))
scpu_fpreg_write(4, scpu_pow(scpu_fpreg_read(4), 2))
scpu_fpreg_write(5, scpu_sub(scpu_fpreg_read(1), scpu_fpreg_read(3)))
scpu_fpreg_write(5, scpu_pow(scpu_fpreg_read(5), 2))
scpu_fpreg_write(6, scpu_sqrt(scpu_add(scpu_fpreg_read(4), scpu_fpreg_read(5))))
svid_put_number(10, 10, scpu_fpreg_read(6), 10, 0xFFFFFF)