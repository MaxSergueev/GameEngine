#pragma once
#include <SDL_rect.h>
#include "Vec2.h"

struct Rectangle
{

    Vector2 position;
    Vector2 dimensions;


    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y) };
    }

    static const Rectangle NullRect;

    bool operator!=(const Rectangle& other) const
    {
        return position != other.position || dimensions != other.dimensions;
    }

};

