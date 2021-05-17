//
// Created by Stefan on 5/17/2021.
//

#ifndef SET_SET_H
#define SET_SET_H
#include <memory>

template <typename T>
class Set {
public:

    virtual auto insert     (T const &) noexcept -> bool = 0;
    virtual auto erase      (T const &) noexcept -> bool = 0;
    virtual auto contains   (T const &) noexcept -> bool = 0;

    ///virtual auto reunion (Set const &) const noexcept -> Set = 0;

    virtual auto reunite    (Set const &) noexcept -> Set & = 0;
    virtual auto subtract   (Set const &) noexcept -> Set & = 0;
    virtual auto intersect  (Set const &) noexcept -> Set & = 0;

    [[nodiscard]] virtual auto empty    () const noexcept -> bool = 0;
    [[nodiscard]] virtual auto size     () const noexcept -> size_t = 0;

    [[nodiscard]] virtual auto toString () const noexcept -> std::string = 0;

    friend auto operator << (std::ostream& buffer, Set const & s) noexcept -> std::ostream&{
        return (buffer << s.toString());
    }

protected:

    Set() noexcept = default;
    virtual  ~Set() noexcept = default;

};



#endif //SET_SET_H
