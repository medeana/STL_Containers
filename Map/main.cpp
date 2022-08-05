#include "map.hpp"

int main(){
    ft::map<char, int> m;
    m.insert(ft::make_pair('d', 4));
    m.print();
}