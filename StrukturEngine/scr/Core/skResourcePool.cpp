#include "skResourcePool.h"

Struktur::Core::skResourcePool::skResourcePool() : m_images()
{
}

Struktur::Core::skResourcePool::~skResourcePool()
{
}

void Struktur::Core::skResourcePool::CreateTexture(const std::string& path)
{
	entt::hashed_string key = entt::hashed_string{ path.c_str() };
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		m_images[key] = RefCounterGPU<Image, Texture2D>{ 1u, LoadImage(path.c_str()), Texture2D{}, false };
	}
	else
	{
		it->second.count++;
	}
}

bool Struktur::Core::skResourcePool::IsTextureLoadedInGPU(const std::string& path)
{
	return false;
}

void Struktur::Core::skResourcePool::LoadTextureInGPU(const std::string& path)
{
}

Texture2D& Struktur::Core::skResourcePool::RetrieveTexture(const std::string& path)
{
	entt::hashed_string key = entt::hashed_string{ path.c_str() };
	auto it = m_images.find(key);
	if (it == m_images.end())
	{
		assert(true);
		Texture2D empty;
		return empty;
	}
	return it->second.referenceVRAM;
}

void Struktur::Core::skResourcePool::ReleaseTexture(const std::string& path)
{
}
