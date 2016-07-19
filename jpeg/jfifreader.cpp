#include "jfifreader.h"

#include <iostream>
#include <fstream>



JfifReader::JfifReader(const std::string &a):
    pathFile(a)
{

}

void JfifReader::readHeader()
{
    std::ifstream stream(pathFile.c_str(), std::ios::binary);

    uint2 marker;
    stream>>marker;

    if(marker == JpegMarker::SOI){
        std::cout<<" START OF IMAGE "<<'\n';
    }


}

void JfifReader::read2bytes(istream &stream, uint2 &outbytes)
{
    char bytes[2];

}

