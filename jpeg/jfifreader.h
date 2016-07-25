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

    char versionMajorId;
    char versionMinorId;
    char units;

    uint2 xDensity;
    uint2 yDensity;

    char xThumbnail;
    char yThumbnail;

    char *thumbnail;



public:
    JfifReader(const std::string &a);
    ~JfifReader();
    void validateFile(std::istream &);
    void readHeader();
    void read2bytes(std::istream &, uint2 &outbytes);
};

#endif // JFIFREADER_H
