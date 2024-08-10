#include "skResourcePool.h"

Struktur::Core::skResourcePool::skResourcePool() : m_images()
{
}

Struktur::Core::skResourcePool::~skResourcePool()
{
}

void Struktur::Core::skResourcePool::CreateTexture(const std::string& path)
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		m_images[key] = RefGPU<Image, Texture2D>{ 1u, LoadImage(path.c_str()), Texture2D{}, false };
	}
	else
	{
		it->second.count++;
	}
}

bool Struktur::Core::skResourcePool::IsTextureLoadedInGPU(const std::string& path) const
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true); // texture does not exist
		return false;
	}
	return it->second.loadedInGPU;
}

void Struktur::Core::skResourcePool::LoadTextureInGPU(const std::string& path)
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true); // texture does not exist
		return;
	}
	if (it->second.loadedInGPU)
	{
		assert(true); // texture is already loaded
		return;
	}
	Image& image = it->second.referenceRAM;
	Texture2D texture = LoadTextureFromImage(image);
	//TODO get the success of the load somehow, and assert when unsuccessful
	it->second.referenceVRAM = texture;
	it->second.loadedInGPU = true;
}

Texture2D Struktur::Core::skResourcePool::RetrieveTexture(const std::string& path) const
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true); // texture does not exist
		Texture2D empty{};
		return empty;
	}
	if (!it->second.loadedInGPU)
	{
		assert(true); // texture is not loaded
	}
	return it->second.referenceVRAM;
}

void Struktur::Core::skResourcePool::UnloadTextureGPU(const std::string& path)
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true); // texture does not exist
		return;
	}
	if (!it->second.loadedInGPU)
	{
		assert(true); // texture is not loaded
		return;
	}
	Texture2D& texture = it->second.referenceVRAM;

	UnloadTexture(texture);
	//TODO get the success of the unload somehow, and assert when unsuccessful
	it->second.referenceVRAM = Texture2D{};
	it->second.loadedInGPU = false;
}

void Struktur::Core::skResourcePool::ReleaseTexture(const std::string& path)
{
	std::string key = path;
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true); // texture does not exist
		return;
	}
	it->second.count--;
	if (it->second.count <= 0)
	{
		if (IsTextureLoadedInGPU(path))
		{
			UnloadTextureGPU(path);
		}
		Image& image = it->second.referenceRAM;
		UnloadImage(image);
		m_images.erase(it);
	}
}
