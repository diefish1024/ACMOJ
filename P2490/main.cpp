#include "RollingHash.hpp"
#include <iostream>

//p1=3 p2=5
int main()
{
    RollingHash rh;
    std::pair<long long, long long> p = rh.getp();
    std::cout << p.first << " " << p.second << std::endl;
    rh.append('a');
    rh.append('s');
    rh.append('d');
    rh.append('d');
    std::pair<long long, long long> re = rh.getHash(1, 4);
    std::cout << re.first << " " << re.second << std::endl;
    rh.append('e');
    re = rh.getHash(1, 4);
    std::cout << re.first << " " << re.second << std::endl;
    rh.append('z');
    re = rh.getHash(3, 5);
    std::cout << re.first << " " << re.second << std::endl;
    rh.append('s');
    rh.append('k');
    rh.append('m');
    rh.append('s');
    rh.append('k');
    rh.append('m');
    re = rh.getHash(7, 10);
    std::cout << re.first << " " << re.second << std::endl;
    return 0;
}