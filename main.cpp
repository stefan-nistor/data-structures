#include <iostream>
#include "src/UnorderedSet.h"
#include "src/OrderedSet.h"

class C;

int main() {
    UnorderedSet<int> set {1 ,2 ,4 ,5 ,3 ,3 ,2};
    UnorderedSet<char> list;
    OrderedSet<int, C> ord;

    Set<int>* a = new UnorderedSet<int> {2 ,5, 3, 6, 3 ,4};
    Set<int>* b = new UnorderedSet<int>;

    *b = *a;

    delete a;

    std::cout << b->toString() << '\n';

    std::cout << set.toString() << '\n';

    set.insert(3);
    std::cout << set.toString() << '\n';

    set.insert(9);
    std::cout << set.toString() << '\n';

    set.erase(1);
    std::cout << set.toString() << '\n';

    std::cout << set.contains(3) << ' ' << set.contains(10) << ' ' << set.empty() << ' ' << set.size() << ' ' << list.empty();

    return 0;
}
