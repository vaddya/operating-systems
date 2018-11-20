all: threads_ctrl_c process_ctrl_c process_ctrl_z

threads_ctrl_c: threads_ctrl_c.c
	gcc -o threads_ctrl_c threads_ctrl_c.c -pthread

process_ctrl_c: process_ctrl_c.c
	gcc -o process_ctrl_c process_ctrl_c.c -pthread

process_ctrl_z: process_ctrl_z.c
	gcc -o process_ctrl_z process_ctrl_z.c -pthread

clean:
	rm threads_ctrl_c process_ctrl_c process_ctrl_z