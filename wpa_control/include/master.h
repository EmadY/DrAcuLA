#ifndef WPACONTROL_MASTER
#define WPACONTROL_MASTER

#include "wpa_control/include/slave.h"

using namespace std;

//TODO(emad): We still don't know if wpa_cli can support multiple ifaces started
// at a time. Once we figure that out we might wanna switch from best_ap_contained
// as it has a 4 second delay.

class Master {
	public:
		// constructor that takes the names of the 4 p2p interfaces as parameters.
		Master(string, string, string, string);
		
		// returns the angle in which the drone should travel, counter clockwise.
		int get_angle();
		
		// returns whether we are in range of the target
		// requires that get_angle() has been called recently, or the answer will be incorrect.
		bool at_dest();
	private:
		// the interfacaes in all 4 cardinal directions
		string iface_[4];
		Slave* slave_[4];
		bool at_dest_;
};


#endif
