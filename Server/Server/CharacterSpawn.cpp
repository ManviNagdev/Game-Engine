#include "CharacterSpawn.h"
GameObject CharacterSpawn::character_spawn_event(GameObject a, GameObject b) {
	a.pos = b.pos;
	return a;
}