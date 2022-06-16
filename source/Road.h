#ifndef __Road_HEADER__
#define __Road_HEADER__

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>

#include <vector>

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

class Road {
public:
	Road(WorldSplineGraphPtr road);
	Vec3 calcPoint(float t);
	Vec3 calcTangent(float t);
	Vec3 calcUpVector(float t);
	int GetSegmentCount();
private:
	WorldSplineGraphPtr m_road;
	Vector<SplineSegmentPtr> m_road_segment;
	float m_road_Lenght = 0;
};
#endif