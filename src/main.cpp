#include <iostream>

#include "seqlist.cpp"

int main() {
    SeqList<int> int_seqlist;
    std::cout << "---------------SeqList---------------" << std::endl;
    std::cout << "int seqlist: ";
    // int_seqlist.print();
    // std::cout << "length: " << int_seqlist.size() << std::endl;
    // std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;
    for (int i = 0; i < 15; i++) {
        int_seqlist.push_back(i);
        //     int_seqlist.print();
        //     std::cout << "length: " << int_seqlist.size() << "; ";
        //     std::cout << "capacity: " << int_seqlist.get_capacity() <<
        //     std::endl;
    }
    int_seqlist.print();
    std::cout << "length: " << int_seqlist.size() << std::endl;
    std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;

    int_seqlist.insert(0, 10101);
    int_seqlist.print();
    std::cout << "length: " << int_seqlist.size() << "; ";
    std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;
    int_seqlist.insert(16, 1616);
    int_seqlist.print();
    std::cout << "length: " << int_seqlist.size() << "; ";
    std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;
    // int_seqlist.insert(18,181818);
    // int_seqlist.print();

    int_seqlist.pop_back();
    int_seqlist.print();
    std::cout << "length: " << int_seqlist.size() << "; ";
    std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;

    int_seqlist.erase(0);
    int_seqlist.print();
    std::cout << "length: " << int_seqlist.size() << "; ";
    std::cout << "capacity: " << int_seqlist.get_capacity() << std::endl;

    const SeqList<int> const_int_seqlist = int_seqlist;
    std::cout << "int_seqlist[1]: " << int_seqlist[1] << std::endl;
    std::cout << "const_int_seqlist[1]: " << const_int_seqlist[1] << std::endl;
    int_seqlist[1] = 100;
    // const_int_seqlist[1] = 100;
    int_seqlist.print();

    SeqList<int>::Iterator it0 = int_seqlist.begin();
    ++it0;
    it0++;
    --it0;
    it0--;
    SeqList<int>::Iterator it1 = int_seqlist.end();
    std::cout << (it0 < it1) << " " << (it0 <= it1) << std::endl;
    std::cout << (it0 > it1) << " " << (it0 >= it1) << std::endl;
    std::cout << (it0 - it1) << std::endl;
    std::cout << (it1 - it0) << std::endl;
    return 0;
}