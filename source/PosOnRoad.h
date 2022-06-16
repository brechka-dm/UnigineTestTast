#include "Road.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>

#include <vector>

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

class PosOnRoad {
public:
	PosOnRoad(Road* road, float distance);
	vec3 GetNewPos(float t);
	float GetStart_t() const;
	vec3 GetNewDir(float t);
	vec3 GetNewUpVec(float t);
	float AddOffset(float offset, float in_t);
	float AddOffset(float offset, Math::vec3 pred_position, float distance, float in_t);
	float space(Vec3 point_0, Vec3 point_1);
	bool isEndRoads();
private:
	bool approximate(float value, float inaccuracy, float reference_distance);
	void CalcInit(float distance);
	float m_t = 0;
	float correct(float pred_position_distance, float distance, vec3 pred_position, float in_t);
	Road* m_road;
};