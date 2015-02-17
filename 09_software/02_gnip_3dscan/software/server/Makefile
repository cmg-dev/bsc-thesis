
EXEC = 3dscan_s
NFSFOLDER_FILE = ~/gnip/bin/$(EXEC)
CC = nios2-linux-uclibc-gcc
CFLAGS   = -I$(ROOTDIR)/$(LINUXDIR)/include -c -Wall
LDFLAGS = -elf2flt="-s 65536"
LINK = -lpthread 
LIB = /home/christoph/src/MiniQuadrix_II/software/mq2_software_library/libMiniQuadrix.a
all: $(EXEC)

3dscan_s: 3dscan_s.o Makefile
	 $(CC) $(LDFLAGS) -o $@ $(EXEC).o ../include/bmp.c $(LIB) $(LINK) $(LDLIBS$(LDLIBS_$@))
	 cp $(EXEC) $(NFSFOLDER_FILE)

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
