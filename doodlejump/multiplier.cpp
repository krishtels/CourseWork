#include "multiplier.h"

Multiplier::Multiplier():GameHelper()
{
    setMultiplier();
    setZValue(1.7);
}

Multiplier::~Multiplier()
{
}

void Multiplier::setMultiplier()
{
    QPixmap pixmap;
    bool success = pixmap.load(MULTIPLIER_PATH_1);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(GHOST_WIDTH));
    setData(GAMEHELPER_TYPE, MULTIPLIER);
}

void Multiplier::incrementCount()
{
    count++;
    changePix();
}

void Multiplier::changePix()
{
    QPixmap pixmap;
    bool success = true;
    switch (count) {
        case 0:
            success = pixmap.load(MULTIPLIER_PATH_1);
            break;
        case 1:
            success = pixmap.load(MULTIPLIER_PATH_3);
            break;
        case 2:
            success = pixmap.load(MULTIPLIER_PATH_5);
            break;
        case 3:
            success = pixmap.load(MULTIPLIER_PATH_10);
            break;
        case 4:
            success = pixmap.load(MULTIPLIER_PATH_200);
            break;
        default:
            break;
    }
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(GHOST_WIDTH));
}
