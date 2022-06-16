#include "Cart.h"
#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>

#include <vector>


class Train {

public:
	Train(Road* road, float speed, vector<int> Cart_types);
	void Update();
	NodePtr GetNodeForCamera() ;
	void SpeedAdd(float value_for_the_sum_to_the_speed);
	float GetSpeed() const;

private:
	float m_speed = 0; 
	Vector<Cart> m_Carts;
	Road* m_road;
};