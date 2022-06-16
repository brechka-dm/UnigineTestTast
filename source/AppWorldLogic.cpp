/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */



#include "AppWorldLogic.h"

#include <random>


using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

AppWorldLogic::AppWorldLogic()
{
}

AppWorldLogic::~AppWorldLogic()
{
}

int AppWorldLogic::init()
{	
	m_camera_actor = checked_ptr_cast<Player>(World::getNodeByName("main_player"));
	m_CameraPlayer_Train = PlayerDummy::create();
	m_CameraPlayer_Train->setWorldRotation(quat(0,0,0));
	WorldSplineGraphPtr WorldSplineGraphPlayer = WorldSplineGraph::create();
	WorldSplineGraphPtr WorldSplineGraphNPC = WorldSplineGraph::create();
	
	WorldSplineGraphPlayer->load("1.spl");
	WorldSplineGraphNPC->load("1.spl");
	WorldSplineGraphNPC->setWorldPosition(vec3(25.53255, 0, 0));
	m_roads.push_back(Road(WorldSplineGraphPlayer));
	m_roads.push_back(Road(WorldSplineGraphNPC));


	random_device rd;   
	mt19937 gen(rd());  
	uniform_int_distribution<> dist(0, 1);

	vector<int> carts_types_NPC;
	vector<int> carts_types_Player;
	for (int i = 0; i < 3; i++)
	{
		carts_types_NPC.push_back(dist(gen));
	}
	for (int i = 0; i < 3; i++)
	{
		carts_types_Player.push_back(dist(gen));
	}

	m_TrainPlayer = make_unique<Train> (Train(&m_roads[0], 5, carts_types_Player));
	m_TrainNPC = make_unique<Train> (Train(&m_roads[1], 5, carts_types_NPC));
	m_TrainPlayer->GetNodeForCamera()->addChild(m_CameraPlayer_Train);
	m_CameraPlayer_Train->setPosition(Vec3(0, 0, 3));
	m_CameraPlayer_Train->rotate(90, 180, 0);
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{

	m_TrainPlayer->Update();
	m_TrainNPC->Update();
	
	

	if (Input::isKeyPressed(Input::KEY_R))
	{
		quat rot = m_CameraPlayer_Train->getWorldRotation();
		m_CameraPlayer_Train->rotate(0, 180, 0);
	}
	if (Input::isKeyPressed(Input::KEY_UP))
	{
		m_TrainPlayer->SpeedAdd(0.0005);
	}
	if (Input::isKeyPressed(Input::KEY_DOWN))
	{
		m_TrainPlayer->SpeedAdd(-0.0005);


	}

	if (Input::isKeyPressed(Input::KEY_F2))
	{
		Game::setPlayer(m_CameraPlayer_Train);
	}

	if (Input::isKeyPressed(Input::KEY_F3))
	{
		Game::setPlayer(m_camera_actor);
	}
	
	return 1;
}
int AppWorldLogic::postUpdate()
{
	// The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	UNIGINE_UNUSED(stream);
	return 1;
}
