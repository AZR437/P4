#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>

class AGameObject
{
	public:
		typedef std::string String;
		AGameObject(String name);
		~AGameObject();
		virtual void initialize() = 0;
		//virtual void processInput(sf::Event event) = 0;
		virtual void update() = 0;
		virtual void draw(GLFWwindow* targetWindow);
		String getName();
		bool getEnabled() const;
		virtual void setEnabled(bool enabled);

		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);
		virtual void setPriority(int priority);

		//virtual sf::FloatRect getLocalBounds();
		//virtual sf::Vector2f getPosition();
		//virtual sf::Vector2f getScale();
		virtual int getPriority();

	protected:
		String name;
		bool enabled = true;

		int priority = 0;
		float posX = 0.0f; float posY = 0.0f;
		float scaleX = 1.0f; float scaleY = 1.0f;
};

