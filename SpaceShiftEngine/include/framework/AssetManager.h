#pragma once
#include <SFML/Graphics.hpp>


#include "framework/Core.h"

namespace ss
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		shared < sf::Font> LoadFont(const std::string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const std::string& directory);
	protected:
		AssetManager();
	private:
		template<typename T>
		shared<T> LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& conteiner);

		static unique<AssetManager> assetManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
		std::string mRootDirectory;

		template<typename T>
		void CleanUniqueRef(Dictionary<std::string, shared<T>>& conteiner);
	};

	template<typename T>
	inline shared<T> AssetManager::LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& conteiner)
	{
		auto found = conteiner.find(path);
		if(found != conteiner.end())
		{
			return found->second;
		}

		shared<T> newAsset{new T};
		if(newAsset->loadFromFile(mRootDirectory + path))
		{
			conteiner.insert({ path, newAsset });
			return newAsset;
		}

		return shared<T> {nullptr};
	}

	template<typename T>
	inline void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& conteiner)
	{
		for (auto iter = conteiner.begin(); iter != conteiner.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning: %s", iter->first.c_str());
				iter = conteiner.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

}