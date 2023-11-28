/*
 * Filename: trick.cc
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "trick.h"
#include <cstdint>

Trick::Trick()
{
    this->m_score = this->m_executionTime = 0;
}

Trick::Trick(int32_t score, uint32_t execTime)
{
    this->m_score         = score;
    this->m_executionTime = execTime;
}

Trick::~Trick() { }

void Trick::SetScore(int32_t score)
{
    this->m_score = score;
}

void Trick::SetExecutionTime(uint32_t execTime)
{
    this->m_executionTime = execTime;
}

int32_t Trick::GetScore()
{
    return this->m_score;
}

uint32_t Trick::GetExecutionTime()
{
    return this->m_executionTime;
}
