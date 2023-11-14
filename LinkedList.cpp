#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//#pragma once
#include <iostream>
#include "Node.cpp"

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
    void addHead(DataType data);
    
    /**
     * @brief Appends a node to the end of the list
     * @details This function creates a new node with the given data and places it at the end of the linked list.
     * @param data The data for the new node
     * @return void
    */
    void addTail(DataType data);
    
    /**
     * @brief Inserts a node after a given node in the list
     * @details This function creates a new node with the provided data and places it in the linked list right after the specified node.
     * @param node The node after which the new node will be inserted
     * @param data The data for the new node
     * @return void
    */
    void addAfter(Node<DataType>* node, DataType data);
    
    /**
     * @brief Locates a node in the list by its data
     * @details This function searches the linked list for a node containing the specified data.
     * @param data The data of the node to locate
     * @return The node containing the given data, or null if no such node is found
    */
    Node<DataType>* search(DataType data);
    
    /**
     * @brief Identifies the node prior to a specified node in the list
     * @details This function takes a reference node and finds the node that is positioned before it in the linked list.
     * @param node The node whose predecessor is to be found
     * @return The node preceding the given node, or null if the provided node is the first in the list or not found
    */
    Node<DataType>* searchPre(Node<DataType>* node);
    
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
     * @brief Prints the data of the linked list
     * @details This function traverses the linked list and prints the data of each node.
     * @return void
    */
    void display() const;
    
    /**
     * @brief Clear linked list
     * @details Clear linked list
     * @return void
    */
    void clear();
};

template<class DataType>
LinkedList<DataType>::LinkedList() {
    _pHead = NULL;
    _pTail = NULL;
    _iSize = 0;
}

template<class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

template<class DataType>
void LinkedList<DataType>::addHead(DataType data) {
    auto* _pAdd = new Node<DataType>(data);
    if (_pHead == NULL)
        _pHead = _pTail = _pAdd;
    else {
        _pAdd->_pNext = _pHead;
        _pHead = _pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addTail(DataType data) {
    auto* _pAdd = new Node<DataType>(data);
    if (_pHead == NULL)
        _pHead = _pTail = _pAdd;
    else {
        _pTail->_pNext = _pAdd;
        _pTail = _pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType data) {
    auto* _pAdd = new Node<DataType>(data);
    if (node == NULL) {
        addHead(data);
    } else {
        _pAdd->_pNext = node->_pNext;
        node->_pNext = _pAdd;
        if (_pAdd->_pNext == NULL)
            _pTail = _pAdd;
        _iSize++;
    }
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
    Node<DataType>* _p = _pHead;
    while (_p != NULL && _p->_data == data)
        _p = _p->_pNext;
    return _p;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
    Node<DataType>* _p = _pHead;
    if (_p == node)
        return NULL;
    while (_p != NULL && _p->_pNext != node)
        _p = _p->_pNext;
    return _p;
}

template<class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != NULL) {
        Node<DataType>* _pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete _pTemp;
        if (_pHead == NULL)
            _pTail = NULL;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead == NULL)
        return;
    Node<DataType>* _pTemp = _pTail;
    _pTail = searchPre(_pTail);
    delete _pTemp;
    if (_pTail != NULL)
        _pTail->_pNext = NULL;
    else
        _pHead = NULL;
    _iSize--;
}

template<class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    if (node == NULL)
        removeHead();
    else {
        Node<DataType>* _pTemp = node->_pNext;
        node->_pNext = _pTemp->_pNext;
        delete _pTemp;
        if (node->_pNext == NULL)
            _pTail = node;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* _p = search(data);
    if (_p == NULL)
        return;
    Node<DataType>* _pPre = searchPre(_p);
    if (_pPre == NULL)
        removeHead();
    else
        removeAfter(_pPre);
    _iSize--;
}

template<class DataType>
void LinkedList<DataType>::display() const {
    Node<DataType>* _pWalker = _pHead;
    while (_pWalker != NULL) {
        _pWalker->display();
        _pWalker = _pWalker->_pNext;
    }
}

template<class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != NULL)
        removeHead();
}

template<class DataType>
int LinkedList<DataType>::getSize() const {
    return _iSize;
}

template<class DataType>
void LinkedList<DataType>::selectionSort() {
    Node<DataType>* _p = _pHead;
    Node<DataType>* _q;
    Node<DataType>* _pMin;
    while (_p != NULL) {
        _pMin = _p;
        _q = _p->_pNext;
        while (_q != NULL) {
            if (_q->_data < _pMin->_data)
                _pMin = _q;
            _q = _q->_pNext;
        }
        swap(_p->_data, _pMin->_data);
        _p = _p->_pNext;
    }
}

#pragma clang diagnostic pop