#include "game_object.h"

Unit::Unit(geo2d::Point position)
    : p(position)
{
}

geo2d::Point Unit::GetPosition() const
{
    return p;
}

bool Unit::Collide(const GameObject& that) const
{
    return that.CollideWith(*this);  
}

bool Unit::CollideWith(const Unit& that) const
{
    return geo2d::Collide(p, that.GetPosition());
}

bool Unit::CollideWith(const Building& that) const
{
    return geo2d::Collide(p, that.GetPosition());
}

bool Unit::CollideWith(const Tower& that) const
{
    return geo2d::Collide(p, that.GetPosition());
}

bool Unit::CollideWith(const Fence& that) const
{
    return geo2d::Collide(p, that.GetPosition());
}


Building::Building(geo2d::Rectangle geometry)
    : rect(geometry)
{
}

geo2d::Rectangle Building::GetPosition() const
{
    return rect;
}

bool Building::Collide(const GameObject& that) const
{
    return that.CollideWith(*this);  
}

bool Building::CollideWith(const Unit& that) const
{
    return geo2d::Collide(rect, that.GetPosition());
}

bool Building::CollideWith(const Building& that) const
{
    return geo2d::Collide(rect, that.GetPosition());
}

bool Building::CollideWith(const Tower& that) const
{
    return geo2d::Collide(rect, that.GetPosition());
}

bool Building::CollideWith(const Fence& that) const
{
    return geo2d::Collide(rect, that.GetPosition());
}

Tower::Tower(geo2d::Circle geometry)
    : circle(geometry)
{
}

geo2d::Circle Tower::GetPosition() const
{
    return circle;
}

bool Tower::Collide(const GameObject& that) const
{
    return that.CollideWith(*this);  
}

bool Tower::CollideWith(const Unit& that) const
{
    return geo2d::Collide(circle, that.GetPosition());
}

bool Tower::CollideWith(const Building& that) const
{
    return geo2d::Collide(circle, that.GetPosition());
}

bool Tower::CollideWith(const Tower& that) const
{
    return geo2d::Collide(circle, that.GetPosition());
}

bool Tower::CollideWith(const Fence& that) const
{
    return geo2d::Collide(circle, that.GetPosition());
}

Fence::Fence(geo2d::Segment geometry)
    : segment(geometry)
{
}

geo2d::Segment Fence::GetPosition() const
{
    return segment;
}

bool Fence::Collide(const GameObject& that) const
{
    return that.CollideWith(*this);  
}

bool Fence::CollideWith(const Unit& that) const
{
    return geo2d::Collide(segment, that.GetPosition());
}

bool Fence::CollideWith(const Building& that) const
{
    return geo2d::Collide(segment, that.GetPosition());
}

bool Fence::CollideWith(const Tower& that) const
{
    return geo2d::Collide(segment, that.GetPosition());
}

bool Fence::CollideWith(const Fence& that) const
{
    return geo2d::Collide(segment, that.GetPosition());
}

bool
Collide
(const GameObject& first, const GameObject& second)
{
    return first.Collide(second);
}


