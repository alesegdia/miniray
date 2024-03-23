#pragma once

#include "skills.h"
#include "../entityfactory.h"
#include "../actor.h"
#include <glrayfw/physics/layers.h>

struct ShootConfig
{
    uint32_t cooldown = 0;
    float bullet_speed = 100;
    float bullet_duration = 10;
    int extraShots = 0;
    int extraShotsSpreadDegs = 0;
    int pushback = 10;
    int damage = 1;
    float shake = 0.0f;
};

class ShootSkill : public Skill
{
public:
    ShootSkill(
            ShootConfig shootConfig,
            bool player,
            Sprite3D* bulletSprite,
            EntityFactory* ef,
            Actor* shooter)
        : Skill(shootConfig.cooldown),
          m_shootConfig(shootConfig),
          m_entityFactory(ef),
          m_shooter(shooter),
          m_player(player),
          m_bulletSprite(bulletSprite)
    {
        
    }

    void Execute() override
    {

        m_shooter->skillSet.ConsumeAmmo();
        if (m_shooter->skillSet.GetAmmo() == 0)
        {
            return;
        }

        CollisionLayer cl = (m_player ? CollisionLayer::ALLY_BULLET : CollisionLayer::ENEMY_BULLET);
        uint16_t mask = (m_player ? Physics::ABULLET_MASK : Physics::EBULLET_MASK );
        cml::vector2f shootdir = m_shooter->GetForward();

        m_shooter->PushBack(m_shootConfig.pushback);

        // main shot
        m_entityFactory->SpawnBullet(
            GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
            shootdir * m_shootConfig.bullet_speed, 	// weapon bullet speed
            cl, mask,
            m_bulletSprite,
            m_shootConfig.bullet_duration,			// weapon bullet lifetime
            m_shootConfig.damage);

        for (int i = 0; i < m_shootConfig.extraShots; i ++)
        {
            int degsPerShot = m_shootConfig.extraShotsSpreadDegs / (m_shootConfig.extraShots);
            auto rads = (i+1) * degsPerShot * 0.017453;
            auto rotatedShootDirLeft = Rotate2D(shootdir, -rads);
            auto rotatedShootDirRight = Rotate2D(shootdir, rads);
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                rotatedShootDirLeft * m_shootConfig.bullet_speed, 	// weapon bullet speed
                cl, mask,
                m_bulletSprite,
                m_shootConfig.bullet_duration, m_shootConfig.damage);			// weapon bullet lifetime
            m_entityFactory->SpawnBullet(
                GetWorld2DPos(m_shooter->transform.position) + shootdir, 	// shoot point
                rotatedShootDirRight * m_shootConfig.bullet_speed, 	// weapon bullet speed
                cl, mask,
                m_bulletSprite,
                m_shootConfig.bullet_duration, m_shootConfig.damage);			// weapon bullet lifetime
        }

        AddShake(m_shootConfig.shake);

    }

private:
    EntityFactory* m_entityFactory;
    Actor* m_shooter;
    bool m_player;
    Sprite3D* m_bulletSprite;
    ShootConfig m_shootConfig;

};
