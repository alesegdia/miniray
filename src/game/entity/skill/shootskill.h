#pragma once

#include "skills.h"
#include "../entityfactory.h"
#include "../actor.h"
#include <glrayfw/physics/layers.h>

class ShootSkill : public Skill
{
public:
    ShootSkill(
            float bullet_speed,
            float bullet_duration,
            bool player,
            Sprite3D* bulletSprite,
            EntityFactory* ef,
            Actor* shooter)
        : m_entityFactory(ef),
          m_shooter(shooter),
          m_bulletSprite(bulletSprite),
          m_bulletSpeed(bullet_speed),
          m_bulletDuration(bullet_duration) { }

    void execute() override
    {
        CollisionLayer cl = (player ? CollisionLayer::ALLY_BULLET : CollisionLayer::ENEMY_BULLET);
        uint16_t mask = (player ? Physics::ABULLET_MASK : Physics::EBULLET_MASK );
        cml::vector2f shootdir = GetForward( m_shooter );
        m_entityFactory->SpawnBullet(
                    GetWorld2DPos( actor->transform.position ) + shootdir, 	// shoot point
                    shootdir * m_bulletSpeed, 	// weapon bullet speed
                    cl, mask,
                    m_bulletSprite,
                    m_bulletDuration );			// weapon bullet lifetime
    }

private:
    EntityFactory* m_entityFactory;
    Actor* m_shooter;
    int m_ammo = 0;
    float m_bulletSpeed = 0.f;
    float m_bulletDuration = 0.f;
    Sprite3D* m_bulletSprite;
};
