#include "Bogie.h"


#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;



class Cart {
public:
	Cart();
	~Cart();
	void init(NodePtr bogie_Front, NodePtr bogie_BACK, NodePtr Upper,
		Road* road, float speed, int position);
	int Update();
	quat GetCameraDir();
	Vec3 GetCameraPos();
	void SpeedAdd(float speedadding);
	float GetSpeed();
	bool stop();
	
private:
	float speed = 0;
	Bogie bogie_front; 
	Bogie bogie_back;
	Unigine::NodePtr Upper; 
	float space(Vec3 old_point, Vec3 new_point);
	Vec3 centerPoint(Vec3 point1, Vec3 point2);
	float getAngleBetweenBogies(Vec3 front, Vec3 back);
};