#pragma once

#include <cstdint>
#include <vector>

class Skill
{
public:
    ~Skill()
    {

    }

    virtual void execute() = 0 ;
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

    class SlotConfig
    {
    public:
        uint32_t cooldown;
        Skill* skill;
    };

    SkillSet(int num_skills)
        : m_slots(num_skills)
    {
        m_slots.shrink_to_fit();
    }

    bool tryFireSkill(int slot_id)
    {
        return m_slots[slot_id].cooldown < 0;
    }

    void update(uint32_t delta)
    {
        for( auto slot : m_slots )
        {
            slot.cooldown = std::max(uint32_t(0), slot.cooldown - delta);
        }
    }

    void setSlotConfig(int slot_id, SlotConfig slot_config)
    {
        m_slots[slot_id] = slot_config;
    }

private:
    std::vector<SlotConfig> m_slots;

};
