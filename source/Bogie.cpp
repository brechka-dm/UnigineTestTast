#include "Bogie.h"

Bogie::Bogie()
{}
void Bogie::init(NodePtr bogie, Road* road, float nulldistance)
{

	this->road.init(road, nulldistance);
	this->bogieNode = bogie;
	vec3 pos = this->road.GetNewPos();
	vec3 dir = this->road.GetNewDir();
	vec3 up = this->road.GetNewUpVec();
	this->bogieNode->setWorldPosition(pos);
	this->bogieNode->setWorldDirection(dir, up);
	bogieNode->rotate(-90, 0, 0);

}

bool Bogie::stop()
{
	return road.stop();
}
void Bogie::DistanceAdd(float frameSpeed)
{
	
	this->road.AddOffset(frameSpeed);
	vec3 pos = road.GetNewPos();
	vec3 dir = road.GetNewDir();
	vec3 up = road.GetNewUpVec();
	
	this->bogieNode->setWorldPosition(pos);
	this->bogieNode->setWorldDirection(dir, up);
	bogieNode->rotate(-90, 0, 0);
}
vec3 Bogie::GetPosition()
{
	return this->bogieNode->getWorldPosition();
}