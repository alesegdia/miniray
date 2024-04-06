#pragma once

#include <cstdint>
#include <vector>
#include <memory>

class Skill
{
public:
    typedef std::shared_ptr<Skill> SharedPtr;

    Skill(uint32_t cooldown)
    {
        m_cooldown = cooldown;
        m_nextShot = cooldown;
    }

    ~Skill()
    {

    }

    void SetPressed(bool pressed)
    {
        m_pressed = pressed;
    }

    void Update(uint32_t delta)
    {
        m_nextShot -= delta;
        if (m_pressed && m_nextShot <= 0)
        {
            Execute();
            m_nextShot = m_cooldown;
        }
    }

    virtual void Execute() = 0 ;

    float ConsumeShakeLastFrame()
    {
        auto f = m_shakeLastFrame;
        m_shakeLastFrame = 0;
        return f;
    }

    void Upgrade()
    {
        m_level++;
        OnWeaponUpgraded(m_level);
    }

protected:
    void AddShake(float f)
    {
        m_shakeLastFrame += f;
    }

    int GetLevel()
    {
        return m_level;
    }

    virtual void OnWeaponUpgraded(int level) = 0;

private:

    int m_nextShot = 0;
    bool m_pressed = false;
    uint32_t m_cooldown;
    float m_shakeLastFrame = 0.0f;
    int m_level = 0;

};


/** EXAMPLE OF USE
 * class FireballSkill
 * {
 * public:
 *      FireballSkill(Stats& stats);
 *      void execute()
 *      {
 *          // create fireball bullet with damage
 *          // depending on stats passed at ctor
 *      }
 */

class SkillSet
{
public:

    SkillSet(int num_skills)
        : m_skills(num_skills)
    {
        m_skills.shrink_to_fit();
    }

    void update(uint32_t delta)
    {
        m_skills[m_currentSkillIndex]->Update(delta);
    }

    void SetSlotSkill(int skillIndex, std::shared_ptr<Skill> skill)
    {
        m_skills[skillIndex] = skill;
    }

    void SetPressed(bool pressed)
    {
        m_skills[m_currentSkillIndex]->SetPressed(pressed);
    }

    int UpgradeSkill(int weaponIndex)
    {
        if (weaponIndex >= 0 && weaponIndex < m_skills.size())
        {
            m_skills[weaponIndex]->Upgrade();
        }
        else
        {
            return -1;
        }
    }

    void SetCurrentSlot(int slot)
    {
        m_currentSkillIndex = slot;
    }

    std::shared_ptr<Skill> GetCurrentSkill()
    {
        return m_skills[m_currentSkillIndex];
    }

    int GetCurrentSlot()
    {
        return m_currentSkillIndex;
    }

    void AddAmmo(int ammo)
    {
        m_ammo += ammo;
    }

    void ConsumeAmmo()
    {
        if (m_ammo > 0)
        {
            m_ammo--;
        }
    }

    int GetAmmo()
    {
        return m_ammo;
    }

private:
    std::vector<std::shared_ptr<Skill>> m_skills;
    int m_currentSkillIndex = 0;
    int m_ammo = -1;

};
