PROG=	ifflags

CFLAGS+=	-ansi -Wall -pedantic	\
		-Wall -Wmissing-prototypes -Werror	\
		-Wstrict-prototypes

.include <bsd.prog.mk>
