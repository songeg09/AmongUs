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

	GHOST_SIGHT_SENSOR,
	GHOST_HEARING_SENSOR,
	GHOST_CHASING_SENSOR,
	GHOST_ATTACK_RANGE,

	OBJECT_INTERACTION_DETECTOR,

	SOUND,
	WALL,
	END
};

enum DIRECTION
{
	START,
	LEFT = START,
	RIGHT,
	UP,
	DOWN,
	END
};