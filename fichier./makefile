CC = gcc
EXEC = run
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)



all : $(EXEC)

%.o : %.c
    $(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
    $(CC) -o $@ $^

clean :
    $(CLEAN)

mrproper : clean
    $(MRPROPER)
