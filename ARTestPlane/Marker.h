/**
 * Marker.h
 * Created By: Michael Feist
 */

#pragma once
class Marker
{
private:
	int id;
	float pos[3];

public:
	Marker(void) {}
	Marker(int id) { this->id = id; }
	Marker(int id, float x, float y, float z) 
	{ 
		this->id = id;
		this->pos[0] = x;
		this->pos[1] = y;
		this->pos[2] = z;
	}

	~Marker(void) {}

	void setId(int id)
	{
		this->id = id;
	}

	int getId()
	{
		return this->id;
	}

	void setPos(float x, float y, float z)
	{
		this->pos[0] = x;
		this->pos[1] = y;
		this->pos[2] = z;
	}

	float* getPos()
	{
		return this->pos;
	}

	void setX(float x)
	{
		this->pos[0] = x;
	}

	float getX()
	{
		return this->pos[0];
	}

	void setY(float y)
	{
		this->pos[1] = y;
	}

	float getY()
	{
		return this->pos[1];
	}

	void setZ(float z)
	{
		this->pos[2] = z;
	}

	float getZ()
	{
		return this->pos[2];
	}
};

