//
//  main.cpp
//  cppfuncsXcode
//
//  Created by Kaiyin Zhong on 23/07/14.
//  Copyright (c) 2014 com.mycomp. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <algorithm>
#include <fstream> 
#include <boost/algorithm/string.hpp>

typedef unsigned int  uint;

// count lines of a file
uint countlines(std::string fn) {
    std::ifstream in_file(fn);
    uint nlines =  (uint) std::count(std::istreambuf_iterator<char>(in_file), std::istreambuf_iterator<char>(), '\n');
    return nlines;
}

// print each line of a file
void printlines(std::string fn) {
    std::ifstream in_file(fn);
    std::string tmpline;
    while(in_file) {
        std::getline(in_file, tmpline);
        std::cout << tmpline << "\n";
    }
}

// get the last line of a file
std::string lastline(std::string fn) {
    std::ifstream in_file(fn);
    std::string tmpline;
    unsigned char tmpchar;
    in_file.seekg(-1, in_file.end);
    tmpchar = in_file.get();
    
    // if the last char is a newline, ignore it
    if(tmpchar == '\n') {
        in_file.seekg(-2, in_file.end);
    } else {
        in_file.seekg(-1, in_file.end);
    }
    
    // trace back the file until a newline is read
    tmpchar = in_file.get();
    while(true) {
        std::cout << tmpchar << " is retrieved.\n";
        if(tmpchar != '\n') {
            in_file.seekg(-2, in_file.cur);
            tmpchar = in_file.get();
        } else {
            break;
        }
    }
    
    // read the last line
    std::getline(in_file, tmpline);
    return tmpline;
}

// check if a file has trailing whitespaces
bool checktrail(std::string fn) {
    std::string llast = lastline(fn);
    boost::algorithm::trim(llast);
    bool checktrail_res = llast == "" ? true : false;
    if (checktrail_res) {
        std::cout << "It has trailing whitespaces!" << "\n";
    } else {
        std::cout << "OK, no trailong whitespaces." << "\n";
    }
    return checktrail_res;
}

//std::vector<std::string> split(const std::string &s, char delim) {
//    std::vector<std::string> elems;
//    std::stringstream ss(s);
//    std::string item;
//    while (std::getline(ss, item, delim)) {
//        if(not item.empty()) {
//            elems.push_back(item);
//        }
//    }
//    return elems;
//}
//
//size_t nCols(std::string fn) {
//    std::ifstream in_file(fn);
//    std::string tmpline;
//    std::getline(in_file, tmpline);
//    
//    std::vector<std::string> strs;
//    strs = split(tmpline, ' ');
//    return strs.size();
//}

void testerase() {
    std::vector<std::string> svec {"", "", "hi", "there", ""};
    svec.erase(std::remove_if(svec.begin(), svec.end(), [](std::string const& s) {return s=="";}));
    for(int i=0; i<svec.size(); i++) {
        std::cout << svec[i] << "\n";
    }
}


int main(int argc, const char * argv[])
{
    // insert code here...
    std::string tmpfn = "/tmp/testfile";
    uint n = countlines(tmpfn);
    std::cout << "File lines: " << n << "\n";
    checktrail(tmpfn);
//    std::cout << "It has " << nCols(tmpfn) << " columns" << "\n";
    testerase();
    
    return 0;
}

