#include "PosOnRoad.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>


using namespace Unigine;
using namespace std;
using namespace Unigine::Math;


class Bogie {
public:
	Bogie();
	void init(NodePtr bogie, Road* road, float nulldistance);
	void DistanceAdd(float frameSpeed);
	vec3 GetPosition();
	bool stop();
private:
	NodePtr bogieNode;
	PosOnRoad road;
};