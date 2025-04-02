#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class AGameObject
{
public:
	typedef std::string String;
	AGameObject(String name);
	~AGameObject();
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	String getName();
	bool getEnabled() const;
	virtual void setEnabled(bool enabled);
	virtual void setPriority(int priority);

public:
	void translate(glm::vec3 translation);
	void translate(float x, float y, float z);
	void scale(glm::vec3 escalation);
	void scale(float x, float y, float z);
	void scale(float scalar);
	void rotate(float theta, glm::vec3 axis);
	void rotate(float theta, float x, float y, float z);

public:
	void setPosition(glm::vec3 position);
	glm::mat4 getTransformation();
	glm::vec3 getPosition();
	virtual int getPriority();

protected:
	String name;
	bool enabled = true;
	glm::mat4 transformation;
	int priority = 0;
};

