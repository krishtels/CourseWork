#include "simpleplatform.h"

SimplePlatform::SimplePlatform():Platform()
{
    setPlatform();
}

SimplePlatform::~SimplePlatform()
{
}

void SimplePlatform::setPlatform()
{
    QPixmap pixmap;
    bool success = pixmap.load(PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pixmap.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, SIMPLE);
}

