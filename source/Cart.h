#include "Bogie.h"


#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>
#include <memory>

class Cart {
public:
	Cart(Unigine::NodePtr bogie_Front, Unigine::NodePtr bogie_BACK, Unigine::NodePtr Upper,
		Road* road, float speed, int position);
	int Update();
	int Update(Math::vec3 pos, float distance);
	NodePtr GetNodeForCamera() const;
	void SpeedAdd(float speedadding);
	float GetSpeed() const;
	bool isEndRoads();
	vec3 GetFrontBogie();
	
private:
	float m_speed = 0;
	std::shared_ptr<Bogie> m_bogie_front;
	std::shared_ptr<Bogie> m_bogie_back;
	Unigine::NodePtr m_Upper;
	float space(Vec3 old_point, Vec3 new_point);
	Vec3 centerPoint(Vec3 point1, Vec3 point2);
	float getAngleBetweenBogies(Vec3 front, Vec3 back);
};