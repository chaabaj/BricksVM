//Music player


scpu_reg_write(0, 0)
scpu_reg_write(2, 0)

load_music:
scpu_write_reg(0, shd_read(scpu_read_reg(2), 4096), scpu_read_reg(2), 4096)
scpu_write_reg(2, scpu_add(scpu_read_reg(2), scpu_read_reg(0)))
scpu_write_reg(1, scpu_cmp(0, scpu_read_reg(1)))
scpu_je(scpu_read_reg(1), play_music)
scpu_jmp(load_music)

play_music:
saudio_load_music(0, 0, scpu_read_reg(2))
saudio_play_music(0) 
