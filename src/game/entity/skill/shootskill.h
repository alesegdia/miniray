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
            int extraShots,
            int extraShotsSpreadDegs,
            bool player,
            Sprite3D* bulletSprite,
            EntityFactory* ef,
            Actor* shooter)
        : Skill(cooldown),
          m_entityFactory(ef),
          m_shooter(shooter),
          m_extraShots(extraShots),
          m_extraShotsSpreadDegs(extraShotsSpreadDegs),
          m_player(player),
          m_bulletSprite(bulletSprite),
          m_bulletSpeed(bullet_speed),
          m_bulletDuration(bullet_duration) { }

    void Execute() override
    {
        CollisionLayer cl = (m_player ? CollisionLayer::ALLY_BULLET : CollisionLayer::ENEMY_BULLET);
        uint16_t mask = (m_player ? Physics::ABULLET_MASK : Physics::EBULLET_MASK );
        cml::vector2f shootdir = GetForward( m_shooter );

        int degsPerShot = m_extraShotsSpreadDegs / (m_extraShots);

        // main shot
        m_entityFactory->SpawnBullet(
            GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
            shootdir * m_bulletSpeed, 	// weapon bullet speed
            cl, mask,
            m_bulletSprite,
            m_bulletDuration);			// weapon bullet lifetime

        for (int i = 0; i < m_extraShots; i ++)
        {
            auto rads = (i+1) * degsPerShot * 0.017453;
            auto rotatedShootDirLeft = Rotate2D(shootdir, -rads);
            auto rotatedShootDirRight = Rotate2D(shootdir, rads);
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                rotatedShootDirLeft * m_bulletSpeed, 	// weapon bullet speed
                cl, mask,
                m_bulletSprite,
                m_bulletDuration);			// weapon bullet lifetime
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                rotatedShootDirRight * m_bulletSpeed, 	// weapon bullet speed
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
    int m_extraShotsSpreadDegs = 0;
    int m_extraShots = 0;
};
