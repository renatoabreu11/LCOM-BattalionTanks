COMPILER_TYPE= gnu

CC=gcc

PROG =	 Tanks
SRCS =   main.c
SRCS +=  vbe.c video_gr.c timer.c kbd.c mouse.c rtc.c
SRCS +=  bitmap.c tank.c bullet.c menu.c BattalionTanks.c game.c terrain.c font.c

CCFLAGS= -Wall -O3

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	-llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>