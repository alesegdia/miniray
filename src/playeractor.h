
class Inventory;

class PlayerActor : public Actor
{

private:

	Inventory* inventory;

public:

	PlayerActor()
	{
		type = Entity::Type::PLAYER;
		controller = new PlayerController();
	}

	void Step( uint32_t delta )
	{
		// cosas del player
	}

};
