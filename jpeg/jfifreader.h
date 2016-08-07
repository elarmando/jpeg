#ifndef JFIFREADER_H
#define JFIFREADER_H
#include "jpegmarker.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


class DQT {
public:
    DQT();

    char identifier;
    char size;
    std::vector<char> table;
};


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

    std::vector<char> thumbnail;

    DQT _dqt;
    std::ifstream _stream;

    void skipAppMarkers();
    void readDQT();


public:
    JfifReader(const std::string &a);
    ~JfifReader();
    void validateFile(std::istream &);

    void read();
    void readHeader();

    void readTable();
    void read2bytes(std::istream &, uint2 &outbytes);
};

#endif // JFIFREADER_H
