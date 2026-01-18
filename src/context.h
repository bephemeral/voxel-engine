#pragma once
#include "camera.h"

struct AppContext
{
    Camera *camera;
    bool *paused;
};