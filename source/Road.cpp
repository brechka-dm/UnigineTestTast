#include "Road.h"

Road::Road(WorldSplineGraphPtr road)
{

	m_road = road;
	road->getSplineSegments(m_road_segment);

	for (SplineSegmentPtr& segment : m_road_segment)
	{
		segment->assignSource(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::FORWARD_X);
		segment->setSegmentMode(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::SEGMENT_STRETCH);
		m_road_Lenght += segment->getLength();
	}
}


int Road::GetSegmentCount()
{
	return this->m_road_segment.size();
}

Vec3 Road::calcPoint(float t)
{
	int segment = t;
	t -= segment;
	return m_road_segment[segment]->calcPoint(t) + m_road->getWorldPosition();
}

Vec3 Road::calcTangent(float t)
{
	int segment = t;
	t -= segment;
	return m_road_segment[segment]->calcTangent((t));
}

Vec3 Road::calcUpVector(float t)
{
	int segment = t;
	t -= segment;
	return m_road_segment[segment]->calcUpVector(t);
}


