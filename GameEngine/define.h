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
	WALL_DETECTOR,
	
	INTERACTION_CREW,
	INTERACTION_IMPOSTER,

	PLAYER_HURTBOX,
	PLAYER_INTERACTION,

	MONSTER_PLAYER_DETECTOR,
	MONSTER_ATTACK_RANGE,

	OBJECT_INTERACTION_DETECTOR,

	WALL,
	END
};