//
//  table.h
//  CSE_461_Project
//
//  Created by Kyle Westphal on 11/19/19.
//

#ifndef table_h
#define table_h

#include "filesys.h"
#include <stdio.h>
#include <string>


class Table : public Filesys {
public :
    Table(string diskname,int numberOfBlocks,int blockSize, string flatfile, string indexfile);
    int Build_Table(string input_file);
    int Search(string value);
private :
    string flatfile;
    string indexfile;
    int IndexSearch(string value);
};

#endif /* table_h */
