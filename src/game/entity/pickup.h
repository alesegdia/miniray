
#pragma once

class Pickup : public Entity {
public:
	enum Type {
		AMMO, HEALTH, ITEM
	};

	Type type;
	int quantity=20;
};

