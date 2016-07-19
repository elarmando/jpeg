#ifndef JFIFREADER_H
#define JFIFREADER_H
#include "jpegmarker.h"

#include <string>
#include <iostream>
#include <fstream>



using namespace std;

class JfifReader
{
private:
    string pathFile;
public:
    JfifReader(const std::string &a);
    void readHeader();
    void read2bytes(std::istream &, uint2 &outbytes);
};

#endif // JFIFREADER_H
