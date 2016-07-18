#ifndef JPEGMARKER_H
#define JPEGMARKER_H

typedef  unsigned short uint2;

class JpegMarker
{
public:
    JpegMarker();

    static uint2 SOI = 0xFFD8;//start of image
    static uint2 EOI = 0xFFD9;//END OF IMAGE
    static uint2 APP0 = 0xFFE0;//Application marker

};

#endif // JPEGMARKER_H
