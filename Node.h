//#pragma once

#ifndef CTDL_GK_NODE_CPP
#define CTDL_GK_NODE_CPP

template <class DataType>
class LinkedList;

template <class DataType>
class Node {
    friend class LinkedList<DataType>;
private:
    DataType _data;
    Node* _pNext;

public:
    //constructor
    Node(DataType data);

    //method
    void display() const;
};

#endif // CTDL_GK_NODE_CPP