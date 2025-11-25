#include <iostream>

#include "../src/linklist.cpp"

int main() {
    LinkList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_front(3);
    l1.push_front(4);
    l1.insert(0, 0);
    l1.insert(1, 11);
    l1.insert(6, 66);
    l1.insert(3, 33);
    l1.remove(0);
    // l1.remove(7);
    l1.remove(2);
    l1.remove(0);
    l1.remove_value(66);
    std::cout << l1.get(0) << " " << l1[0] << std::endl;
    int& a = l1.get(0);
    int b = l1.get(0);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    a = 10;
    l1.print();
    b = 100;
    l1.print();
    return 0;
};