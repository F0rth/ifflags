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

#include "ifflags.h"

/* Global variables */

int             sock;
struct ifreq    ifr;
char           *interface;
unsigned int    mode;



/* Let's begin ! */

int
main(int argc, char *argv[])
{
	char           *all_flags;
	Load_os_flags();

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
		printf("--- network interface flags hacking tool	:D ---\n");
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

	for (i = 0; i <= table_length; i++) {
		if ((ifr.ifr_flags & os_flags[i].flag) == os_flags[i].flag) {
			printf("%x %s\n", os_flags[i].flag, os_flags[i].comment);
		}
	}

	return (0);
}
