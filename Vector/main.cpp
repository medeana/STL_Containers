#include "vector.hpp"
#include <vector>

int main(){
    std::vector<int> b1(5, 6);
    std::vector<int> b2(5, 1);

    std::vector<int>::iterator it2;
    std::vector<int>::iterator ite2;
    it2 = b1.begin();
    ite2 = b1.end();

    b2.insert(b2.begin() + 2, it2, ite2);
    it2 = b2.begin();
    ite2 = b2.end();

    ft::vector<int> v1(5, 6);
    ft::vector<int> v2(5, 1);

    ft::vector<int>::iterator it;
    ft::vector<int>::iterator ite;
    it = v1.begin();
    ite = v1.end();

    v2.insert(v2.begin() + 2, it, ite);
    it = v2.begin();
    ite = v2.end();
    while (it != ite && it2 != ite2){
        std::cout << *it2 << "  |  " << *it << std::endl;
        it++;
        it2++;
    }
    std::cout << v2.capacity() << "  " << b2.capacity() << std::endl;
    // while (it2 != ite2){
    // std::cout << *it2 << std::endl;
    // it2++;
    // }
    // ft::vector<int> v2(5, 3);

    // ft::vector<int>::iterator it2;
    // ft::vector<int>::iterator ite2;
    // it2 = v2.begin() + 2;
    // v2.insert(it2, 3, 88);
    // it2 = v2.begin();
    // ite2 = v2.end();
    // while(it != ite && it2 != ite2)
    // {
    //     std::cout << *it << "  |  " << *it2 << std::endl; 
    //     it++;
    //     it2++;
    // }
    // ft::vector<int> v1(15);

    // for (int i = 0; i < 30; i++)
    // {
    //     v1.push_back(i);
    //     // std::cout << v1[i] << std::endl;

    // }

    // ft::vector<int>::iterator it;
    // ft::vector<int>::iterator ite;

    // it = v1.begin() + 3;
    // ite = v1.end();

    // // while (it != ite)
    // // {
    // //     std::cout << *it << std::endl;
    // //     it++;
    // // }

    // ft::vector<int> v3(it, ite);

    // ft::vector<int>::iterator it2;
    // ft::vector<int>::iterator ite2;

    // it2 = v3.begin();
    // ite2 = v3.end();

    // while (it2 != ite2)
    // {
    //     std::cout << *it2 << std::endl;
    //     it2++;
    // }
}