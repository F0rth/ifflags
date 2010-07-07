OS!=	uname -s
PROG=	ifflags
SRCS=	ifflags.c
.if ${OS} == OpenBSD
SRCS+=	openbsd.c
.elif  ${OS} == Linux
SRCS+= linux.c
.endif
CFLAGS+=	-g -Wall -ansi -pedantic	\
		-Wall -Wmissing-prototypes \
		-Wstrict-prototypes

.include <bsd.prog.mk>
