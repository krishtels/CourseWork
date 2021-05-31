#include "movingplatform.h"

MovingPlatform::MovingPlatform():Platform()
{
    setPlatform();
}

MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::setPlatform()
{
    QPixmap pixmap;
    bool success = pixmap.load(MOVING_PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pixmap.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, MOVING);
}
