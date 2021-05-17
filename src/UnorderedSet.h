//
// Created by Stefan on 5/17/2021.
//

#ifndef SET_UNORDEREDSET_H
#define SET_UNORDEREDSET_H
#include "Set.h"
#include <initializer_list>

template <typename  T>
class UnorderedSet : public Set <T> {
private:

    struct Node {
        T value;
        Node *next;
    };

    Node * _front = nullptr;
    size_t _size = 0u;
    friend class Iterator;

public:

    UnorderedSet() noexcept = default;
    UnorderedSet(std::initializer_list<T> list) noexcept;
    ~UnorderedSet() noexcept override;


    class Iterator;

    auto insert     (T const &) noexcept -> bool override;
    auto erase      (T const &) noexcept -> bool override;
    auto contains   (T const &) noexcept -> bool override;

    auto reunite    (Set<T> const &) noexcept -> UnorderedSet & override;
    auto intersect  (Set<T> const &) noexcept -> UnorderedSet & override;
    auto subtract   (Set<T> const &) noexcept -> UnorderedSet & override;

    [[nodiscard]] auto toString   () const noexcept -> std::string override;

    [[nodiscard]] inline auto empty   () const noexcept -> bool override {return this->_size == 0;}
    [[nodiscard]] inline auto size    () const noexcept -> size_t override {return this->_size;}

    template<typename funcType>
    auto filter (funcType const &) noexcept -> UnorderedSet&;

    template<typename funcType>
    auto foreach (funcType const &) const noexcept -> void;

    template<typename funcType>
    auto count (funcType const &) const noexcept -> size_t;

    template<typename  funcType>
    auto any (funcType const & f) const noexcept -> bool {return this->count(f) > 0;}

    template<typename  funcType>
    auto all (funcType const & f) const noexcept -> bool {return this->count(f) == this->size();}

    inline auto begin () const noexcept -> Iterator {return this->_front;}
    inline auto end   () const noexcept -> Iterator {return nullptr;}

};

template<typename  T>
class UnorderedSet<T> :: Iterator{
private:

    using Node = UnorderedSet<T>::Node;
    Node mutable *node ;

public:

    Iterator(Node* node) noexcept {this-> node = node;}

    auto operator== (Iterator const &) const noexcept -> bool;
    auto operator!= (Iterator const &) const noexcept -> bool;
    auto operator++ () noexcept -> Iterator &;
    auto operator++ (int) noexcept -> Iterator;
    auto operator* () const noexcept -> T &;

};

template<typename T>
auto UnorderedSet<T>::Iterator::operator==(const UnorderedSet<T>::Iterator & it) const noexcept -> bool {
    return this->node == it.node;
}

template<typename T>
auto UnorderedSet<T>::Iterator::operator!=(const UnorderedSet<T>::Iterator & it) const noexcept -> bool {
    return !(this->node == it.node);
}

template<typename T>
auto UnorderedSet<T>::Iterator::operator++() noexcept -> UnorderedSet<T>::Iterator & {
    if(this -> node == nullptr)
        return *this;

    this->node = this->node->next;
    return *this;
}

template<typename T>
auto UnorderedSet<T>::Iterator::operator*() const noexcept -> T & {
    return this->node->value;
}


template<typename T>
auto UnorderedSet<T>::insert(const T & value) noexcept -> bool {

    auto current = this->_front;

    while(current != nullptr){
        if(current->value == value)
            return false;
        current = current->next;
    }

    Node* temp = new Node;
    temp->value = value;
    temp->next = this->_front;
    this->_front = temp;
    this->_size++;
    return true;
}

template<typename T>
auto UnorderedSet<T>::erase(const T & value) noexcept -> bool {
    auto current = this->_front;

    while (current->value != value){
        current = current->next;

        if (current->next == nullptr)
            return false;
    }

    current->next = current->next->next;
    current->next->value = value;
    this->_size--;
    return true;
}

template<typename T>
auto UnorderedSet<T>::contains(const T & value) noexcept -> bool {
    auto current = this->_front;
    while(current != nullptr){
        if(current->value == value)
            return true;
        current = current->next;
    }

    return false;
}

template<typename T>
auto UnorderedSet<T>::reunite(const Set<T> & set) noexcept -> UnorderedSet & {

    return *this;
}

template<typename T>
auto UnorderedSet<T>::intersect(const Set<T> &set) noexcept -> UnorderedSet & {

    return *this;
}

template<typename T>
auto UnorderedSet<T>::subtract(const Set<T> &set) noexcept -> UnorderedSet & {

    return *this;
}

#include <sstream>
template<typename T>
auto UnorderedSet<T>::toString() const noexcept -> std::string {
    if(this->empty())
        return std::string(" [ ]");

    std::stringstream out;
    out << "[ ";

    for(auto it : *this)
        out << it << ", ";

    out << " ]";

    return std::string(out.str());
}

template<typename T>
UnorderedSet<T>::~UnorderedSet() noexcept {
    auto current = this->_front;

    while (current != nullptr){
        auto temp = current;
        current = current->next;
        delete temp;
    }
}

template<typename T>
UnorderedSet<T>::UnorderedSet(std::initializer_list<T> list) noexcept {
    for(auto it : list)
        this->insert(it);
}

template<typename T>
template<typename funcType>
auto UnorderedSet<T>::count(const funcType & f) const noexcept -> size_t {
    size_t count;
    for (auto it : this)
        if(f(it))
            count ++;
    return count;
}


#endif //SET_UNORDEREDSET_H
