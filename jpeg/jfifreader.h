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


class SOSComponentDescriptor{
public:
    SOSComponentDescriptor();


    char componentIdentifier;
    char dcHuffmanTable;
    char acHuffmanTable;
};

class SOS{

public:
    SOS();
    char componentCount;

     //descriptor
    std::vector<SOSComponentDescriptor> componentDescriptors;

   // char componentIdentifier;
   // char dcHuffmanTable;
   // char acHuffmanTable;

    char spectralSelectionStart;
    char spectralSelectionStop;

    char succesiveApproximation;
};

class DHT{
 public:

    DHT();

    char classNum;
    char identifier;
    std::vector<char> countHuffmanCodes;
    std::vector<char> symbols;


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
    std::vector<DHT> _dhts;

    SOF0 _sof0;
    SOS _sos;
    DHT _dht;




    std::ifstream _stream;

    void skipAppMarkers();
    void readSequenceOfDQT(std::vector<DQT> &dqts, bool skipmarker = false);
    void readDQT(std::vector<DQT> dqts);

    void readSOF0(SOF0 &sof0);
    void readSOS(SOS &sos);

    void readDHT(DHT &dht, bool skipmarker = false);
    void readDHT(std::vector<DHT> &dht);

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
