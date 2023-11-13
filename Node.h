//#pragma once

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