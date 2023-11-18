

//#ifndef CTDL_GK_USER_CPP
//#define CTDL_GK_USER_CPP

#include <iostream>

class Login {
private:
	std::string _strUser;
	std::string _strPass;
	int _intTypeUser;		// co 2 type user la admin va employee
							//admin Administrators
							//employ Employees
	
public:
	Login(std::string user = "", std::string pass = "", int type = 0);
	
	~Login();
	std::string getUser() const;
	void setUser(std::string user);
	std::string getPass() const;
	void setPass(std::string pass);
	int getIntTypeUser() const;
	std::string getStrTypeUser() const;
	void setTypeUser(int type);
	bool authenticate() const;

};

//#endif
