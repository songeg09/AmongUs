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

enum class OBJECT_GROUP
{
	MONSTER,
	PLAYABLE,
	BULLET,
	PLAYER_SKILL,
	MONSTER_SKILL,
	END
};