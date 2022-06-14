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
	PosOnRoad();
	void init(Road* road, float distance);
	vec3 GetNewPos();
	vec3 GetNewDir();
	vec3 GetNewUpVec();
	void AddOffset(float offset);
	float space(Vec3 point_0, Vec3 point_1);
	bool stop();
private:

	void CalcInit(float distance);
	float distance = 0;
	float t = 0;
	void correct(float offset);
	Vec3 pos;
	Road* road;
};