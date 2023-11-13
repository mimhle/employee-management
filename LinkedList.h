#ifndef LinkedList_H
#define LinkedList_H

#include <User.h>
#include <iostream>
#include <string>

class Node {
    friend class LinkedList;
    private:
    User _data;
    Node* _next;

    public:
    //constructor
    Node() {
        _data = User();
        _next = NULL;
    }
    Node(User data) {
        _data = data;
        _next = NULL;
    }

    //desctructor
    ~Node() {
        _data = User();
        _next = NULL;
    }

    //getter && setter
    User getData() { return _data; }
    void setData(User data) { _data = data; }

    //method
};

class LinkedList {
    private:
    Node* _head;
    Node* _tail;
    int _size;

    public:
    //constructor
    LinkedList() {
        _head = NULL;
        _tail = NULL;
        _size = 0;
    }

    //destructor
    ~LinkedList() {
        _head = NULL;
        _tail = NULL;
        _size = 0;
    }

    //method
    void addTail(User data) {
        Node* newNode = new Node(data);
        if (_head == NULL) {
            _head = newNode;
            _tail = newNode;
        }
        else {
            _tail->_next = newNode;
            _tail = newNode;
        }
        _size++;
    }

    //key input is username
    void removeNode(std::string key) {
        Node* pWalker = _head;
        Node* prev = NULL;
        while (pWalker != NULL && pWalker->_data.getUsername() != key) {
            prev = pWalker;
            pWalker = pWalker->_next;
        }
        if (pWalker == NULL)
            return;
        if (prev == NULL)
            _head = _head->_next;
        else
            prev->_next = pWalker->_next;
        delete pWalker;
        _size--;
    }

    //return User with key is username
    User searchNode(std::string key) {
        Node* pWalker = _head;
        while (pWalker != NULL && pWalker->_data.getUsername() != key) {
            pWalker = pWalker->_next;
        }
        if (pWalker == NULL)
            return User();
        return pWalker->_data;
    }

    void updateNode(std::string key, User newData) {
        Node* pWalker = _head;
        while (pWalker != NULL && pWalker->_data.getUsername() != key) {
            pWalker = pWalker->_next;
        }
        if (pWalker == NULL)
            return;
        pWalker->_data = newData;
    }

    //change password of User with key is username
    void changePassword(std::string key, std::string newPassword) {
        Node* pWalker = _head;
        while (pWalker != NULL && pWalker->_data.getUsername() != key) {
            pWalker = pWalker->_next;
        }
        if (pWalker == NULL)
            return;
        pWalker->_data.setPassword(newPassword);
    }

    void Display() {
        Node* pWalker = _head;
        while (pWalker != NULL) {
            std::cout << pWalker->_data.getName() << std::endl;
            std::cout << pWalker->_data.getAddress() << std::endl;
            std::cout << pWalker->_data.getPhoneNumber() << std::endl;
            std::cout << pWalker->_data.getEmail() << std::endl;
            pWalker = pWalker->_next;
        }
    }
};



#endif