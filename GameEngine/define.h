#pragma once

#define SINGLETON(Type) public:		\
	static Type* GetInstance()		\
	{								\
		static Type instance;		\
		return &instance;			\
	}								\
									\
	private:						\
		Type();						\
		~Type();

enum class COLLISION_TAG
{
	CHARACTER,
	INTERACT,
	WALL,
	END
};