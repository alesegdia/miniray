#pragma once

#include <cstdint>
#include <vector>
#include <memory>

class Skill
{
public:
    typedef std::shared_ptr<Skill> SharedPtr;

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
        uint32_t rate = 1;
        uint32_t last_shot = 0;
        Skill::SharedPtr skill;
        bool pressed = false;
    };

    SkillSet(int num_skills)
        : m_slots(num_skills)
    {
        m_slots.shrink_to_fit();
    }

    void update(uint32_t delta)
    {
        for( auto slot : m_slots )
        {
            if( updateSlot(slot, delta) )
            {
                slot.skill->execute();
            }
        }
    }

    SlotConfig& slot(int slot_id)
    {
        return m_slots[slot_id];
    }

    bool updateSlot(SlotConfig& slot, uint32_t delta)
    {
        slot.last_shot += delta;
        if( slot.pressed && slot.last_shot >= slot.rate )
        {
            slot.last_shot = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    void setSlotConfig(int slot_id, SlotConfig slot_config)
    {
        m_slots[slot_id] = slot_config;
    }

private:
    std::vector<SlotConfig> m_slots;

};
