#include "jfifreader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>


DQT::DQT(){

}

ComponentSOF::ComponentSOF(){}

SOF0::SOF0(){}


SOSComponentDescriptor::SOSComponentDescriptor()
{

}

SOS::SOS()
{}




void JfifReader::skipAppMarkers()
{
    uint2 marker = 0;
    uint2 length = 0;

    read2bytes(_stream, marker);

    while(JpegMarker::isAPP(marker)){
        read2bytes(_stream, length);
        length -=2;      
        _stream.seekg( length, std::ios_base::cur);
        read2bytes(_stream, marker);

    }

    _stream.seekg(-2, std::ios::cur);
}

void JfifReader::readSequenceOfDQT(std::vector<DQT> &dqts, bool skipmarker)
{
    uint2 marker = 0, len = 0;


    if(!skipmarker){
        read2bytes(_stream, marker);

        if(JpegMarker::DQT != marker)
            return;
    }


    read2bytes(_stream, len);
    unsigned long bytesRead = 2;//counting the  2 bytes length

    while(bytesRead < len){

        DQT dqt;
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

        dqt.identifier = identifier;
        dqt.size = size;

        dqts.push_back(dqt);

        bytesRead+= tableLength + 1;//el tamaño de la tabla y un byte de la descripcion
    }



}

void JfifReader::readDQT(std::vector<DQT> dqts)
{
    uint2 marker = 0;

    read2bytes(_stream, marker);


    while(marker == JpegMarker::DQT){
        readSequenceOfDQT(dqts, true);
        read2bytes(_stream, marker);
    }


    _stream.seekg(-2, std::ios_base::cur);
}

void JfifReader::readSOF0(SOF0 &sof0)
{
    uint2 marker = 0;

    read2bytes(_stream, marker);

    if(marker != JpegMarker::SOF0)
        return;

    uint2 len = 0 ;

    read2bytes(_stream, len);


    _stream.read(&sof0.precision, 1);
    read2bytes(_stream, sof0.height);
    read2bytes(_stream, sof0.width);
    _stream.read(&(sof0.numComponents), 1);

    sof0.components.resize(0);


    for(int i = 0; i < sof0.numComponents; i+=1){
        ComponentSOF component;
        char sampling;

        _stream.read(&component.identifier, 1);
        _stream.read(&sampling, 1);
        _stream.read(&component.quantizationIdentifier, 1);

        component.horizontalSampling = (sampling & 0xF0) >>4;
        component.verticalSampling = (sampling & 0x0F);

        _sof0.components.push_back(component);

    }
}

void JfifReader::readSOS(SOS &sos)
{
    uint2 marker = 0, len = 0;

    read2bytes(_stream, marker);

    if(JpegMarker::SOS != marker){
        return;
    }

    read2bytes(_stream, len);



    _stream.read(&sos.componentCount, 1);

    sos.componentDescriptors.resize(sos.componentCount);

    for(char i = 0; i < sos.componentCount; i++){
        SOSComponentDescriptor descriptor;
          char descriptor1 = 0, descriptor2 = 0;
          _stream.read(&descriptor1, 1);
          _stream.read(&descriptor2, 1);

          descriptor.componentIdentifier  = descriptor1;
          descriptor.acHuffmanTable =  (descriptor2 & 0x0F);
          descriptor.dcHuffmanTable = (descriptor2 & 0xF0) >> 4;
    }


    _stream.read(&sos.spectralSelectionStart, 1);
    _stream.read(&sos.spectralSelectionStop, 1);
    _stream.read(&sos.succesiveApproximation, 1);


    auto initilPos = _stream.tellg();
    size_t lenData = 0;

    uint2 newmarker = 0xFF00;
     read2bytes(_stream, newmarker);

    while(!JpegMarker::isMarker(newmarker) || JpegMarker::isRST(newmarker)){//itera mientras no sea un marcador o si es Restart marker
        lenData+=2;

        read2bytes(_stream, newmarker);

    }



    if(len > 0){
        sos.dataScan.resize(lenData);

        _stream.seekg(initilPos);
        _stream.read(&sos.dataScan[0], lenData);
    }else{
        sos.dataScan.resize(0);
        _stream.seekg(-2,std::ios_base::cur);
    }



}

void JfifReader::readDHT(DHT &dht, bool skipmarker)
{

    if(skipmarker == false){
        uint2 marker = 0;

        read2bytes(_stream, marker);

        if(marker != JpegMarker::DHT)
            return;
    }



    uint2 len = 0;

    read2bytes(_stream, len);

    char firstByte;

    _stream.read(&firstByte, 1);
    dht.classNum = (firstByte & 0xF0) >> 4;
    dht.identifier = firstByte & 0x0F;

    dht.countHuffmanCodes.resize(16);

    _stream.read(&dht.countHuffmanCodes[0], 16);

    unsigned int sum = 0;

    auto ite = dht.countHuffmanCodes.begin();
    auto end = dht.countHuffmanCodes.end();

    for(;ite != end; ite++){

        char count = *ite;

        sum+= (unsigned char) count;

    }

    dht.symbols.resize(sum);

    _stream.read(dht.symbols.data(), sum);

}

void JfifReader::readDHT(std::vector<DHT> &dhts)
{

    uint2 marker = 0;

    read2bytes(_stream, marker);

    while(marker == JpegMarker::DHT){

        DHT dht;
        readDHT(dht, true);

        dhts.push_back(dht);

        read2bytes(_stream, marker);
    }

    _stream.seekg(-2, std::ios::cur);

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


    this->readSOF0(this->_sof0);
    this->readDHT(this->_dhts);

    this->readSOS(this->_sos);



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







DHT::DHT()
{

}

