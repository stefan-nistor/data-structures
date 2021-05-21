//
// Created by Stefan on 5/17/2021.
//

#ifndef SET_SET_H
#define SET_SET_H
#include <memory>

template <typename T>
class Set {
protected:

    struct Node {
        T value;
        Node *next;
    };

    Node * _front = nullptr;
    size_t _size = 0u;
    friend class Iterator;

    Set() noexcept = default;

public:

    virtual  ~Set() noexcept = default;

    class Iterator;

    virtual auto insert     (T const &) noexcept -> bool = 0;
    virtual auto erase      (T const &) noexcept -> bool = 0;
    virtual auto contains   (T const &) noexcept -> bool = 0;

    /// virtual auto reunion (Set const &) const noexcept -> Set = 0;

    virtual auto reunite    (Set const &) noexcept -> Set & = 0;
    virtual auto subtract   (Set const &) noexcept -> Set & = 0;
    virtual auto intersect  (Set const &) noexcept -> Set & = 0;

    [[nodiscard]] virtual auto empty    () const noexcept -> bool = 0;
    [[nodiscard]] virtual auto size     () const noexcept -> size_t = 0;

    [[nodiscard]] virtual auto toString () const noexcept -> std::string = 0;

    virtual auto clear () noexcept -> void = 0;
    virtual Set & operator= (Set const &) noexcept = 0;
    friend auto operator << (std::ostream& buffer, Set const & s) noexcept -> std::ostream&{
        return (buffer << s.toString());
    }

    inline auto begin () const noexcept -> Iterator {return Iterator(this->_front);}
    inline auto end   () const noexcept -> Iterator {return Iterator(nullptr);}

};

template<typename  T>
class Set<T> :: Iterator{
private:

    using Node = Set<T>::Node;
    Node mutable *node ;

public:

    explicit Iterator(Node* node) noexcept {this-> node = node;}

    auto operator== (Iterator const &) const noexcept -> bool;
    auto operator!= (Iterator const &) const noexcept -> bool;
    auto operator++ () noexcept -> Iterator &;
    auto operator++ (int) noexcept -> Iterator;
    auto operator* () const noexcept -> T &;

};


template<typename T>
auto Set<T>::Iterator::operator==(const Set<T>::Iterator & it) const noexcept -> bool {
    return this->node == it.node;
}

template<typename T>
auto Set<T>::Iterator::operator!=(const Set<T>::Iterator & it) const noexcept -> bool {
    return !(this->node == it.node);
}

template<typename T>
auto Set<T>::Iterator::operator++() noexcept -> Set<T>::Iterator & {
    if(this -> node == nullptr)
        return *this;

    this->node = this->node->next;
    return *this;
}

template<typename T>
auto Set<T>::Iterator::operator*() const noexcept -> T & {
    return this->node->value;
}

template<typename T>
auto Set<T>::Iterator::operator++(int) noexcept -> Set<T>::Iterator {
    if (this -> node == nullptr)
        return *this;

    this->node = this->node->next;
    return this;
}
#endif //SET_SET_H