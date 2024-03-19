#pragma once

#include "skills.h"
#include "../entityfactory.h"
#include "../actor.h"
#include <glrayfw/physics/layers.h>

class ShootSkill : public Skill
{
public:
    ShootSkill(
            uint32_t cooldown,
            float bullet_speed,
            float bullet_duration,
            bool player,
            Sprite3D* bulletSprite,
            EntityFactory* ef,
            Actor* shooter)
        : Skill(cooldown),
          m_entityFactory(ef),
          m_shooter(shooter),
          m_player(player),
          m_bulletSprite(bulletSprite),
          m_bulletSpeed(bullet_speed),
          m_bulletDuration(bullet_duration) { }

    void Execute() override
    {
        CollisionLayer cl = (m_player ? CollisionLayer::ALLY_BULLET : CollisionLayer::ENEMY_BULLET);
        uint16_t mask = (m_player ? Physics::ABULLET_MASK : Physics::EBULLET_MASK );
        cml::vector2f shootdir = GetForward( m_shooter );

        int shots = 3;
        int degrees = 30;
        int degsPerShot = degrees / (shots - 1);
        int degsHalf = degrees / 2;

        if (shots > 1)
        {
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                shootdir * m_bulletSpeed, 	// weapon bullet speed
                cl, mask,
                m_bulletSprite,
                m_bulletDuration);			// weapon bullet lifetime
        }

        for (int i = -degsHalf; i <= degsHalf; i += degsPerShot)
        {
            auto rads = i * 0.017453;
            auto rotatedShootDir = Rotate2D(shootdir, rads);
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                rotatedShootDir * m_bulletSpeed, 	// weapon bullet speed
                cl, mask,
                m_bulletSprite,
                m_bulletDuration);			// weapon bullet lifetime
        }

    }

private:
    EntityFactory* m_entityFactory;
    Actor* m_shooter;
    bool m_player;
    int m_ammo = 0;
    float m_bulletSpeed = 0.f;
    float m_bulletDuration = 0.f;
    Sprite3D* m_bulletSprite;
};
