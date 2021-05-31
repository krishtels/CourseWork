#include "fallingplatform.h"

FallingPlatform::FallingPlatform():Threat()
{
    srand(time(NULL));
    setThreat();
}

FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::setThreat()
{
    QPixmap pixmap;
    bool success = pixmap.load(FALLING_PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    setData(THREAT_TYPE, FALLING_PLATFORM);
}
