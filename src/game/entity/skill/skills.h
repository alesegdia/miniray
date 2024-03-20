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
        m_lastShot = cooldown;
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
        if (m_pressed)
        {
            m_lastShot += delta;
            if (m_lastShot >= m_cooldown)
            {
                m_lastShot -= m_cooldown;
                Execute();
            }
        }
        else
        {
            m_lastShot = m_cooldown;
        }
    }

    virtual void Execute() = 0 ;

private:
    uint32_t m_lastShot = 0;
    bool m_pressed = false;
    uint32_t m_cooldown;

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

private:
    std::vector<std::shared_ptr<Skill>> m_skills;
    int m_currentSkillIndex = 0;

};
