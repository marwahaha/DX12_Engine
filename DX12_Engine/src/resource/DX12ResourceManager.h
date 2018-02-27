#pragma once

#include "engine/Defines.h"

#include <vector>
#include <map>

// DX12 resource is a GPU resource as mesh, textures
class DX12Resource;
class DX12Context;
// specific GPU resource
class DX12Mesh;
class DX12Texture;
class DX12Material;

class DX12ResourceManager
{
public:
	// this push a DX12 resource on resource queue to be loaded
	// load mesh through data
	DX12Mesh *			PushMesh(void * i_Data);
	DX12Material *		PushMaterial(void * i_Data);
	DX12Texture *		PushTexture(void * i_Data);

	// load resources from file path
	DX12Material *		PushMaterial(std::string & i_File);
	DX12Texture *		PushTexture(std::string & i_File);


	friend class Engine;
private:
	DX12ResourceManager();
	~DX12ResourceManager();

	// resource management
	void		PushResourceOnGPUWithWait();
	void		PushResourceOnGPU();
	
	struct ResourceData
	{
		bool			IsFile = false;
		void *			Data = nullptr;
		DX12Resource *	Resource = nullptr;
	};

	// upload resource management
	std::vector<ResourceData>		m_ResourceQueue;	// resource to load in queue

	// push command list on GPU
	DX12Context *					m_CopyContext;
	ID3D12CommandQueue *			m_CommandQueue;
};