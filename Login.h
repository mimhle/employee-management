

#ifndef CTDL_GK_USER_CPP
#define CTDL_GK_USER_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Login {
private:
	std::string _strUser;
	std::string _strPass;

public:
	Login(std::string user = "", std::string pass = "");
	
	~Login();
	std::string getUser() const;
	void setUser(std::string user);

	std::string getPass() const;
	void setPass(std::string pass);

	bool authenticate() const;

};

#endif
