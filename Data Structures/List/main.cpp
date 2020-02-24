// main.cpp

#include <iostream>
#include "List.h"

using namespace std;

int main() 
{
    List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);

    cout << l[2];

    l.reverse;

    for(int i = 1; i < my_size; i++) {
        cout << l[i - 1];
    }

    return 0;
}
