#ifndef CTDL_GK_USERACTION_H
#define CTDL_GK_USERACTION_H

#include "Users.h"
#include "UserData.h"

class UserAction {
private:
	Users list;
	std::string strRole;

public:
	UserAction(std::string role);
	UserAction();
	~UserAction();
	void setUserRole(std::string role);
	std::string getUserRole();
	void addUser(UserData user);
	void deleteUser(UserData user);
	UserData findUser(std::string userName);
	void editUser(std::string userName,UserData editedUser);
	std::string displayUser(std::string UserName);
	std::vector<std::string> displayUsers();
	bool authentication(std::string userName, std::string passWord);
};


#endif //CTDL_GK_USERACTION_H
