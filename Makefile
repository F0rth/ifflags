PROG=	ifflags

CFLAGS+=	-Wall -ansi -pedantic	\
		-Wall -Wmissing-prototypes \
		-Wstrict-prototypes -Werror

.include <bsd.prog.mk>
