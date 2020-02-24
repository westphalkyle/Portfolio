//
//  table.cpp
//  CSE_461_Project
//
//  Created by Kyle Westphal on 11/19/19.
//

#include "table.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

Table::Table(string diskname,int numberOfBlocks,int blockSize, string flatfile, string indexfile):Filesys(diskname, numberOfBlocks, blockSize) {
    newFile(flatfile);
    newFile(indexfile);
    this->flatfile = flatfile;
    this->indexfile = indexfile;
}
int Table::Build_Table(string input_file) {
    ifstream infile;
    infile.open(input_file.c_str());
    string record;
    int count = 0;
    getline(infile, record);
    vector<string> key;
    vector<string> iBlock;
    ostringstream outstream;
    
    while(!infile.eof() && infile.good()) {
        // Process Record
        string primaryKey;
        primaryKey = record.substr(0, 5);
        vector<string>blocks = block(record, getBlockSize());
        int blockID = addBlock(flatfile, blocks[0]);
        outstream << primaryKey << " " << blockID << " ";
        count++;
        if (count == 4) {
            // Time to addBlock
            vector<string> blocks2 = block(outstream.str(), getBlockSize());
            addBlock(indexfile, blocks2[0]);
            count = 0;
            outstream.str("");
        } // if
        getline(infile, record);
    } // while
    return 1;
}

int Table::Search(string value) {
    string date = value;
    if(value == "") {
        cout << "What date would you like to search for: ";
        cin >> date;
    }
    date = date.substr(0,5);
    cout << "Searching for record with date: " << date << "." << endl;
    string buffer;
    int block = IndexSearch(date);
    readBlock(flatfile, block, buffer);
    cout << buffer << endl;
    cin.clear();
    return 1;
}

int Table::IndexSearch(string value) {
    istringstream instream;
    int blockID = getFirstBlock(indexfile);
    // TODO: Check is blockID is -1
    while (blockID != 0) {
        string buffer, k;
        int b;
        readBlock(indexfile, blockID, buffer);
        instream.str(buffer);
        for (int i = 0; i <= 4; i++) {
            instream >> k >> b;
            if (k == value) return b;
        }
        blockID = nextBlock(indexfile, blockID);
    } // while
    return 0;
}
