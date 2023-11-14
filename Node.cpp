#include <iostream>
#include "Node.h"

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}

template<class DataType>
void Node<DataType>::display() const {
    std::cout << _data << std::endl;
}