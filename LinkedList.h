#ifndef CTDL_GK_LINKEDLIST_CPP
#define CTDL_GK_LINKEDLIST_CPP

#include <iostream>
#include "UserData.h"

template<class DataType>
class LinkedList;

/**
* @class Node
* @brief Class representing a Node
* @details This class encapsulates the data and operations for a Node in a data structure (like a linked list, tree, etc.).
* @note This class can be used on LinkedList, Tree.
*/
template<class DataType>
class Node {
    friend class LinkedList<DataType>;

private:
    DataType _data;
    Node* _pNext;

public:
    explicit Node(DataType data);

    /**
     * @brief Gets the data of a node
     * @details This function retrieves the data stored in a node.
     * @return The data of the node
    */
    DataType getData() const;
};


/**
* @class LinkedList
* @brief Class representing a LinkedList
* @details This class encapsulates the data and operations for a LinkedList. It includes operations such as insertion, deletion, traversal, etc.
* @note This class can be used on any platform that supports C++.
*/
template<class DataType>
class LinkedList {
private:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;

public:
    LinkedList();

    ~LinkedList();

    /**
    * @brief Inserts a node at the beginning of the list
    * @details This function creates a new node with the provided data and places it at the start of the linked list.
    * @param data The data for the new node
    * @return void
   */
    void addHead(const DataType& data);

    /**
     * @brief Appends a node to the end of the list
     * @details This function creates a new node with the given data and places it at the end of the linked list.
     * @param data The data for the new node
     * @return void
    */
    void addTail(const DataType& data);

    /**
     * @brief Inserts a node after a given node in the list
     * @details This function creates a new node with the provided data and places it in the linked list right after the specified node.
     * @param node The node after which the new node will be inserted
     * @param data The data for the new node
     * @return void
    */
    void addAfter(Node<DataType>* node, const DataType& data);

    /**
     * @brief Locates a node in the list by its data
     * @details This function searches the linked list for a node containing the specified data.
     * @param data The data of the node to locate
     * @return The node containing the given data, or null if no such node is found
    */
    Node<DataType>* search(const DataType& data) const;


    /**
     * @brief Identifies the node prior to a specified node in the list
     * @details This function takes a reference node and finds the node that is positioned before it in the linked list.
     * @param node The node whose predecessor is to be found
     * @return The node preceding the given node, or null if the provided node is the first in the list or not found
    */
    Node<DataType>* searchPre(Node<DataType>* node) const;

    /**
     * @brief Deletes the head node of the list
     * @details This function removes the node at the beginning of the linked list.
     * @return void
    */
    void removeHead();

    /**
     * @brief Removes the last node in the list
     * @details This function deletes the node at the tail of the linked list.
     * @return void
    */
    void removeTail();

    /**
     * @brief Removes the node after a specified node in the list
     * @details This function deletes the node that is positioned after the specified node in the linked list.
     * @param node The node whose successor is to be deleted
    */
    void removeAfter(Node<DataType>* node);

    /**
     * @brief Deletes the first occurrence of a node with the given data in the list
     * @details This function locates the first node in the linked list with the provided data and removes it.
     * @param data The data of the node to be removed
     * @return void
    */
    void remove(DataType data);

    /**
     * @brief Arranges the list elements in increasing order
     * @details This function applies the selection sort algorithm to arrange the nodes of the linked list in ascending order.
     * @return void
    */
    void selectionSort();

    /**
     * @brief Return size of linked list
     * @details Return size of linked list
     * @return int
    */
    int getSize() const;

    /**
     * @brief Clear linked list
     * @details Clear linked list
     * @return void
    */
    void clear();

    /**
     * @brief Overload operator []
     * @details Overload operator []
     * @return DataType
    */
    DataType operator[](int index) const;
};

#endif // CTDL_GK_LINKEDLIST_CPP