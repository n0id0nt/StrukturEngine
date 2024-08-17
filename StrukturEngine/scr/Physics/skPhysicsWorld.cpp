#include "skPhysicsWorld.h"

Struktur::Physics::skPhysicsWorld::skPhysicsWorld(Vector2 gravity, float timeStep, int velocityIterations, int positionIterations, float pixelsPerMeter)
	: m_world({ gravity.x, gravity.y }), m_timeStep(timeStep), m_velocityIteration(velocityIterations), m_positionIterations(positionIterations), m_pixelsPerMeter(pixelsPerMeter), m_contactListener()
{
	m_world.SetContactListener(&m_contactListener);
}

void Struktur::Physics::skPhysicsWorld::Step()
{
	m_world.Step(m_timeStep, m_velocityIteration, m_positionIterations);
}

void Struktur::Physics::skPhysicsWorld::ClearForces()
{
	m_world.ClearForces();
}

b2Body* Struktur::Physics::skPhysicsWorld::CreateBody(const b2BodyDef* bodyDef)
{
	return m_world.CreateBody(bodyDef);
}

void Struktur::Physics::skPhysicsWorld::DestroyBody(b2Body* body)
{
	m_world.DestroyBody(body);
}

float Struktur::Physics::skPhysicsWorld::GetPixelsPerMeter() const
{
	return m_pixelsPerMeter;
}

void Struktur::Physics::skPhysicsWorld::SetPixelsPerMeter(float pixelsPerMeter)
{
	m_pixelsPerMeter = pixelsPerMeter;
	// TODO resize everything in the scene to match the new pixel size, or just assert to ensure the scene is empty before resizeing
}
