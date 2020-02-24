// Kyle Westphal
// CSE 461

#include <iostream>
//#include "sdisk.h"
//#include "filesys.h"
#include "shell.h"
#include "table.h"

using namespace std;

int main() {
 
// This main program inputs commands to the shell.
// It inputs commands as : command op1 op2
// You should modify it to work for your implementation.

    //Sdisk sdisk = Sdisk("sdisk.txt",256,128);
    //Filesys fsys = Filesys("sdisk.txt",256,128);
    Shell shell = Shell("sdisk.txt",256,128);
    Table table = Table("sdisk.txt",256,128,"flatfile","indexfile");
    table.Build_Table("data.txt");
    
    string s;
    string command = "go";
    string op1, op2;

    while (command != "quit") {
        cin.clear();
        command.clear();
        op1.clear();
        op2.clear();
        cout << "$ ";
        getline(cin,s);
        
        size_t firstBlank = s.find(' ');
        if (firstBlank < s.length()) s[firstBlank] = '#';
        size_t secondBlank = s.find(' ');
        
        command = s.substr(0, firstBlank);
        
        if (firstBlank < s.length()) {
            op1 = s.substr(firstBlank + 1, secondBlank - firstBlank - 1);
        }
        
        if (secondBlank < s.length()) {
            op2 = s.substr(secondBlank + 1);
        }
        
        if (command == "dir") {
            shell.dir();
            continue;
        }
        
        if (command == "add") {
            // The variable op1 is the new file
            shell.add(op1);
            continue;
        }
        
        if (command == "del") {
            // The variable op1 is the file
            shell.del(op1);
            continue;
        }
        
        if (command == "type") {
            // The variable op1 is the file
            shell.type(op1);
            continue;
        }
        
        if (command == "copy") {
            // The variable op1 is the source file and the variable op2 is the destination file.
            shell.copy(op1, op2);
            continue;
        }
        if (command == "search") {
            // The variable op1 is the date
            table.Search(op1);
            continue;
        }
        if (command == "quit") {}
        else {cout << "command not found" << endl;}
        
    }
    return 0;
}

/** Previous Lab Main */
// Sdisk disk1("test1.txt",16,32);
 
 // Sdisk disk1("disk.txt", 128, 256);
 // Filesys fsys = Filesys("disk.txt", 128, 256);
 /*
 string block1, block2, block3, block4;
 for (int i=1; i<=32; i++) block1=block1+"1";
 for (int i=1; i<=32; i++) block2=block2+"2";
 disk1.putBlock(4,block1);
 disk1.getBlock(4,block3);
 cout << "Should be 32 1s : ";
 cout << block3 << endl;
 disk1.putBlock(8,block2);
 disk1.getBlock(8,block4);
 cout << "Should be 32 2s : ";
 cout << block4 << endl;
 */

//Lab 3/4
 /*
 Sdisk disk1("disk1.txt",256,128);
 Filesys fsys("disk1.txt",256,128);

 fsys.newFile("file1.txt");

 fsys.newFile("file2.txt");


 string bfile1;
 string bfile2;

 for (int i=1; i<=1024; i++) {
     bfile1+="1";
 }

 vector<string> blocks = disk1.block(bfile1, 128);

 int blocknumber = 0;

 for (int i=0; i < blocks.size(); i++) {
     blocknumber = fsys.addBlock("file1.txt", blocks[i]);
 }

 fsys.delBlock("file1.txt",fsys.getFirstBlock("file1.txt"));

 for (int i=1; i<=2048; i++)
    {
      bfile2+="2";
    }

 blocks = disk1.block(bfile2,128);

 for (int i=0; i< blocks.size(); i++)
    {
      blocknumber = fsys.addBlock("file2.txt",blocks[i]);
    }
 

 fsys.delBlock("file2.txt",blocknumber);
 */
