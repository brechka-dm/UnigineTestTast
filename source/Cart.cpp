#include "Cart.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Cart::Cart(NodePtr bogie_Front, NodePtr bogie_BACK, NodePtr Upper,
	Road* road, float speed, int position)
{
	//make_unique<Train> (Train(&roads[0], 5, carts_types_Player));
	this->m_Upper = Upper;
	this->m_speed = speed;
	this->m_bogie_back = make_unique<Bogie>(bogie_BACK, road, 7 * position);
	this->m_bogie_front = make_unique<Bogie>(bogie_Front, road, 7 * position + 4);

	Upper->setPosition(centerPoint(m_bogie_back->GetPosition(),
		m_bogie_front->GetPosition()));

	Upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(m_bogie_front->GetPosition(), m_bogie_back->GetPosition())));
}


float Cart::space(Vec3 point_0, Vec3 point_1)
{
	float new_x = point_0.x - point_1.x;
	float new_y = point_0.y - point_1.y;
	return Math::fsqrt(new_x * new_x + new_y * new_y);
}


float Cart::getAngleBetweenBogies(Vec3 front, Vec3 back)
{

	vec2 temp = vec2(front.x - back.x, front.y - back.y);

	float test = atan2(temp.y, temp.x) * 57.29578f;

	return test;
}

Vec3 Cart::centerPoint(Vec3 point1, Vec3 point2)
{
	return Vec3((point1.x + point2.x) / 2, (point1.y + point2.y) / 2, 0);
}

NodePtr Cart::GetNodeForCamera() const
{
	return m_Upper;
}


bool Cart::isEndRoads()
{
	if (m_bogie_front->isEndRoads() && m_bogie_back->isEndRoads())
		return true;
	else
		return false;
}

int Cart::Update(Math::vec3 pos, float distance)
{
	float speed = this->m_speed * Game::getIFps();

	this->m_bogie_back->DistanceAdd(speed, pos, distance);
	pos = m_bogie_back->GetPosition();
	this->m_bogie_front->DistanceAdd(speed, pos, 4);

	m_Upper->setPosition(centerPoint(m_bogie_back->GetPosition(), m_bogie_front->GetPosition()));
	m_Upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(m_bogie_front->GetPosition(), m_bogie_back->GetPosition())));

	return 0;
}

vec3 Cart::GetFrontBogie()
{
	return m_bogie_front->GetPosition();
}

int Cart::Update()
{
	float speed = this->m_speed * Game::getIFps();

	this->m_bogie_back->DistanceAdd(speed);
	this->m_bogie_front->DistanceAdd(speed);

	m_Upper->setPosition(centerPoint(m_bogie_back->GetPosition(), m_bogie_front->GetPosition()));

	m_Upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(m_bogie_front->GetPosition(), m_bogie_back->GetPosition())));
	
	return 1;
}

void Cart::SpeedAdd(float speedadding)
{
	m_speed += speedadding;
}
float Cart::GetSpeed() const
{
	return m_speed;
}
