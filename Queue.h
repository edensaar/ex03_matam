#include <iostream>
using namespace std;

template <class T>
class Queue{
    struct Node
    {
        T data;
        Node* next;
        Node(const T& data , Node* next = nullptr): data(data) , next(next){};
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
    Queue<T>& operator=(const Queue&);
    T& front();
    T& front() const;
    void pushBack(T value);
    void popFront();
    int size()const;
    struct Iterator;
    Iterator begin();
    Iterator end();
    struct ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    void deletelist(Node *node);
    void deletelist();
    struct EmptyQueue{};
};

template <class T, class F>
Queue<T> filter(const Queue<T>& queue , F function);
template <typename T, class F>
void transform(Queue<T>& queue , F function);
template <typename T, class F>
T reduce(const Queue<T>& queue ,T first, F function);
template <class T>
Queue<T>::Queue() {
    try{
        this->first = nullptr;
    }
        //TODO - do i need to add something?
    catch (std::bad_alloc& e){
        throw(e);
    }
    this->last = this->first;
    this->index = -1;
}
template <class T>
void Queue<T>::deletelist(Node *node){
    if(node == nullptr){
        return;
    }
    while(node->next != nullptr){
        Node* n = node;
        node = node->next;
        delete n;
    }
    delete node;
}
template <class T>
void Queue<T>::deletelist(){
    while (this->index >= 0) {
        Node *n = this->first;
        this->first = this->first->next;
        delete n;
        this->index--;
    }
}
template <class T>
Queue<T>::Queue(const Queue& queue){
//try and except - if there is a prob with allocation
    try{
        this->first = nullptr;
    }
    catch (std::bad_alloc& e){
        throw(e);
    }
    this->index = -1;
    this->last = this->first;

    for (typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it){
        try{
            this->pushBack(*it);
        }
        catch(std::bad_alloc& e){
            deletelist(this->first);
            throw e;
        }
    }
    this->index = queue.index;

}
template <class T>
Queue<T>::~Queue() {
    while (this->index >= 0) {
        Node *n = this->first;
        this->first = this->first->next;
        delete n;
        this->index--;
    }
}
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue){

    if(this == &queue){
        return *this;
    }
    else
    {
        Node* temp_first;
        Node* temp_last ;
        int i = -1;
        try{
            for(const T& data: queue){
                if(i == -1){
                    temp_first  = new Node(data);
                    temp_last = temp_first;
                    i++;
                }
                else{
                    Node* newnode = new Node(data);
                    temp_last->next = newnode;
                    temp_last = newnode;
                    i++;
                }
            }
        }
        catch(...){
            deletelist(temp_first);
            throw;
        }
        Node* todelete = this->first;
        this->first = temp_first;
        this->last = temp_last;
        this->index = i;
        deletelist(todelete);


    }
    return *this;
}

template <class T>
void Queue<T>::pushBack(T value) {
    // TODO - add bad alloc
    if(this->index < 0)
    {
            this->first = new Node(value);
            this->last = this->first;
    }
    else
    {
            Node* new_node = new Node(value);
            this->last->next = new_node;
            this->last = new_node;
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
T& Queue<T>::front() const{
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

            this->first = nullptr;
            this->last = this->first;
            delete n;
        }
    }
    this->index--;
    return;
}
template <class T>
int Queue<T>::size()const
{
    return this->index + 1;
}

template <class T, class F>
Queue<T> filter(const Queue<T>& queue , F function)
{
    Queue<T> new_queue;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        if (function(*it)) {
            try{
                new_queue.pushBack(*it);
            }
            catch (std::bad_alloc& e){
            new_queue.deletelist();
            throw e;
            }
//            new_queue.pushBack(*it);

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

template <typename T, typename S, class F>
S reduce(const Queue<T>& queue ,S first, F function)
{
    S final = first;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it){
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
















