
EXEC = video
NFSFOLDER_FILE = ~/gnip/bin/$(EXEC)
CC = nios2-linux-uclibc-gcc
CFLAGS   += -I$(ROOTDIR)/$(LINUXDIR)/include -c -Wall 
LDFLAGS = -elf2flt="-s 65536"
LINK = -lpthread 
LIB = /home/christoph/src/MiniQuadrix_II/software/mq2_software_library/libMiniQuadrix.a
all: $(EXEC)

video: video.o Makefile
	 $(CC) $(LDFLAGS) -o $@ video.o $(LIB) $(LINK) $(LDLIBS$(LDLIBS_$@))
	 cp $(EXEC) $(NFSFOLDER_FILE)

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
