#include <iostream>
#include <cassert>
#include "String.h"
#include <cstring>

using namespace std;

int main()
{
    bool DEBUG = true;

    String s1; // s1 == ""
    assert(s1.length() == 0);
    if(DEBUG) cout << "Pass block 1" << endl;

    String s2("hi");  // s2 == "hi"
    assert(s2.length() == 2);
    if(DEBUG) cout << "Pass block 2" << endl;

    String s3(s2);  // s3 == "hi"
    assert(s3.length() == 2);
    assert(s3[0] == 'h');
    assert(s3[1] == 'i');
    if(DEBUG) cout << "Pass block 3" << endl;

    s1 = s2;  // s1 == "hi"
    assert(s1 == s2);
    if(DEBUG) cout << "Pass block 4" << endl;

    s3 = "bye";  // s3 == "bye"
    assert(s3.length() == 3);
    assert(s3[0] == 'b');
    assert(s3[1] == 'y');
    assert(s3[2] == 'e');
    s1 += "re";  // s1 == "hire"
    assert(s1 == "hire");
    if(DEBUG) cout << "Pass block 5" << endl;
    s1 += "d"; // s1 == "hired"
    assert(not (s1 == "hire"));

    cout << "SUCCESS" << endl;
}

