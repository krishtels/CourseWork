#include "drivehorizontalplatform.h"

DriveHorizontalPlatform::DriveHorizontalPlatform():Platform(),
  currentDirection(RIGHT),
  current(0),
  speed(1)
{
  srand(time(NULL));
  minX=-1*rand()%PLATFORM_RANGE;
  maxX=-1*minX;
  connect(this, SIGNAL(leftSign()), this, SLOT(movingLeft()));
  connect(this, SIGNAL(rightSign()), this, SLOT(movingRight()));
  setPlatform();
  setZValue(1.5);
}

DriveHorizontalPlatform::~DriveHorizontalPlatform()
{
}

void DriveHorizontalPlatform::setPlatform()
{
    QPixmap pixmap;
    bool success = pixmap.load(DRIVE_HOR_PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pixmap.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, DRIVE);
}

void DriveHorizontalPlatform::setDirection(horizontalDirection direction)
{
    currentDirection=direction;
}

void DriveHorizontalPlatform::movingLeft()
{
    current-=1;
}

void DriveHorizontalPlatform::movingRight()
{
    current+=1;
}
