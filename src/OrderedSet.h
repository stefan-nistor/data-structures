//
// Created by Stefan on 5/23/2021.
//

#ifndef SET_ORDEREDSET_H
#define SET_ORDEREDSET_H
#include "Set.h"
#include <initializer_list>

namespace dataTypes {
    template <typename T>
    class Comparator{
    public:
        inline auto operator () (T const & a, T const & b) const noexcept -> bool{return a < b;}
    };
}

template <typename T, typename C = dataTypes::Comparator<T>>
class OrderedSet : public Set<T> {
private:
    using Node = typename Set<T> ::  Node;

public:
    OrderedSet() noexcept = default;
    OrderedSet(std::initializer_list<T>) noexcept;
    OrderedSet( OrderedSet &) noexcept;
    ~OrderedSet() noexcept override;

    auto insert     (T const &) noexcept -> bool override;
    auto erase      (T const &) noexcept -> bool override;
    auto contains   (T const &) noexcept -> bool override;

    auto reunion (OrderedSet const &) const noexcept -> OrderedSet;

    auto reunite    (Set<T> const &) noexcept -> OrderedSet & override;
    auto intersect  (Set<T> const &) noexcept -> OrderedSet & override;
    auto subtract   (Set<T> const &) noexcept -> OrderedSet & override;

    auto clear  () noexcept -> void override;
    auto reverse() noexcept -> void;

    [[nodiscard]] auto toString () const noexcept -> std::string override;

    [[nodiscard]] inline auto empty () const noexcept -> bool override {return this->_size == 0;}
    [[nodiscard]] inline auto size () const noexcept -> size_t override {return this->_size;}

    template<typename funcType>
    auto filter (funcType const &) noexcept -> OrderedSet &;

    template<typename funcType>
    auto foreach (funcType const &) const noexcept -> void;

    template<typename funcType>
    auto count (funcType const &) const noexcept -> size_t;

    template<typename  funcType>
    auto any (funcType const & f) const noexcept -> bool {return this->count(f) > 0;}

    template<typename  funcType>
    auto all (funcType const & f) const noexcept -> bool {return this->count(f) == this->size();}

    auto operator=(Set<T> const &) noexcept -> OrderedSet & override;

    inline OrderedSet & operator=(OrderedSet<T, C> const & o) noexcept {
        return this->operator=((Set<T> const &) o);
    }



};

template<typename T, typename C>
auto OrderedSet<T, C>::insert(const T & value) noexcept -> bool {
    C comparator;

    auto current = this->_front;

    while (current) {
        if(current->value == value)
            return false;
        current = current->next;
    }

    if ( comparator ( value, this->_front->value ) ) {
        this->_front = new Node { value, this->_front };
        this->_size ++;
        return true;
    }

    auto front = this->_front;

    while(front->next != nullptr){
        if(front->next->value == value)
            return false;
        if(comparator(value, this->_front->value)) {
            front->next = new Node{value, front->next};
            this->_size ++;
            return true;
        }

        front = front->next;
    }

    front->next = new Node {value, nullptr};
    this->_size++;
    return true;
}

//template<typename T, typename C>
//bool OrderedSet<T, C>::validate(const T & newValue, C comparator) const noexcept {
//    if(comparator (newValue, this->_front->value)){
//        auto *temp = new Node;
//        temp->value = value;
//        temp->next = this->_front;
//        this->_front = temp;
//        this->_size ++;
//        return true;
//    }
//    return false;
//}


#endif //SET_ORDEREDSET_H
