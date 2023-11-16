#include <iostream>
#include "Node.h"
#include "User.h"

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}