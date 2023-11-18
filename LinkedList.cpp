#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

#include "LinkedList.h"
#include "UserData.h"

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}

template<class DataType>
DataType Node<DataType>::getData() const { return _data; }

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
void LinkedList<DataType>::addHead(const DataType& data) {
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
void LinkedList<DataType>::addTail(const DataType& data) {
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
void LinkedList<DataType>::addAfter(Node<DataType>* node, const DataType& data) {
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
Node<DataType>* LinkedList<DataType>::search(const DataType& data) const {
    Node<DataType>* _p = _pHead;
    while (_p != NULL && _p->_data != data)
        _p = _p->_pNext;
    return _p;
}

template<>
Node<UserData>* LinkedList<UserData>::search(const std::string& key) const {
    Node<UserData>* _p = _pHead;
    while (_p != NULL && _p->_data.getName() != key)
        _p = _p->_pNext;
    return _p;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) const {
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
    Node<DataType>* _pWalker = _pHead, * _pPre = NULL;
    while (_pWalker != NULL && _pWalker->_data != data) {
        _pPre = _pWalker;
        _pWalker = _pWalker->_pNext;
    }
    if (_pWalker == NULL)
        return;
    if (_pPre != NULL) {
        if (_pWalker == _pTail) {
            _pTail = _pPre;
            _pPre->_pNext = NULL;
        }
        _pPre->_pNext = _pWalker->_pNext;
        delete _pWalker;
        _iSize--;
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

template<class DataType>
DataType LinkedList<DataType>::getNodeData(Node<DataType>* node) const {
    return node->getData();
}

template<class DataType>
DataType LinkedList<DataType>::operator[](int index) const {
    Node<DataType>* _p = _pHead;
    for (int i = 0; i < index; i++)
        _p = _p->_pNext;
    return _p->_data;
}

//#endif // CTDL_GK_USER_CPP
#pragma clang diagnostic pop