#ifndef JPEGMARKER_H
#define JPEGMARKER_H

#include <stdint.h>

typedef  uint16_t uint2;


class JpegMarker
{
public:
    JpegMarker();

    const static uint2 SOI = 0xFFD8;//start of image
    const static uint2 EOI = 0xFFD9;//END OF IMAGE
    const static uint2 APP0 = 0xFFE0;//Application marker
    const static uint2 DHT = 0xFFC4;//define huffman table
    const static uint2 DQT = 0xFFDB; //define quantization table
    const static uint2 SOF0 = 0xFFC0; //start of frame, baseline

    static bool isAPP(uint2 marker);

};

#endif // JPEGMARKER_H
