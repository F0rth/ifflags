PROG=	ifflags

CFLAGS+=	-g -Wall -ansi -pedantic	\
		-Wall -Wmissing-prototypes \
		-Wstrict-prototypes

.include <bsd.prog.mk>
