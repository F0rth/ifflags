#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>


#include "strlcpy.h"

/* Prototypes functions */
int             Decode_flags(void);
int             Set_mode(void);
int             Open_if(void);
int             Open_Raw_Socket(void);
int             Load_os_flags(void);

struct if_mode {
	int             flag;
	char           *comment;
};

extern int      	sock;
extern struct		ifreq ifr;
extern char	   	   *interface;
extern unsigned int mode;
extern struct if_mode os_flags[];
extern short    	table_length;
