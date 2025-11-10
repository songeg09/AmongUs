#include "pch.h"
#include "Object.h"
#include "Wall.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::Init(Vector2 _vec2Position)
{
	SetPosition(_vec2Position);
}

void Wall::Update()
{

}

void Wall::Render(HDC _memDC)
{
	Object::Render(_memDC);
}

