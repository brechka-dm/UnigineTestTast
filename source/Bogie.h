#include "PosOnRoad.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>
#include <memory>





class Bogie {
public:
	Bogie(Unigine::NodePtr bogie, Road* road, float nulldistance);
	void DistanceAdd(float frameSpeed);
	void DistanceAdd(float frameSpeed, Math::vec3 pos, float distance);
	vec3 GetPosition();
	bool isEndRoads();
private:
	const float m_pi = 3.1415926f;
	const float m_R = 1.5f / 2;
	float m_t = 0;
	float m_distance = 0;
	void wheel_rotation(float offset);
	NodePtr m_bogieNode;
	shared_ptr<PosOnRoad> m_road;
};