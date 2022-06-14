#include "Road.h"

Road::Road(WorldSplineGraphPtr road)
{

	this->road = road;
	road->getSplineSegments(road_segment);

	for (SplineSegmentPtr& segment : road_segment)
	{
		segment->assignSource(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::FORWARD_X);
		segment->setSegmentMode(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::SEGMENT_STRETCH);
		road_Lenght += segment->getLength();
	}
}
Vec3 Road::calcPoint(float t)
{
	int segment = t;
	t -= segment;
	t= road_segment[segment]->linearToParametric(t);
	return road_segment[segment]->calcPoint(t) + road->getWorldPosition();
}

int Road::GetSegmentCount()
{
	return this->road_segment.size();
}

Vec3 Road::calcTangent(float t)
{
	int segment = t;
	t -= segment;
	t = road_segment[segment]->linearToParametric(t);
	return road_segment[segment]->calcTangent((t));
}

Vec3 Road::calcUpVector(float t)
{
	
	int segment = t;
	t -= segment;
	t = road_segment[segment]->linearToParametric(t);
	return road_segment[segment]->calcUpVector(t);
}

float Road::GetLenght()
{
	return this->road_Lenght;
}

int Road::GetSegment(float distance)
{
	float max_distance = 0;
	int returned = 0;
	for (int i = 0; i < road_segment.size(); i++)
	{
		max_distance += road_segment[i]->getLength();
		if (distance <= max_distance) {
			returned = i;
			i = road_segment.size();
		}
	}
	return returned;
}

float Road::GetSegmentLenght(int segment)
{
	return road_segment[segment]->getLength();
}
