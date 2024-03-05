#include <iostream>
using namespace std;

template <class T>
class Queue{
    struct Node
    {
        T data;
        Node* next;
        Node(T data);
        Node();
        Node(Node& Node);
        ~Node() = default;
    };


public:
    Node* first;
    Node* last;
    int index;
    Queue();
    Queue(const Queue& queue);
    ~Queue();

    T& front();
    void pushBack(T value);
    void popFront();
    int size();
    struct Iterator;
    Iterator begin();
    Iterator end();
    struct ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    struct EmptyQueue{};
};

template <class T, class F>
Queue<T> filter(Queue<T>& queue , F function);
template <typename T, class F>
void transform(Queue<T>& queue , F function);
template <typename T, class F>
int reduce(Queue<T>& queue ,int first, F function);
template <class T>
Queue<T>::Queue() {
    try{
        this->first = new Node();
    }
    //TODO - do i need to add something?
    catch (std::bad_alloc& e){
        throw(e);
    }
    this->last = this->first;
    this->index = -1;
}
template <class T>
Queue<T>::Queue(const Queue& queue){
//try and except - if there is a prob with allocation
    try{
        this->first = new Node();
    }
    catch (std::bad_alloc& e){
        throw(e);
    }
    this->index = -1;
    this->last = this->first;

    for (typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it){
        this->pushBack(*it);
    }
    this->index = queue.index;

}
template <class T>
Queue<T>::~Queue(){
    while(this->index >= 0)
    {
        Node* n = this->first;
        this->first = this->first->next;
        delete n;
        this->index--;
    }
};
template <class T>
Queue<T>::Node::Node(T data){
    this->data = data;
    this->next = nullptr;
}
template <class T>
Queue<T>::Node::Node(){
    this->data = 0;
    this->next = nullptr;
}
template <class T>
void Queue<T>::pushBack(T value) {
    if(this->index < 0)
    {
        this->first->data = value;
    }
    else
    {
        try{
            Node* new_node = new Node(value);
            this->last->next = new_node;
            this->last = new_node;
        }
        catch (std::bad_alloc& e){
            throw(e);
        }

    }
    this->index++;
}
template <class T>
T& Queue<T>::front() {
    if(this->index <0){
        throw EmptyQueue();
    }
        return this->first->data;
}

template <class T>
void Queue<T>::popFront() {
    if(this->index <0){
        throw EmptyQueue();
    }
    if(this->index > 0)
    {
        Node* n = this->first;
        this->first = this->first->next;
        delete n;
    }
    else
    {
        {
            Node* n = this->first;
            try{
                this->first = new Node();
            }
            catch (std::bad_alloc& e){
                throw(e);
            }
            this->last = this->first;
            delete n;
        }
    }
    this->index--;
    return;
}
template <class T>
int Queue<T>::size()
{
    return this->index + 1;
}

template <class T, class F>
Queue<T> filter(Queue<T>& queue , F function)
{
    Queue<T> new_queue;
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it){
        if(function(*it)){
            new_queue.pushBack(*it);
        }
    }
    return new_queue;
}

template <typename T, class F>
void transform(Queue<T>& queue , F function)
{
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it){
        *it = function(*it);
    }
}

template <typename T, class F>
int reduce(Queue<T>& queue ,int first, F function)
{
    int final = first;
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it){
        final = function(final , *it);
    }
    return final;
}


template <class T>
struct Queue<T>::Iterator{
    Node* current;
    Iterator(Node* node);
    ~Iterator() = default;
    T& operator*();
    Iterator& operator++();
    bool operator != (const Iterator& iterator) const;
    struct InvalidOperation{};
};
template <class T>
Queue<T>::Iterator::Iterator(Queue::Node *node) {
    this->current = node;
}


template <class T>
typename  Queue<T>::Iterator Queue<T>::begin(){
    return Queue<T>::Iterator(first);
}
template <class T>
typename  Queue<T>::Iterator Queue<T>::end(){
//error
    return nullptr;
}
template <class T>
T& Queue<T>::Iterator::operator*() {
    if(this->current == nullptr){
        throw InvalidOperation();
    }
    return this->current->data;
}
template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    if(this->current == nullptr){
        throw InvalidOperation();
    }
    this->current = this->current->next;
    return *this;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const{
    return iterator.current != this->current;
}


template <class T>
struct Queue<T>::ConstIterator{
    Node* current;
    ConstIterator(Node* node);
    ~ConstIterator() = default;
    const T& operator*() const;
     ConstIterator& operator++() ;
    bool operator != (const ConstIterator& iterator) const;
    struct InvalidOperation{};

};
template<class T>
Queue<T>::ConstIterator::ConstIterator(Queue::Node *node) {
    this->current = node;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const{
    if(this->current == nullptr){
        throw InvalidOperation();
    }
    return this->current->data;
}
template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()  {
    if(this->current == nullptr){
        throw InvalidOperation();
    }
    this->current = this->current->next;
    return *this;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constiterator) const{
    return constiterator.current != this->current;
}
template <class T>
typename  Queue<T>::ConstIterator Queue<T>::begin() const{
    return Queue<T>::ConstIterator(first);
}
template <class T>
typename  Queue<T>::ConstIterator Queue<T>::end() const{
    return nullptr;
}














