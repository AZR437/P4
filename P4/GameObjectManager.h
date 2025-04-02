#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the update function
 */
#include "AGameObject.h"

typedef std::unordered_map<std::string, AGameObject*> HashTable;
typedef std::vector<AGameObject*> List;

class GameObjectManager
{
	public:
		static GameObjectManager* getInstance();
		AGameObject* findObjectByName(AGameObject::String name);
		List getAllObjects();
		int activeObjects();
		void processInput();
		void update();
		void draw();
		void addObject(AGameObject* gameObject);
		void deleteObject(AGameObject* gameObject);
		void deleteObjectByName(AGameObject::String name);
		void sortObjects();

	private:
		GameObjectManager() {};
		GameObjectManager(GameObjectManager const&) {};
		GameObjectManager& operator=(GameObjectManager const&) {};
		static GameObjectManager* sharedInstance;

		HashTable gameObjectMap;
		List gameObjectList;
};

