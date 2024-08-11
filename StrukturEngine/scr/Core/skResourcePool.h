#pragma once
#include <string>
#include <unordered_map>
#include "raylib.h"
#include <entt/entt.hpp>

namespace Struktur
{
	namespace Core
	{
		class skResourcePool
		{
		private:
			template <typename RAM, typename VRAM>
			struct RefGPU {
				RAM referenceRAM;
				VRAM referenceVRAM;
				bool loadedInGPU;
			};
		public:
			skResourcePool();
			~skResourcePool();
		
			//void CreateShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
			//Shader* RetrieveShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
			//void ReleaseShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		
			void CreateTexture(const std::string& path);
			bool IsTextureLoadedInGPU(const std::string& path) const;
			void LoadTextureInGPU(const std::string& path);
			Texture2D RetrieveTexture(const std::string& path) const;
			Image RetrieveImage(const std::string& path) const;
			void UnloadTextureGPU(const std::string& path);
			void ReleaseTexture(const std::string& path);
		
			//void CreateFont(const std::string& path, int size);
			//Font* RetrieveFont(const std::string& path, int size);
			//void ReleaseFont(const std::string& path, int size);
		private:
			std::unordered_map<std::string, RefGPU<Image, Texture2D>> m_images;
		};
	}
}
