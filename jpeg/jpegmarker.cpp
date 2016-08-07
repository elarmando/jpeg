#include "jpegmarker.h"

JpegMarker::JpegMarker()
{

}

bool JpegMarker::isAPP(uint2 marker)
{
    return 0xFFE0 <= marker && marker <= 0xFFEF;
}

