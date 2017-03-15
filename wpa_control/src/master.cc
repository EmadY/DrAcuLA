#include <math.h>

#include "wpa_control/include/master.h"

Master::Master(string U_iface, string R_iface, string D_iface, string L_iface) {
	iface_[0] = U_iface;
	iface_[1] = R_iface;
	iface_[2] = D_iface;
	iface_[3] = L_iface;
	
	for(int i = 0; i < 4; i++) {
		slave_[i] = new Slave(iface_[i]);
	}	
}
	
int Master::get_angle() {
	int top_loc = 0;
	AP best_ap;
	AP curr_ap[4];
	
	slave_[0]->best_ap_contained(best_ap);
	
	for(int i = 0; i < 4; i++) {
		slave_[i]->best_ap_contained(curr_ap[i]);
		
		if(curr_ap[i].index < best_ap.index && curr_ap[i].rssi != 0) {
			best_ap = curr_ap[i]; top_loc = i;
		} else if(curr_ap[i].index == best_ap.index && curr_ap[i].rssi != 0 && curr_ap[i].rssi > best_ap.rssi) {
			best_ap = curr_ap[i]; top_loc = i;
		}
	}
	
	// set whether we reached for next time we get asked
	at_dest_ = (best_ap.index == 0);
	
	// now that we know the best index, we need to check that the adjacent ones aren't close enough
	// that we have to move in a diagonal.
	
	int left = (top_loc + 3) % 4, right = (top_loc + 5) % 4;
	if(abs(curr_ap[top_loc].rssi - curr_ap[left].rssi) < 5) return (left * 90 + 45) % 360;
	else if(abs(curr_ap[top_loc].rssi - curr_ap[right].rssi) < 5) return (top_loc * 90 + 45) % 360;
	else return (top_loc * 90);
}

bool Master::at_dest() {
	return at_dest_;
}
