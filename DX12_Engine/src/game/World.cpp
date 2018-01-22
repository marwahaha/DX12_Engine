#include "World.h"

#include "Actor.h"

#include "dx12/DX12Utils.h"

World::World()
{
}

World::~World()
{
}

float World::GetFrameTime() const
{
	return m_FrameTime;
}

Actor * World::SpawnActor(Actor * i_Parent)
{
	Actor * newActor = new Actor(this);
	m_Actors.push_back(newActor);

	// add actor to the parent if needed
	if (i_Parent = nullptr)
	{
		newActor->m_Parent = i_Parent;
		i_Parent->m_Children.push_back(newActor);
	}

	// push actor on roots actors if needed
	if (newActor->IsRoot())
	{
		m_RootActors.push_back(newActor);
	}

	return newActor;
}

bool World::DeleteActor(Actor * i_ActorToRemove, bool i_RemoveChildren)
{
	auto itr = std::find(m_Actors.begin(), m_Actors.end(), i_ActorToRemove);

	// the actor is not in the list
	if (itr == m_Actors.end())
	{
		return false;
	}

	// erase the actor from the actors list
	m_Actors.erase(itr);

	// remove the actor from the root
	if (i_ActorToRemove->IsRoot())
	{
		auto itr = std::find(m_RootActors.begin(), m_RootActors.end(), i_ActorToRemove);

		// the actor is supposed to be in the root actors
		if (itr == m_RootActors.end())
		{
			DEBUG_BREAK;
			return false;
		}

		m_RootActors.erase(itr);

	}

	// To do : call to a Destroy event on Actor
	// remove the actor from the memory
	delete i_ActorToRemove;

	return true;
}

bool World::AttachActor(Actor * i_Parent, Actor * i_Child)
{
	if (i_Parent == nullptr || i_Child == nullptr)
		return false;

	// we need to remove the actor from the childs
	if (i_Child->IsRoot())
	{
		auto itr = std::find(m_RootActors.begin(), m_RootActors.end(), i_Child);

		// the actor is supposed to be in the root actors
		if (itr == m_RootActors.end())
		{
			DEBUG_BREAK;
			return false;
		}

		m_RootActors.erase(itr);
	}
	else
	{
		Actor * parent = i_Child->m_Parent;

		// remove the child from the current parent children
		auto itr = std::find(parent->m_Children.begin(), parent->m_Children.end(), i_Child);

		if (itr == parent->m_Children.end())
		{
			DEBUG_BREAK;
			return false;
		}

		parent->m_Children.erase(itr);
	}

	// update parent/childrens
	i_Parent->m_Children.push_back(i_Child);
	i_Child->m_Parent = i_Parent;

	return true;
}

bool World::DetachActor(Actor * i_ActorToDetach)
{
	// if the actor is attached to something
	if (!i_ActorToDetach->IsRoot())
	{
		Actor * parent = i_ActorToDetach->m_Parent;

		// remove the child from the current parent children
		auto itr = std::find(parent->m_Children.begin(), parent->m_Children.end(), i_ActorToDetach);

		if (itr == parent->m_Children.end())
		{
			DEBUG_BREAK;
			return false;
		}

		parent->m_Children.erase(itr);
	}

	// push the actor to the root actors
	m_RootActors.push_back(i_ActorToDetach);

	return true;
}

void World::TickWorld(float i_Elapsed)
{
	// save elapsed time
	m_FrameTime = i_Elapsed;

	// update components
	for (size_t i = 0; i < m_Actors.size(); ++i)
	{
		Actor * actor = m_Actors[i];

		if (actor->IsEnabled())
		{
			// first we need to update the actor
			if (actor->NeedTick())
			{
				actor->Tick(m_FrameTime);
			}

			// then we need maybe to render the actor,
			// this mean we push the render component to the render list
			// To do : push the render component to the specific list
			if (actor->NeedRendering())
			{

			}
		}
	}
}
