CFLAGS = -Wall -Wextra -pedantic -std=c99
SRC = src/main.c src/linker.c
BIN = my_ld

.PHONY: my_ld

all:
	${CC} ${CFLAGS} ${SRC} -o ${BIN}

my_ld:
	echo "ca link O. K. L. M"

check:
	make -C tests MY_LD=../my_ld

clean:
	${RM} ${BIN}
	make -C tests clean
