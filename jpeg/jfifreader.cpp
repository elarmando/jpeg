#include "jfifreader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>


JfifReader::JfifReader(const std::string &a):
    pathFile(a)
{

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

void JfifReader::readHeader()
{
    std::ifstream stream(pathFile.c_str(), std::ios::binary);
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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

void JfifReader::read2bytes(istream &stream, uint2 &outbytes)
{
    unsigned char bytes[2];

    stream.read((char*)bytes, 2);

    outbytes = ((int)(bytes[0]) << 8 ) + bytes[1];

}

