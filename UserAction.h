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
	Users _usersList;
	std::string _strRole;

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
	 * @brief Add a new user
	 * @param user UserData object representing the user
	 */
	void addUser(UserData user);

	/**
	* @brief Delete a user.
	* @param user UserData object representing the user to be deleted.
	* @param iLine Initialize iLine to -1 to handle the case when the user is not found.
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
	 * @param iLine Initialize iLine to -1 to handle the case when the user is not found.
	 * @param editedUser UserData object representing the edited user information
	 */
	void updateUserInformation(std::string userName,UserData user);

	/**
	 * @brief Display user information
	 * @param userName Username of the user to display (for employee role)
	 * @return String containing user information
	 */
	std::string getUserInformation(std::string UserName);

	/**
	 * @brief Display all employees information (for admin role)
	 * @return Vector of strings containing information of all users
	 */
	std::vector<std::string> getAllUsersInformation();

	/**
	 * @brief Authenticate user based on username and password
	 * @param userName Username
	 * @param passWord Password
	 * @return True if authentication succeeds, false otherwise
	 */
	bool authenticateUser(std::string userName, std::string passWord);
};


#endif //CTDL_GK_USERACTION_H
