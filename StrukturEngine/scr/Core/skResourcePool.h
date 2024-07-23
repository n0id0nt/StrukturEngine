#pragma once
#include <string>
struct Font;
struct Image;

namespace Struktur
{
	namespace Core
	{
		//class skResourcePool
		//{
		//private:
		//	template <typename T>
		//	struct RefCounter {
		//		unsigned int count;
		//		std::unique_ptr<T> reference;
		//	};
		//public:
		//	skResourcePool();
		//	~skResourcePool();
		//
		//	//void CreateShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		//	//Shader* RetrieveShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		//	//void ReleaseShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		//
		//	void CreateTexture(const std::string& path);
		//	Texture* RetrieveTexture(const std::string& path);
		//	void ReleaseTexture(const std::string& path);
		//
		//	void CreateFont(const std::string& path, int size);
		//	Font* RetrieveFont(const std::string& path, int size);
		//	void ReleaseFont(const std::string& path, int size);
		//};
	}
}
