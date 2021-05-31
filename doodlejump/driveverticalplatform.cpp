#include "driveverticalplatform.h"

DriveVerticalPlatform::DriveVerticalPlatform():Platform(),
  currentDirection(UP),
  current(0),
  speed(1)
{
  srand(time(NULL));
  minY=-1*rand()%PLATFORM_RANGE;
  maxY=-1*minY;
  connect(this, SIGNAL(upSignal()), this, SLOT(up()));
  connect(this, SIGNAL(downSignal()), this, SLOT(down()));
  setPlatform();
}

DriveVerticalPlatform::~DriveVerticalPlatform()
{
}

void DriveVerticalPlatform::setPlatform()
{
    QPixmap pixmap;
    bool success = pixmap.load(DRIVE_HOR_PLATFORM_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pixmap.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, VERTICAL);
}

void DriveVerticalPlatform::setDirection(verticalDirection direction)
{
    currentDirection=direction;
}

void DriveVerticalPlatform::up()
{
    current-=1;
}

void DriveVerticalPlatform::down()
{
    current+=1;
}

