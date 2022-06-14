#include "PosOnRoad.h"

PosOnRoad::PosOnRoad()
{

}

void PosOnRoad::init(Road* road, float distance)
{
	
	this->road = road;
	CalcInit(distance);
}


void PosOnRoad::CalcInit(float distance)
{
	/*
	float dist = distance;

	int segment = road->GetSegment(dist);

	float lenghtseg = road->GetSegmentLenght(segment);

	for (int i = 0; i < segment; i++)
	{
		dist -= road->GetSegmentLenght(i);
	}

	t = (dist / lenghtseg) + segment;

	this->t = t;

	this->pos = road->calcPoint(t);
	this->distance += dist;
	*/



	float dist = 0;
	float tmax = road->GetSegmentCount();
	vec3 pos = road->calcPoint(0);
	for (float i = 0.0f; i < tmax; i += 0.0001)
	{
		vec3 post = road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= distance)
		{
			this->t = i;
			i = tmax + 1;
		}
	}
	this->distance = dist;
	this->pos = pos;

}
void PosOnRoad::correct(float offset)
{
	float dist = 0;
	float tmax = road->GetSegmentCount();
	vec3 pos = road->calcPoint(t);
	for (float i = this->t; i < tmax; i += 0.0001)
	{
		vec3 post = road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= offset)
		{
			this->t = i;
			i = tmax + 1;
		}
	}
	this->distance += offset;
	this->pos = pos;
}

bool PosOnRoad::stop()
{
	if (t >= road->GetSegmentCount() - 0.1 || t == 0)
		return true;
	else
		return false;
}
void PosOnRoad::AddOffset(float offset)
{
	correct(offset);
}



vec3 PosOnRoad::GetNewPos()
{	
	return road->calcPoint(t) + vec3(0,0,1);
}

vec3 PosOnRoad::GetNewDir()
{
	return road->calcTangent(t);
}

vec3 PosOnRoad::GetNewUpVec()
{
	return road->calcUpVector(t);
}

float PosOnRoad::space(Vec3 point_0, Vec3 point_1)
{
	float new_x = point_0.x - point_1.x;
	float new_y = point_0.y - point_1.y;
	return Math::fsqrt(new_x * new_x + new_y * new_y);
}