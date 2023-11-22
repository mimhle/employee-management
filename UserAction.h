#ifndef CTDL_GK_USERACTION_H
#define CTDL_GK_USERACTION_H

#include "Users.h"
#include "UserData.h"
/**
 * @class UserAction
 * @brief Class for user actions
 * @details This class provides functionality for performing various user-related actions,
 * such as adding, deleting, finding, editing, and displaying user information.
 */
class UserAction {
private:
	std::string strRole; ///< User role (admin/employee)
	Users list; ///< User data list

public:
	/**
	 * @brief Constructor with role parameter
	 * @param role User role (default is empty)
	 */
	UserAction(std::string role);

	/**
	 * @brief Default constructor
	 */
	UserAction();

	/**
	 * @brief Get the user role
	 * @return User role
	 */
	std::string getUserRole();

	/**
	* @brief Add a new user
	* @param user UserData object representing the user
	*/
	void addUser(UserData user);

	/**
	 * @brief Delete a user
	 * @param user UserData object representing the user to be deleted
	 */
	void deleteUser(UserData user);

	/**
	 * @brief Find a user by username
	 * @param userName Username of the user to find
	 * @return UserData object representing the found user
	 */
	UserData findUser(std::string userName);

	/**
	 * @brief Edit user information
	 * @param userName Username of the user to edit
	 * @param editedUser UserData object representing the edited user information
	 */
	void editUser(std::string userName,UserData editedUser);
	
	/**
	 * @brief Display user information
	 * @param userName Username of the user to display (for employee role)
	 * @return String containing user information
	 */
	std::string displayUser(std::string UserName);

	/**
	* @brief Display all users' information (for admin role)
	* @return Vector of strings containing information of all users
	*/
	std::vector<std::string> displayUsers();

	/**
	 * @brief Authenticate user based on username and password
	 * @param userName Username
	 * @param passWord Password
	 * @return True if authentication succeeds, false otherwise
	 */
	bool authentication(std::string userName, std::string passWord);
};


#endif //CTDL_GK_USERACTION_H
