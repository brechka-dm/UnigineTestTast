#include "Train.h"





Train::Train()
{ }
void Train::init(Road* road, float speed, vector<int> Cart_types)
{
	this->speed = speed;
	this->road = road;
	
	for(int i = 0; i < Cart_types.size();i++)
	{
		Cart vag;
		if(Cart_types[i] == 0)
			vag.init(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_box.node"), road, speed, i);
		else
			vag.init(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_cylingr.node"), road, speed, i);
		Carts.push_back(vag);
	}
}

void Train::SpeedAdd(float speedadding)
{
	if (!((speed >= 0.5 && speedadding > 0) || (speed < 0.0005 && speedadding<0)))
	{
		speed += speedadding;
		for (int i = 0; i < Carts.size(); i++)
		{
			Carts[i].SpeedAdd(speedadding);
		}
	}
}
float Train::GetSpeed()
{
	return speed;
}


quat Train::GetCamera()
{
	int size = Carts.size() - 1;
	return Carts[size].GetCameraDir();
}

Vec3 Train::GetCameraPos()
{
	int size = Carts.size() - 1;
	return Carts[size].GetCameraPos() + vec3(0,0,3);
}

void Train::Update()
{
	int lastCart = Carts.size() - 1;
	if (!Carts[lastCart].stop())
	{
		for (int i = 0; i < Carts.size(); i++)
		{
			Carts[i].Update();
		}
	}
}