#include "stopplatform.h"

StopPlatform::StopPlatform():Platform()
{
    setPlatform();
}

StopPlatform::~StopPlatform()
{
}

void StopPlatform::setPlatform()
{
    QPixmap pixmap;
    bool success = pixmap.load(STOP_PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pixmap.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, STOPING);
}

