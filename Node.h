//#pragma once

#ifndef CTDL_GK_NODE_CPP
#define CTDL_GK_NODE_CPP

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
     * @brief Display information of node
     * @details Display information of node
     * @return void
    */
    void display() const;
};

#endif // CTDL_GK_NODE_CPP