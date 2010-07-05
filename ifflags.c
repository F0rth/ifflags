/*
Copyright (c) 2010, Forth <forth@ophane.net>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


Part of this program has been derived from "Basic Packet-Sniffer Construction from the
Ground Up" http://www.packetstormsecurity.org/sniffers/Sniffer_construction.txt
by Chad Renfro <raw_sock@hotmail.com>
*/

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

/* Global variables */
int             sock;
struct ifreq    ifr;
char           *interface;
unsigned int    mode;

/* Prototypes functions */
int             Decode_flags(void);
int             Set_mode(void);
int             Open_if(void);
int             Open_Raw_Socket(void);

/* Let's begin ! */

int
main(int argc, char *argv[])
{
	char           *all_flags;
	switch (argc) {
	case (2):
		interface = argv[1];
		strlcpy(ifr.ifr_name, interface, strlen(interface) + 1);
		Open_Raw_Socket();
		Open_if();
		printf("%s is currently set to: %x\n", interface, ifr.ifr_flags);
		Decode_flags();
		break;

	case (3):
		interface = argv[1];
		strlcpy(ifr.ifr_name, interface, strlen(interface) + 1);
		mode = strtol(argv[2], NULL, 16);

		Open_Raw_Socket();
		Open_if();
		printf("%s is currently set to: %x\n", interface, ifr.ifr_flags);
		Decode_flags();
		printf("\n");
		Set_mode();
		printf("\n");
		printf("%s is now set to: %x\n", interface, ifr.ifr_flags);
		Decode_flags();
		break;

	default:

		all_flags = "ffff";
		mode = strtol(all_flags, NULL, 16);
		ifr.ifr_flags = mode;
		printf("--- network interface flags hacking tool:D ---\n");
		printf("ifflags ifname [flags]\n");
		printf("flags values in hexa:\n\n");
		Decode_flags();
	}
	return (0);
}

int
Open_Raw_Socket()
{
	if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		/* Then the socket was not created properly and must die */
		printf("The raw socket was not created\n");
		printf("try with root ... ;-)\n");
		exit(0);
	};
	return (0);
}

int
Open_if()
{

	if ((ioctl(sock, SIOCGIFFLAGS, &ifr) == -1)) {
		/* Could not retrieve flags for the interface */
		printf("Could not retrive flags for the interface :( \n");
		exit(0);
	}
	printf("interface --> %s <--\n", interface);
	printf("retrieved flags from interface successfully ... :D \n\n");
	return (0);
}

int
Set_mode()
{
	/* now that the flags have been retrieved */
	/* set the flags to "mode" */
	ifr.ifr_flags = mode;
	if (ioctl(sock, SIOCSIFFLAGS, &ifr) == -1) {
		/* Could not set the flags on the interface */
		printf("Could not set %x:", mode);
		exit(0);
	}
	printf("!!! setting interface --> %s <-- to %x !!! \n", ifr.ifr_name, mode);
	return (0);
}

int
Decode_flags()
{
	short           i;
	short           table_length;
	struct if_mode {
		int             flag;
		char           *comment;
	};
	struct if_mode *openbsd_mode = NULL;

	openbsd_mode[0].flag = IFF_UP;
	openbsd_mode[0].comment = "interface is up";
	openbsd_mode[1].flag = IFF_BROADCAST;
	openbsd_mode[1].comment = "broadcast address valid";
	openbsd_mode[2].flag = IFF_DEBUG;
	openbsd_mode[2].comment = "turn on debugging";
	openbsd_mode[3].flag = IFF_LOOPBACK;
	openbsd_mode[3].comment = "is a loopback net";
	openbsd_mode[4].flag = IFF_POINTOPOINT;
	openbsd_mode[4].comment = "interface is point-to-point link";
	openbsd_mode[5].flag = IFF_NOTRAILERS;
	openbsd_mode[5].comment = "avoid use of trailers";
	openbsd_mode[6].flag = IFF_RUNNING;
	openbsd_mode[6].comment = "resources allocated";
	openbsd_mode[7].flag = IFF_NOARP;
	openbsd_mode[7].comment = "no address resolution protocol";
	openbsd_mode[8].flag = IFF_PROMISC;
	openbsd_mode[8].comment = "receive all packets";
	openbsd_mode[9].flag = IFF_ALLMULTI;
	openbsd_mode[9].comment = "receive all multicast packets";
	openbsd_mode[10].flag = IFF_OACTIVE;
	openbsd_mode[10].comment = "transmission in progress";
	openbsd_mode[11].flag = IFF_SIMPLEX;
	openbsd_mode[11].comment = "can\'t hear own transmissions";
	openbsd_mode[12].flag = IFF_LINK0;
	openbsd_mode[12].comment = "link0 defined bit";
	openbsd_mode[13].flag = IFF_LINK1;
	openbsd_mode[13].comment = "link1 defined bit";
	openbsd_mode[14].flag = IFF_LINK2;
	openbsd_mode[14].comment = "link2 defined bit";
	openbsd_mode[15].flag = IFF_MULTICAST;
	openbsd_mode[15].comment = "supports multicast";

	table_length = sizeof(openbsd_mode);
	for (i = 0; i <= table_length; i++) {
		if ((ifr.ifr_flags & openbsd_mode[i].flag) == openbsd_mode[i].flag) {
			printf("%x %s\n", openbsd_mode[i].flag, openbsd_mode[i].comment);
		}
	}

	return (0);
}
