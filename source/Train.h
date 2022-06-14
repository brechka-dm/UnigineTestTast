#include "Cart.h"
#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>

#include <vector>

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

class Train {

public:
	Train();
	void init(Road* road, float speed, vector<int> Cart_types);
	void Update();
	quat GetCamera();
	Vec3 GetCameraPos();
	void SpeedAdd(float speedadding);
	float GetSpeed();
	~Train() {}

private:
	float speed = 0; 
	Vector<Cart> Carts;
	Road* road;
};