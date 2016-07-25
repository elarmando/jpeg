#include "jfifreader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>


JfifReader::JfifReader(const std::string &a):
    pathFile(a)
{
    thumbnail =  nullptr;
}

JfifReader::~JfifReader()
{
    if(thumbnail){
        delete []thumbnail;
    }
}

void JfifReader::validateFile(istream &stream)
{
    uint2 marker;
    read2bytes(stream, marker);

    if(marker != JpegMarker::SOI)
        std::logic_error("No jfif file in header");


    read2bytes(stream, marker);

    if(marker != JpegMarker::APP0)
        std::logic_error("No app0 marker in header");

    read2bytes(stream, marker);

    char jfifstring[5];

    stream.read(jfifstring, 5);

    if(stream.gcount() < 5)
         std::logic_error("No jfif string in header");

    if(jfifstring[0] != 'J' || jfifstring[1] != 'F' ||
       jfifstring[2] != 'I' ||  jfifstring[3] != 'F' ||  jfifstring[4] != 0)
         std::logic_error("No jfif string in header");


}

void JfifReader::readHeader()
{
    std::ifstream stream(pathFile.c_str(), std::ios::binary);
    this->validateFile(stream);

    uint2 marker;

    read2bytes(stream, marker);

    if(marker == JpegMarker::APP0){
        //TODO read extra app0 data
        std::logic_error("read extra app0 header is missing");
    }

    versionMajorId = (char)((marker & 0xFF00)>>8);
    versionMinorId = (char)(unsigned char)(marker & 0x00FF);


}

void JfifReader::read2bytes(istream &stream, uint2 &outbytes)
{
    unsigned char bytes[2];

    stream.read((char*)bytes, 2);

    outbytes = ((int)(bytes[0]) << 8 ) + bytes[1];

}

