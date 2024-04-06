
#include "mobaicontroller.h"

RNG MobAIController::rng;
std::shared_ptr<EntityFactory> MobAIController::entityfactory = nullptr;
Player* MobAIController::player = nullptr;

