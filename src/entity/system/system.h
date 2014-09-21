
#pragma once

class EntityFactory;
class Entity;

class System {

protected:

	static EntityFactory* entityfactory;


public:

	static Entity* player;
	static void SetEntityFactory( EntityFactory* efact );
	static void SetPlayerEntity( Entity* player );

};

