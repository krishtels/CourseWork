#include "springboots.h"

SpringBoots::SpringBoots():GameHelper()
{
    setSpringBoots();
}

SpringBoots::~SpringBoots()
{
}

void SpringBoots::setSpringBoots()
{
    QPixmap pixmap;
    bool success = pixmap.load(SPRING_BOOTS_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(SPRING_BOOTS_WIDTH));
    setData(GAMEHELPER_TYPE, SPRING_BOOTS);
}
