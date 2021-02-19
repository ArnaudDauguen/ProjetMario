#pragma once

class IUpdatableObject
{
public:
	virtual void update(int deltaTime) = 0;
	virtual ~IUpdatableObject() = default;
};