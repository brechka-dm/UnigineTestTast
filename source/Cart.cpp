#include "Cart.h"

Cart::Cart()
{

}

Cart::~Cart()
{

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
void Cart::init(NodePtr bogie_Front, NodePtr bogie_BACK, NodePtr Upper, 
	Road* road, float speed, int position)
{
	this->Upper = Upper;
	this->speed = speed;
	this->bogie_back.init(bogie_BACK, road, 7 * position);
	this->bogie_front.init(bogie_Front, road, 7 * position + 4);
	
	Upper->setPosition(centerPoint(bogie_back.GetPosition(), bogie_front.GetPosition()));

	Upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(bogie_front.GetPosition(), bogie_back.GetPosition())));
	
}





quat Cart::GetCameraDir()
{
	return Upper->getWorldRotation();
}
Vec3 Cart::GetCameraPos()
{
	return Upper->getWorldPosition();
}



bool Cart::stop()
{
	
	if (bogie_front.stop() && bogie_back.stop())
		return true;
	else
		return false;
}

int Cart::Update()
{
	
	float speed = this->speed * Game::getIFps();
	

	Upper->setPosition(centerPoint(bogie_back.GetPosition(), bogie_front.GetPosition()));

	Upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(bogie_front.GetPosition(), bogie_back.GetPosition())));

	this->bogie_back.DistanceAdd(speed);
	this->bogie_front.DistanceAdd(speed);
	
	
	return 1;
}

void Cart::SpeedAdd(float speedadding)
{
	speed += speedadding;
}
float Cart::GetSpeed()
{
	return speed;
}
