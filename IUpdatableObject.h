#pragma once

class IUpdatableObject
{
public:
	virtual void update(int deltaTime) = 0;
	virtual bool mustDie() = 0;
	virtual ~IUpdatableObject() = default;
};