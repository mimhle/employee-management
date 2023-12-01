#ifndef CTDL_GK_USERACTION_H
#define CTDL_GK_USERACTION_H

#include "Users.h"
#include "UserData.h"

/**
 * @class UserAction
 * @brief Manages actions related to user data and authentication
 *
 * This class allows creating, reading, updating, and deleting user records
 * from a user list. It also handles user authentication. Methods are
 * provided for adding new users, finding existing users, updating user
 * information, displaying user data, and validating username/password.
 *
 * Access to full user data is restricted based on the user role set for
 * the class instance. The default role has read-only access. The "admin"
 * role allows full access to all methods.
 */
class UserAction {
private:
    Users _usersList;
    std::string _strRole;

public:

    /**
     * @brief Constructor
     * Creates an empty UserAction instance with default empty role.
     * @param role User role to assign ("employee" or "admin")
     */
    explicit UserAction(std::string role = "");

    /**
     * @brief Default constructor
     */
    UserAction();

    /**
     * @brief Set user role
     * @param role User role to assign ("employee" or "admin")
     */
    void setRole(std::string role);

    /**
     * @brief Add new user record
     * Adds a provided UserData object as a new user record in the user list.
     * Accessible only if the instance role is "admin".
     * @param user UserData object with new user data
     * @return true if the user was added successfully, false otherwise
     */
    bool addUser(const UserData& user);

    /**
     * @brief Delete a user
     * @param userName Username of the user to be deleted
     * @return true if the user was deleted successfully, false otherwise
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
     * @return true if the user information was edited successfully, false otherwise
     */
    bool updateUserInformation(const std::string& userName, const UserData& user);

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

    /**
     * @brief find user based on username
     * @param userName Username
     * @return True if find succeeds, false otherwise
     */
    bool findUserName(const std::string& userName);
};


#endif //CTDL_GK_USERACTION_H
