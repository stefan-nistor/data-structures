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
    /// typename forces the compiler to generate Set<T> class
    using Node = typename  Set<T> :: Node;
public:

    UnorderedSet() noexcept = default;
    UnorderedSet(std::initializer_list<T> list) noexcept;
    UnorderedSet( UnorderedSet&) noexcept;
    ~UnorderedSet() noexcept override;


    auto insert     (T const &) noexcept -> bool override;
    auto erase      (T const &) noexcept -> bool override;
    auto contains   (T const &) noexcept -> bool override;

    auto reunion (UnorderedSet const &) const noexcept -> UnorderedSet;

    auto reunite    (Set<T> const &) noexcept -> UnorderedSet & override;
    auto intersect  (Set<T> const &) noexcept -> UnorderedSet & override;
    auto subtract   (Set<T> const &) noexcept -> UnorderedSet & override;

    auto clear () noexcept -> void override;

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

    auto operator=(Set<T> const &) noexcept -> UnorderedSet& override;

    inline UnorderedSet& operator=(UnorderedSet<T> const & o) noexcept {
        return this->operator=((Set<T> const &) o);
    }
};

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
    if(set.empty())
        return *this;

    for (const auto &item : set)
        if(!this->contains(item))
            this->insert(item);
    return *this;
}

template<typename T>
auto UnorderedSet<T>::intersect(const Set<T> & set) noexcept -> UnorderedSet & {
    if(set.empty())
        return *this;

    for (const auto &item : set)
        if(!this->contains(item))
            this->erase(item);
    return *this;
}

template<typename T>
auto UnorderedSet<T>::subtract(const Set<T> & set) noexcept -> UnorderedSet & {
    if(set.empty())
        return *this;

    for (const auto &item : set)
        if(this->contains(item))
            this->erase(item);
    return *this;
}

#include <sstream>
#include <iostream>

template<typename T>
auto UnorderedSet<T>::toString() const noexcept -> std::string {
    if(this->empty())
        return std::string(" [ ]");

    std::stringstream out;
    out << "[ ";

    for(auto it : *this)
        out << it << ", ";
    auto s = out.str();

    return s.substr(0,s.size() - 2).append(" ]");
}

template<typename T>
UnorderedSet<T>::~UnorderedSet() noexcept {
    this->clear();
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

template<typename T>
template<typename funcType>
auto UnorderedSet<T>::filter(const funcType & f) noexcept -> UnorderedSet & {
    for(auto &it : this)
        if(f(it))
            it.erase();

    return this;
}

template<typename T>
template<typename funcType>
auto UnorderedSet<T>::foreach(const funcType & f) const noexcept -> void {
    for(auto & it : this)
        f(it);
}

template<typename T>
auto UnorderedSet<T>::reunion(const UnorderedSet & set) const noexcept -> UnorderedSet {

    UnorderedSet<T> result(this);
    result.reunite(set);
    return UnorderedSet();
}

template<typename T>
UnorderedSet<T>::UnorderedSet(UnorderedSet & set) noexcept {
    for (const auto &item : set)
        this->insert(item);
}

template<typename T>
auto UnorderedSet<T>::operator=(Set<T> const & set) noexcept -> UnorderedSet& {
    /// clear lvalue then copy rvalue in lvalue
    this->clear();

    for (const auto &item : set)
        this->insert(item);

    return *this;
}

template<typename T>
auto UnorderedSet<T>::clear() noexcept -> void {
    auto current = this->_front;

    while (current != nullptr){
        auto temp = current;
        current = current->next;
        delete temp;
    }
}

#endif //SET_UNORDEREDSET_H
