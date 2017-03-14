#ifndef WPACONTROL_SLAVE
#define WPACONTROL_SLAVE

#include <vector>
#include <string>

#include "helpers/include/terminal.h"

using namespace std;

struct AP {
	string mac;
	int rssi;
	int index;
};

class Slave {
	public:
		// For the constructor, we simple need to pass the interface
		// this slave will be listening on.
		Slave(string iface);

		// best_ap finds the best AP that this slave has detected, and returns 
		// it via the passed parameters. Returns a boolean that specifies
		// whether the passed value was modified. It is only false when
		// there are no aps detected by this slave.
		bool best_ap(AP&);
		
		// does the same as above, except it also starts and stops the p2p on
		// this interface.
		bool best_ap_contained(AP&);
		
		// takes a mac adderss as a parameter, and returns all the info about
		// that device in an AP object (RSSI + index)
		AP more_info(string mac);
		
		// control functions. Should be inserted into the loop somehow.
		void p2p_find();
		void p2p_stop();
		void p2p_flush();
		
	private:
		// the interface of the slave
		string iface_;
		
		// a string containing the inital wpa_cli command, to avoid retyping.
		string start_cmd_;
		
		// finds the mac addresses of all APs within range of this slave
		void get_macs(vector<string>&);
};

#endif
