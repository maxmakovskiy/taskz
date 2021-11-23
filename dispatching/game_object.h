#pragma once

#include "geo2d.h"

class Unit;
class Building;
class Tower;
class Fence;

struct GameObject 
{
  virtual ~GameObject() = default;

  virtual bool Collide(const GameObject& that) const = 0;
  virtual bool CollideWith(const Unit& that) const = 0;
  virtual bool CollideWith(const Building& that) const = 0;
  virtual bool CollideWith(const Tower& that) const = 0;
  virtual bool CollideWith(const Fence& that) const = 0;
};

bool Collide(const GameObject& first, const GameObject& second);

// Curiously recurring template pattern
template <typename T>
struct Collider : GameObject 
{
    bool Collide(const GameObject& that) const final
    {
        return that.CollideWith(static_cast<const T&>(*this));
    }
};

class Unit final : public Collider<Unit>
{
public:
    explicit Unit(geo2d::Point position);
    geo2d::Point GetPosition() const;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

private:
    geo2d::Point p;
};

class Building final : public Collider<Building> 
{
public:
    explicit Building(geo2d::Rectangle geometry);
    geo2d::Rectangle GetPosition() const;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

private:
    geo2d::Rectangle rect;
};

class Tower final : public Collider<Tower>
{
public:
    explicit Tower(geo2d::Circle geometry);
    geo2d::Circle GetPosition() const;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

private:
    geo2d::Circle circle;
};

class Fence final : public Collider<Fence>
{
public:
    explicit Fence(geo2d::Segment geometry);
    geo2d::Segment GetPosition() const;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

private:
    geo2d::Segment segment;
};

