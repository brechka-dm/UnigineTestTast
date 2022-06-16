#include "Train.h"


using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Train::Train(Road* road, float speed, vector<int> Cart_types)
{
	m_speed = speed;
	m_road = road;

	for (int i = 0; i < Cart_types.size(); i++)
	{
		if (Cart_types[i] == 0)
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_box.node"), road, speed, i);
			m_Carts.emplace_back(vag);
		}
		else
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_cylingr.node"), road, speed, i);
			m_Carts.emplace_back(vag);
		}
	}
}

void Train::SpeedAdd(float value_for_the_sum_to_the_speed)
{
	if (!((m_speed >= 0.5 && value_for_the_sum_to_the_speed > 0) || (m_speed < 0.0005 && value_for_the_sum_to_the_speed <0)))
	{
		m_speed += value_for_the_sum_to_the_speed;
		for (int i = 0; i < m_Carts.size(); i++)
		{
			m_Carts[i].SpeedAdd(value_for_the_sum_to_the_speed);
		}
	}
}

float Train::GetSpeed() const
{
	return m_speed;
}


NodePtr Train::GetNodeForCamera()
{
	int size = m_Carts.size() - 1;
	return m_Carts[size].GetNodeForCamera();
}

void Train::Update()
{
	int lastCart = m_Carts.size() - 1;
	if (!m_Carts[lastCart].isEndRoads())
	{
		m_Carts[0].Update();
		vec3 reference = m_Carts[0].GetFrontBogie();
		for (int i = 1; i < m_Carts.size(); i++)
		{
			m_Carts[i].Update(reference, 3);
			reference = m_Carts[i].GetFrontBogie();
		}
	}
}