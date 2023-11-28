/*
 * Filename: skatepark.cc
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "skatepark.h"
#include "skatepark_section.h"
#include "trick.h"
#include "vector.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

SkatePark::SkatePark()
{
    // Allocate memory for the cache and initialize all cells as infinity
    this->m_cache.Resize(MAX_TRICKS + 1, Vector<int64_t>(MAX_SECTIONS + 1));

    for (std::size_t i = 0; i < this->m_cache.GetMaxSize(); i++)
    {
        for (std::size_t j = 0; j < this->m_cache[i].GetMaxSize(); j++)
        {
            this->m_cache[i][j] = NEGATIVE_INFINITY;
        }
    }

    // Initilize vector of vectors
    this->m_tricksInSections.Resize(MAX_SECTIONS, Vector<bool>(MAX_TRICKS));

    for (std::size_t i = 0; i < this->m_tricksInSections.GetMaxSize(); i++)
    {
        for (std::size_t j = 0; j < this->m_tricksInSections[i].GetMaxSize(); j++)
        {
            this->m_tricksInSections[i][j] = false;
        }
    }
}

SkatePark::~SkatePark() { }

void SkatePark::AddTrick(int32_t trickScore, uint32_t trickExecTime)
{
    this->m_tricks.PushBack(Trick(trickScore, trickExecTime));
}

void SkatePark::AddSection(uint16_t sectionBonus, uint32_t sectionTraversalTime)
{
    this->m_sections.PushBack(Section(sectionBonus, sectionTraversalTime));
}

// Função para calcular o resultado máximo usando programação dinâmica e memoização
int64_t SkatePark::CalculateMaxScore(uint16_t trickID, uint16_t sectionID)
{

    // Verifique se o resultado já foi calculado
    // Se todas as tricks tiverem o tempo de execução > do que o tempo de travesia
    // de uma seção, isso vai da problema, pois o valor será == 0.
    if (this->m_cache[trickID][sectionID] != NEGATIVE_INFINITY)
    {
        return this->m_cache[trickID][sectionID];
    }

    // Caso base: se não há mais manobras ou seções
    if (trickID == this->m_tricks.Size() or sectionID == this->m_sections.Size())
    {
        return 0;
    }

    // Verifique se a manobra atual pode ser realizada na seção atual
    if (this->m_tricks[trickID].GetExecutionTime() <=
            this->m_sections[sectionID].GetAvailableTraversalTime() and
        not this->m_tricksInSections[sectionID][trickID])
    {
        // resultado máximo entre escolher ou não escolher a manobra atual
        int64_t chooseTrick = this->m_tricks[trickID].GetScore() *
                                  this->m_sections[sectionID].GetBonus() +
                              CalculateMaxScore(trickID, sectionID + 1);

        int64_t skipTrick = CalculateMaxScore(trickID, sectionID + 1);

        // Se a trick foi realizada na seção anterior
        if (sectionID > 0 and this->m_tricksInSections[sectionID - 1][trickID])
        {
            chooseTrick /= 2;
        }

        // Se a trick foi realizada na seção anterior
        if (sectionID > 0 and this->m_tricksInSections[sectionID - 1][trickID])
        {
            skipTrick /= 2;
        }

        if (chooseTrick == skipTrick)
        {
            std::cout << "WARNING: Tricks with the same score" << std::endl;
        }

        if (skipTrick > chooseTrick)
        {
            // Atualize a tabela de memoização
            this->m_cache[trickID][sectionID] = skipTrick;
        }
        else
        {
            // Atualize a tabela de memoização
            this->m_cache[trickID][sectionID] = chooseTrick;
        }
    }
    else
    {
        // Se a manobra não pode ser realizada na seção atual, pule para a próxima
        // manobra
        int64_t skipTrick = CalculateMaxScore(trickID + 1, sectionID);

        this->m_cache[trickID][sectionID] = skipTrick;
    }

    // Atualizar tempo disponível nessa seção
    this->m_sections[sectionID].UpdateAvailableTraversalTime(
        this->m_tricks[trickID].GetExecutionTime());

    // Define que a manobra foi feita nessa seção
    this->m_tricksInSections[sectionID][trickID] = true;
    return this->m_cache[trickID][sectionID];
}

int64_t SkatePark::GetMaxScore()
{
    if (this->m_sections.IsEmpty() or this->m_tricks.IsEmpty())
    {
        return 0;
    }

    int64_t max = 0;

    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        max += CalculateMaxScore(0, i);
    }

    return max;
}

void SkatePark::ShowTricksList()
{
    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        // show section id
        std::cout << i + 1 << " ";
        for (std::size_t j = 0; j < this->m_tricks.Size(); j++)
        {
            // Show trick if it has performed in this section
            if (this->m_tricksInSections[i][j])
            {
                std::cout << j + 1 << " ";
            }
        }
        std::cout << std::endl;
    }
}
