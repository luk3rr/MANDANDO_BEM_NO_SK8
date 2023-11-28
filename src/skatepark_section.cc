/*
 * Filename: skatepark_section.cc
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "skatepark_section.h"
#include <cstdint>
#include <stdexcept>

Section::Section()
{
    this->m_bonus = this->m_traversalTime = 0;
}

Section::Section(int8_t bonus, uint32_t traversalTime)
{
    this->m_bonus                  = bonus;
    this->m_traversalTime          = traversalTime;
    this->m_availableTraversalTime = traversalTime;
}

Section::~Section() { }

void Section::SetBonus(uint16_t bonus)
{
    this->m_bonus = bonus;
}

void Section::SetTraversalTime(uint32_t traversalTime)
{
    this->m_traversalTime = traversalTime;
}

int8_t Section::GetBonus()
{
    return this->m_bonus;
}

uint32_t Section::GetTraversalTime()
{
    return this->m_traversalTime;
}

uint32_t Section::GetAvailableTraversalTime()
{
    return this->m_availableTraversalTime;
}

void Section::UpdateAvailableTraversalTime(uint32_t timeSpent)
{
    if (timeSpent > this->m_availableTraversalTime)
        throw std::out_of_range(
            "Time spent on maneuvers exceeds available traversal time in the section.");

    this->m_availableTraversalTime -= timeSpent;
}
