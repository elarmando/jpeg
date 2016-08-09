#include "jfifreader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>


DQT::DQT(){

}

void JfifReader::skipAppMarkers()
{
    uint2 marker = 0;
    uint2 length = 0;

    read2bytes(_stream, marker);

    while(JpegMarker::isAPP(marker)){


        read2bytes(_stream, length);

        length -=2;
       //  std::cout<<"pos "<< _stream.tellg();
       // std::cout<<" marker "<<hex<<marker;
        //std::cout<<" lenght "<<dec<<length<<'\n';


        _stream.seekg( length, std::ios_base::cur);




        read2bytes(_stream, marker);

    }

    _stream.seekg(-2, std::ios::cur);
}

void JfifReader::readDQT(DQT &dqt, bool skipmarker)
{
    uint2 marker = 0, len = 0;


    if(!skipmarker){
        read2bytes(_stream, marker);

        if(JpegMarker::DQT != marker)
            return;
    }


    read2bytes(_stream, len);

    char byte, identifier, size;
    int tableLength = 0;

    _stream.read(&byte, 1);

    identifier = 0x0F & byte;
    size = (0xF0 & byte)>>4;

    if(size == 0){
        size = 1;
        tableLength = 64;
    }
    else{
        size = 2;
        tableLength = 128;
    }


    dqt.table.resize(tableLength);

    _stream.read(&dqt.table[0], tableLength);

    dqt.identifier = 0x0F & byte;
    dqt.size = size;

}

void JfifReader::readDQT(std::vector<DQT> dqts)
{
    uint2 marker = 0;

    read2bytes(_stream, marker);


    while(marker == JpegMarker::DQT){

        DQT n;
        dqts.push_back(n);

        DQT &l = dqts.back();

        readDQT(l, true);


        read2bytes(_stream, marker);
    }


    _stream.seekg(-2, std::ios_base::cur);
}

JfifReader::JfifReader(const std::string &a):
    pathFile(a),
    _stream(pathFile.c_str(), std::ios::binary)
{
    _stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

}

JfifReader::~JfifReader()
{

}

void JfifReader::validateFile(istream &stream)
{
    uint2 marker;
    read2bytes(stream, marker);

    if(marker != JpegMarker::SOI)
        throw std::logic_error("No jfif file in header");


    read2bytes(stream, marker);

    if(marker != JpegMarker::APP0)
        throw std::logic_error("No app0 marker in header");

    read2bytes(stream, marker);

    char jfifstring[5];

    stream.read(jfifstring, 5);

    if(stream.gcount() < 5)
         throw std::logic_error("No jfif string in header");

    if(jfifstring[0] != 'J' || jfifstring[1] != 'F' ||
       jfifstring[2] != 'I' ||  jfifstring[3] != 'F' ||  jfifstring[4] != 0)
         throw std::logic_error("No jfif string in header");


}

void JfifReader::read()
{
    this->readHeader();
    this->skipAppMarkers();
    this->readDQT(this->_dqts);


}



void JfifReader::readHeader()
{
    //std::ifstream stream(pathFile.c_str(), std::ios::binary);

    std::istream &stream = _stream;


    if(!stream.good())
        throw std::logic_error("could not open file");

    this->validateFile(stream);

    uint2 marker;

    read2bytes(stream, marker);

    if(marker == JpegMarker::APP0){
        //TODO read extra app0 data
        std::logic_error("read extra app0 header is missing");
    }

    versionMajorId = (char)((marker & 0xFF00)>>8);
    versionMinorId = (char)(unsigned char)(marker & 0x00FF);


    stream.read(&units, 1);

    read2bytes(stream, xDensity);
    read2bytes(stream, yDensity);

    stream.read(&xThumbnail, 1);
    stream.read(&yThumbnail, 1);

    long int size = 3*((int)xThumbnail) * ((int)yThumbnail);

    if(size > 0){
        thumbnail.resize(size);
        stream.read(&thumbnail[0], size);
    }



}



void JfifReader::readTable()
{
    uint2 twobytes = 0;

    read2bytes(_stream, twobytes);

    if(JpegMarker::DHT == twobytes){
        std::cout<<"Read tables";
    }
}

void JfifReader::read2bytes(istream &stream, uint2 &outbytes)
{
    unsigned char bytes[2];

    stream.read((char*)bytes, 2);

    outbytes = ((int)(bytes[0]) << 8 ) + bytes[1];

}

