#ifndef JFIFREADER_H
#define JFIFREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include "jpegmarker.h"


using namespace std;

class JfifReader
{
private:
    string pathFile;
public:
    JfifReader(const char *);
    void readHeader();
    void read2bytes(std::istream &, uint2 &outbytes);
};

#endif // JFIFREADER_H
