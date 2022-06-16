#include "PosOnRoad.h"

PosOnRoad::PosOnRoad(Road* road, float distance)
{
	this->m_road = road;
	CalcInit(distance);
}


float PosOnRoad::GetStart_t() const
{
	return m_t;
}
void PosOnRoad::CalcInit(float distance)
{
	float dist = 0;
	float tmax = m_road->GetSegmentCount();
	vec3 pos = m_road->calcPoint(0);
	for (float i = 0.0f; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= distance)
		{
			this->m_t = i;
			i = tmax + 1;
		}
	}

}
float PosOnRoad::correct(float pred_position_distance, float distance, vec3 pred_position, float in_t)
{
	float tmax = m_road->GetSegmentCount();
	vec3 post = m_road->calcPoint(m_t);
	if (pred_position_distance > distance)
	{
		for (float i = in_t; i > 0; i -= 0.0001)
		{
			post = m_road->calcPoint(i);
			pred_position_distance = space(pred_position, post);
			if (pred_position_distance <= distance)
			{
				in_t = i;
				i = -1;
			}
		}
	}
	else if (pred_position_distance < distance)
	{
		for (float i = in_t; i < tmax; i += 0.0001)
		{
			post = m_road->calcPoint(i);
			pred_position_distance = space(pred_position, post);
			if (pred_position_distance >= distance)
			{
				in_t = i;
				i = tmax + 1;
			}
		}
	}

	return in_t;

}

bool PosOnRoad::isEndRoads()
{
	if (m_t >= m_road->GetSegmentCount() - 0.1 || m_t == 0)
		return true;
	else
		return false;
}

float PosOnRoad::AddOffset(float offset, Math::vec3 pred_position, float distance, float in_t)
{
	float dist = 0;
	float tmax = m_road->GetSegmentCount();
	vec3 pos = m_road->calcPoint(in_t);
	for (float i = in_t; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		
		pos = post;
		if (dist >= offset)
		{
			in_t = i;
			i = tmax + 1;
		}
	}
	float pred_position_distance = space(pred_position, pos);
	if (!approximate(pred_position_distance, 0.05f, distance))
	{
		in_t = correct(pred_position_distance, distance, pred_position, in_t);
	}
	return in_t;
}

bool PosOnRoad::approximate(float value, float inaccuracy, float reference_distance)
{
	bool returned = false;
	if (reference_distance < 0 || (value <= reference_distance + inaccuracy && value >=  reference_distance - inaccuracy))
	{
		returned = true;
	}
		return returned;
}

float PosOnRoad::AddOffset(float offset, float in_t)
{
	float dist = 0;
	float tmax = m_road->GetSegmentCount();
	vec3 pos = m_road->calcPoint(in_t);
	for (float i = in_t; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= offset)
		{
			in_t = i;
			i = tmax + 1;
		}
	}
	return in_t;
}



vec3 PosOnRoad::GetNewPos(float t)
{	
	return m_road->calcPoint(t) + vec3(0,0,1);
}

vec3 PosOnRoad::GetNewDir(float t)
{
	return m_road->calcTangent(t);
}

vec3 PosOnRoad::GetNewUpVec(float t)
{
	return m_road->calcUpVector(t);
}

float PosOnRoad::space(Vec3 point_0, Vec3 point_1)
{
	float new_x = point_0.x - point_1.x;
	float new_y = point_0.y - point_1.y;
	return Math::fsqrt(new_x * new_x + new_y * new_y);
}