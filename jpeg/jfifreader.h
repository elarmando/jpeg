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

class ComponentSOF{
public:
    ComponentSOF();
    char identifier;
    char horizontalSampling;
    char verticalSampling;
    char quantizationIdentifier;
};

class SOF0{
public:
    SOF0();
     char precision;
     uint2 height;
     uint2 width;
     char numComponents;

     std::vector<ComponentSOF> components;
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
    std::vector<DQT> _dqts;

    SOF0 _sof0;


    std::ifstream _stream;

    void skipAppMarkers();
    void readDQT(DQT &, bool skipmarker = false);
    void readDQT(std::vector<DQT> dqts);

    void readSOF0(SOF0 &sof0);
    void readSOFBaseline();

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
