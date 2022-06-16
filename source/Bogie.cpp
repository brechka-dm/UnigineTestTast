#include "Bogie.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Bogie::Bogie(NodePtr bogie, Road* road, float nulldistance)
{
	m_distance = nulldistance;
	this->m_road = make_unique<PosOnRoad>(road, nulldistance);
	this->m_bogieNode = bogie;
	m_t = m_road->GetStart_t();
	vec3 pos = this->m_road->GetNewPos(m_t);
	vec3 dir = this->m_road->GetNewDir(m_t);
	vec3 up = this->m_road->GetNewUpVec(m_t);
	this->m_bogieNode->setWorldPosition(pos);
	this->m_bogieNode->setWorldDirection(dir, up);
	m_bogieNode->rotate(-90, 0, 0);
	
	
}

void Bogie::wheel_rotation(float offset)
{
	float angle = (180 * offset) / (m_pi * m_R);
	m_bogieNode->findNode("front_axle")->rotate(-angle, 0, 0);
	m_bogieNode->findNode("back_axle")->rotate(-angle, 0, 0);
}

bool Bogie::isEndRoads() 
{
	return m_road->isEndRoads(m_t);
}
void Bogie::DistanceAdd(float frameSpeed)
{
	m_distance += frameSpeed;
	m_t = this->m_road->AddOffset(frameSpeed, m_t);
	vec3 pos = m_road->GetNewPos(m_t);
	vec3 dir = m_road->GetNewDir(m_t);
	vec3 up = m_road->GetNewUpVec(m_t);
	
	this->m_bogieNode->setWorldPosition(pos);
	this->m_bogieNode->setWorldDirection(dir, up);
	m_bogieNode->rotate(-90, 0, 0);

	wheel_rotation(frameSpeed);
}

void Bogie::DistanceAdd(float frameSpeed, Math::vec3 previous, float distance)
{
	m_distance += frameSpeed;
	m_t = this->m_road->AddOffset(frameSpeed, previous, distance, m_t);
	vec3 pos = m_road->GetNewPos(m_t);
	vec3 dir = m_road->GetNewDir(m_t);
	vec3 up = m_road->GetNewUpVec(m_t);

	this->m_bogieNode->setWorldPosition(pos);
	this->m_bogieNode->setWorldDirection(dir, up);
	m_bogieNode->rotate(-90, 0, 0);

	wheel_rotation(frameSpeed);
}
vec3 Bogie::GetPosition() 
{
	return this->m_bogieNode->getWorldPosition();
}