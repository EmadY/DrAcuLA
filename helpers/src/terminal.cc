#include "helpers/include/terminal.h"

std::string Terminal::Exec(std::string s_cmd) {
	const char* cmd = s_cmd.c_str();
	char buffer[128];
	std::string result = "";
	
	FILE* pipe = popen(cmd, "r");
	if(!pipe) throw std::runtime_error("popen() failed");
	try { 
		
		while(!feof(pipe)) {
			if(fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}		
		
	} catch (...) {
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return result;
}

std::string Terminal::dExec(std::string s_cmd) {
    printf("dExec : %s\n", s_cmd.c_str());
    return Exec(s_cmd);
}
