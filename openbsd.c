#include "ifflags.h"

short           table_length = 15;
struct if_mode  os_flags[15];

int 
Load_os_flags()
{

	os_flags[0].flag = IFF_UP;
	os_flags[0].comment = "interface is up";
	os_flags[1].flag = IFF_BROADCAST;
	os_flags[1].comment = "broadcast address valid";
	os_flags[2].flag = IFF_DEBUG;
	os_flags[2].comment = "turn on debugging";
	os_flags[3].flag = IFF_LOOPBACK;
	os_flags[3].comment = "is a loopback net";
	os_flags[4].flag = IFF_POINTOPOINT;
	os_flags[4].comment = "interface is point-to-point link";
	os_flags[5].flag = IFF_NOTRAILERS;
	os_flags[5].comment = "avoid use of trailers";
	os_flags[6].flag = IFF_RUNNING;
	os_flags[6].comment = "resources allocated";
	os_flags[7].flag = IFF_NOARP;
	os_flags[7].comment = "no address resolution protocol";
	os_flags[8].flag = IFF_PROMISC;
	os_flags[8].comment = "receive all packets";
	os_flags[9].flag = IFF_ALLMULTI;
	os_flags[9].comment = "receive all multicast packets";
	os_flags[10].flag = IFF_OACTIVE;
	os_flags[10].comment = "transmission in progress";
	os_flags[11].flag = IFF_SIMPLEX;
	os_flags[11].comment = "can\'t hear own transmissions";
	os_flags[12].flag = IFF_LINK0;
	os_flags[12].comment = "link0 defined bit";
	os_flags[13].flag = IFF_LINK1;
	os_flags[13].comment = "link1 defined bit";
	os_flags[14].flag = IFF_LINK2;
	os_flags[14].comment = "link2 defined bit";
	os_flags[15].flag = IFF_MULTICAST;
	os_flags[15].comment = "supports multicast";

	return (0);

}
