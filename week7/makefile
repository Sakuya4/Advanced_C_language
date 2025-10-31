CC=gcc
OBJ=list.o ui.o main.o
EXE=run

all:${EXE}
$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)
%.o: %.c
	$(CC) -c $< -o $@

clean:
	del $(OBJ) $(EXE).exe 2>NUL
