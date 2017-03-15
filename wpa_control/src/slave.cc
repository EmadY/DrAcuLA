#include "wpa_control/include/slave.h"
#include <iostream>


Slave::Slave(string iface): 
	iface_(iface) {
	
	start_cmd_ = "sudo wpa_cli -i " + iface + " ";
}
	
void Slave::get_macs(vector<string>& macs) {
	macs = vector<string>();
	string data = Terminal::Exec(start_cmd_ + "p2p_peers");
		
	size_t nl_pos = data.find("\n");
	int start_loc = 0;
	
	while(nl_pos != std::string::npos) {
		macs.push_back(data.substr(start_loc, 17));
		start_loc = nl_pos + 1;
		nl_pos = data.find("\n", nl_pos + 1);
	}
}

bool Slave::best_ap(AP& top_ap) {
	vector<string> macs;
	get_macs(macs);
	
	if(macs.size() == 0) return false;
	
	// set it to the first one, just as a start.
	top_ap = more_info(macs[0]);

	AP curr; 
	for(int i = 1; i < macs.size(); i++) {
		curr = more_info(macs[i]);
		// if it's a lower index, then take if for sure.
		// if it's the same index, pick whichever is closer.
		if(curr.index < top_ap.index && curr.rssi != 0) {
			top_ap = curr; continue;
		} else if(curr.index == top_ap.index && curr.rssi != 0 && curr.rssi > top_ap.rssi) {
			top_ap = curr;
		}	
	}
	
	return true;
}

bool Slave::best_ap_contained(AP& top_ap) {
	p2p_find();
	sleep(1);		// we need to wait for the AP to actually get readings
	bool ret = best_ap(top_ap);
	p2p_stop();
	
	return ret;	
}

AP Slave::more_info(string mac) {
	//TODO(emad): Change after we decide on a correct way to name the apps
	AP ap; ap.mac = mac;
	
	// first we need to make sure this is one of our APs -- there should be DrAcuLA in it's name
	string data = Terminal::Exec(start_cmd_ + "p2p_peer " + mac + " | grep \"device_name\\|level\"");

	size_t first_eq = data.find("[DrAcuLA]");
	if(first_eq == string::npos) {
		ap.rssi = 0;
		ap.index = 1000;
		return ap;
	}	

	size_t first_nl = data.find("\n", first_eq);
	size_t second_nl = data.find("\n", first_nl);
	size_t second_eq = data.find("=", first_eq);
	
	ap.index = stoi(data.substr(first_eq + 10, first_nl - first_eq - 10));	// '[DrAcuLA] ' is 10 letters long.
	ap.rssi = stoi(data.substr(second_eq + 1, second_nl - second_eq - 1));	// '=' is only 1 letter long.
	
	return ap;
}

void Slave::p2p_find() {
	Terminal::Exec(start_cmd_ + "p2p_find");
}


void Slave::p2p_stop() {
	Terminal::Exec(start_cmd_ + "p2p_stop_find");
}


void Slave::p2p_flush() {
	Terminal::Exec(start_cmd_ + "p2p_flush");
}
