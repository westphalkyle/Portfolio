// String.spp
#include "String.h"
#include <cstring>
using namespace std;

String::String() 
{
    size = 0;
    buffer = 0;
}

String::String(const String& op) 
{
    size = op.size;
    buffer = new char[size];
    for (int i = 0; i < size; i++) {
        buffer[i] = op.buffer[i];
    }
}

String::String(const char* op) 
{
    size = strlen(op);
    buffer = new char[size];
    for (int i = 0; i < size; i++) {
        buffer[i] = op[i];
    }
    cout << size << endl;
}

String::~String() 
{
    delete[] buffer;
}


int String::length() 
{
    return size;
}

char & String::operator[](const unsigned int i)
{
    return buffer[i];
}

String String::operator=(const String &s)
{
    delete[] buffer;
    size = s.size;
    buffer = new char[size];
    cout << size << endl;
    for (int i = 0; i < size; i++) {
        cout << "Itt #: " << i << endl;
        buffer[i] = s.buffer[i];
        cout << "Buffer[i] " << buffer[i] << endl;
        cout << "s[i] " << s.buffer[i] << endl;
    }
    return *this;
}

bool operator==(const String &s, const String &t) 
{
    for (int i = 0; s.size && t.size; i++) {
        if (s.buffer[i]==t.buffer[i]){
	}
	else if (s.buffer[i]<t.buffer[i]){
	    return false;
	}
	else if (s.buffer[i]>t.buffer[i]){
	    return false;
	}
    }
}

bool operator<=(const String &s, const String &t) 
{
    for (int i = 0; s.size && t.size; i++) {
        if (s.buffer[i]==t.buffer[i]){
        }
        else if (s.buffer[i]<t.buffer[i]){
        }
        else if (s.buffer[i]>t.buffer[i]){
            return false;
        }
	else return true;
    }
}

bool operator<(const String &s, const String &t) 
{
    for (int i = 0; s.size && t.size; i++) {
        if (s.buffer[i]==t.buffer[i]){
	    return false;
        }
        else if (s.buffer[i]<t.buffer[i]){
        }
        else if (s.buffer[i]>t.buffer[i]){
            return false;
        }
        else return true;
    }
}

ostream & operator<<(ostream & out, const String &s) 
{
    for (int i = 0; s.size; i++) {
        out << s.buffer[i];
    }
    return out;
}

String String::operator+=(const String & source)
{
    int temp_size = size + source.size;
    char * temp;
    temp = new char[temp_size];
    int i;
    for (i = 0; i < size; i++) {
        temp[i] = buffer[i];
    }
    for (int j = 0; j < source.size; j++, i++) {
        temp[i] = source.buffer[j];
    }
    delete [] buffer;
    size = temp_size;
    buffer = temp;
    return *this;
}



