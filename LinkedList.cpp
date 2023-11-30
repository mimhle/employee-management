#include "LinkedList.h"

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = nullptr;
}

template<class DataType>
LinkedList<DataType>::LinkedList() {
    _pHead = nullptr;
    _pTail = nullptr;
    _iSize = 0;
}

template<class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

template<class DataType>
void LinkedList<DataType>::addHead(const DataType& data) {
    auto* _pAdd = new Node<DataType>(data);
    if (_pHead == nullptr)
        _pHead = _pTail = _pAdd;
    else {
        _pAdd->_pNext = _pHead;
        _pHead = _pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addTail(const DataType& data) {
    auto* _pAdd = new Node<DataType>(data);
    if (_pHead == nullptr)
        _pHead = _pTail = _pAdd;
    else {
        _pTail->_pNext = _pAdd;
        _pTail = _pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, const DataType& data) {
    auto* _pAdd = new Node<DataType>(data);
    if (node == nullptr) {
        addHead(data);
    } else {
        _pAdd->_pNext = node->_pNext;
        node->_pNext = _pAdd;
        if (_pAdd->_pNext == nullptr)
            _pTail = _pAdd;
        _iSize++;
    }
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::search(const DataType& data) const {
    Node<DataType>* _p = _pHead;
    while (_p != nullptr && _p->_data != data)
        _p = _p->_pNext;
    return _p;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) const {
    Node<DataType>* _p = _pHead;
    if (_p == node)
        return nullptr;
    while (_p != nullptr && _p->_pNext != node)
        _p = _p->_pNext;
    return _p;
}

template<class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != nullptr) {
        Node<DataType>* _pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete _pTemp;
        if (_pHead == nullptr)
            _pTail = nullptr;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead == nullptr)
        return;
    Node<DataType>* _pTemp = _pTail;
    _pTail = searchPre(_pTail);
    delete _pTemp;
    if (_pTail != nullptr)
        _pTail->_pNext = nullptr;
    else
        _pHead = nullptr;
    _iSize--;
}

template<class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    if (node == nullptr)
        removeHead();
    else {
        Node<DataType>* _pTemp = node->_pNext;
        node->_pNext = _pTemp->_pNext;
        delete _pTemp;
        if (node->_pNext == nullptr)
            _pTail = node;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* _pWalker = _pHead, * _pPre = nullptr;
    while (_pWalker != nullptr && _pWalker->_data != data) {
        _pPre = _pWalker;
        _pWalker = _pWalker->_pNext;
    }
    if (_pWalker == nullptr)
        return;
    if (_pPre != nullptr) {
        if (_pWalker == _pTail) {
            _pTail = _pPre;
            _pPre->_pNext = nullptr;
        }
        _pPre->_pNext = _pWalker->_pNext;
        delete _pWalker;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != nullptr)
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
    while (_p != nullptr) {
        _pMin = _p;
        _q = _p->_pNext;
        while (_q != nullptr) {
            if (_q->_data < _pMin->_data)
                _pMin = _q;
            _q = _q->_pNext;
        }
        swap(_p->_data, _pMin->_data);
        _p = _p->_pNext;
    }
}

template<class DataType>
DataType& LinkedList<DataType>::operator[](int index) const {
    Node<DataType>* _p = _pHead;
    for (int i = 0; i < index; i++)
        _p = _p->_pNext;
    return _p->_data;
}