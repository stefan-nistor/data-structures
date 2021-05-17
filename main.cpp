#include <iostream>
#include "src/UnorderedSet.h"

int main() {
    UnorderedSet<int> set {1 ,2 ,4 ,5 ,3 ,3 ,2};
    UnorderedSet<char> list;
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
