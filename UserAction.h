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
	explicit UserAction(std::string role = "");

	/**
	 * @brief Default constructor
	 */
	UserAction();

	/**
	 * @brief Add a new user
	 * @param user UserData object representing the user
	 */
	bool addUser(const UserData& user);

	/**
	* @brief Delete a user.
	* @param userName Username of the user to delete
	*/
	bool deleteUser(const std::string& userName);

	/**
	 * @brief Find a user by username
	 * @param userName Username of the user to find
	 * @return UserData object representing the found user
	 */
	UserData findUser(const std::string& userName);

	/**
	 * @brief Edit user information
	 * @param userName Username of the user to edit
	 * @param editedUser UserData object representing the edited user information
	 */
	void updateUserInformation(const std::string& userName,const UserData& editedUser);

	/**
	 * @brief Display user information
	 * @param userName Username of the user to display
	 * @return String containing user information
	 */
	std::string getUserInformation(const std::string& UserName);

	/**
	 * @brief Display all employees information (for admin role)
	 * @return Vector of strings containing information of all users
	 */
	std::vector<std::string> getAllUsersInformation();

	/**
	 * @brief Authenticate user based on username and password
	 * @param userName Username
	 * @param password Password
	 * @return True if authentication succeeds, false otherwise
	 */
	bool authenticateUser(const std::string& userName, const std::string& password);
};


#endif //CTDL_GK_USERACTION_H
