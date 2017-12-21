obj-m := rps_dev.o

export PATH:=$(PATH):~wahn/public/cs449/debian-headers/usr/bin:~wahn/public/cs449/debian-headers/usr/lib/gcc/i486-linux-gnu/4.6
export LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):~wahn/public/cs449/debian-headers/usr/lib/i386-linux-gnu

KDIR  := ~wahn/public/cs449/debian-headers/lib/modules/3.2.0-4-686-pae/build
PWD   := $(shell pwd)

default: rps_dev.ko rps_ctrl RPS

rps_dev.ko: rps_dev.c
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) modules

rps_ctrl: rps_ctrl.c
	gcc -m32 rps_ctrl.c -o rps_ctrl
	
RPS: RPS.c
	gcc -m32 RPS.c -o RPS

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) clean
	rm rps_ctrl
	rm RPS
