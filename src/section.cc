/*
 * Filename: skatepark_section.cc
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "section.h"

Section::Section()
{
    this->m_bonus = this->m_traversalTime = 0;
}

Section::Section(int16_t bonus, uint32_t traversalTime)
{
    this->m_bonus         = bonus;
    this->m_traversalTime = traversalTime;
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

int16_t Section::GetBonus()
{
    return this->m_bonus;
}

uint32_t Section::GetTraversalTime()
{
    return this->m_traversalTime;
}
