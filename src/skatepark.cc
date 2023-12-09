/*
 * Filename: skatepark.cc
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "skatepark.h"

SkatePark::SkatePark()
{
    // Initialize vectors and matrices
    this->m_score.Resize(COMBINATIONS,
                         Vector<int64_t>(COMBINATIONS, NEGATIVE_INFINITY));

    this->m_mostRadicalTrick.Resize(MAX_SECTIONS,
                                    Vector<int64_t>(COMBINATIONS, NEGATIVE_INFINITY));

    this->m_tricksPerSections.Resize(MAX_SECTIONS, Vector<uint16_t>(COMBINATIONS, 0));
    this->m_trickPermutations.Resize(COMBINATIONS, Vector<uint16_t>());
    this->m_trickDurations.Resize(COMBINATIONS, NEGATIVE_INFINITY);
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

void SkatePark::StoreScore(uint16_t currentTrick, uint16_t previousTrick)
{
    uint16_t repeated = currentTrick & previousTrick;
    int64_t  points   = 0;

    for (uint16_t i = 0; i < MAX_TRICKS; i++)
    {
        if (repeated >> i & BIT_MASK_ONE)
        {
            points += this->m_tricks[i].GetScore() / 2;
        }
        else if (currentTrick >> i & BIT_MASK_ONE)
        {
            points += this->m_tricks[i].GetScore();
        }
    }

    this->m_score[currentTrick][previousTrick] = points;
}

bool SkatePark::IsTimeWithinSectionLimit(uint16_t section, uint16_t trickSet)
{
    uint32_t sectionTime = this->m_sections[section].GetTraversalTime();

    if (this->m_trickDurations[trickSet] != NEGATIVE_INFINITY)
    {
        return this->m_trickDurations[trickSet] <= sectionTime;
    }

    int64_t trickSetTime = 0;

    for (uint16_t i = 0; i < MAX_TRICKS; i++)
    {
        if (trickSet >> i & BIT_MASK_ONE)
        {
            trickSetTime += this->m_tricks[i].GetExecutionTime();
        }
    }

    this->m_trickDurations[trickSet] = trickSetTime;

    return trickSetTime <= sectionTime;
}

void SkatePark::GenerateTrickPermutations()
{
    for (uint16_t i = 0; i < std::pow(2, this->m_tricks.Size()); i++)
    {
        for (uint16_t j = 0; j < MAX_TRICKS; j++)
        {
            if (i >> j & BIT_MASK_ONE)
            {
                this->m_trickPermutations[i].PushBack(j);
            }
        }
    }
}

int64_t SkatePark::FindMostRadicalTrick(uint16_t section, uint16_t trickSet)
{
    // Base case: No more sections
    if (section > this->m_sections.Size() - 1)
    {
        return 0;
    }

    // If the value has already been calculated, use the one stored in the table instead
    if (this->m_mostRadicalTrick[section][trickSet] != NEGATIVE_INFINITY)
    {
        return this->m_mostRadicalTrick[section][trickSet];
    }

    int64_t max              = NEGATIVE_INFINITY;
    int16_t mostRadicalTrick = 0;

    int64_t  aux;
    uint16_t numTricksInThisSection;

    for (uint16_t i = 0; i < COMBINATIONS; i++)
    {
        // Check if the trick set 'i' can be performed in section 'section'
        if (not IsTimeWithinSectionLimit(section, i))
            continue;

        // Check if the score for the trick set 'i' given that we performed the trick
        // 'trickSet' in the previous section has already been calculated
        if (this->m_score[i][trickSet] == NEGATIVE_INFINITY)
        {
            StoreScore(i, trickSet);
        }

        numTricksInThisSection = this->m_trickPermutations[i].Size();

        aux = FindMostRadicalTrick(section + 1, i) +
              this->m_score[i][trickSet] * this->m_sections[section].GetBonus() *
                  numTricksInThisSection;

        if (aux > max)
        {
            max              = aux;
            mostRadicalTrick = i;
        }
    }

    // Store the most radical trick set for this section
    this->m_tricksPerSections[section][trickSet] = mostRadicalTrick;
    this->m_mostRadicalTrick[section][trickSet]  = max;

    return this->m_mostRadicalTrick[section][trickSet];
}

int64_t SkatePark::FindMostFuckingRadicalTrick()
{
    GenerateTrickPermutations();

    FindMostRadicalTrick(0, 0);

    return this->m_mostRadicalTrick[0][0];
}

void SkatePark::ShowTricksList()
{
    uint16_t    spell = 0;
    uint16_t    aux;
    std::string set;

    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        spell = this->m_tricksPerSections[i][spell];

        aux = 0;
        set.clear();

        for (uint16_t j = 0; j < MAX_TRICKS; j++)
        {
            if (spell >> j & BIT_MASK_ONE)
            {
                aux++;
                set += std::to_string(j + 1) + " ";
            }
        }
        std::cout << aux << " " << set.substr(0, set.size() - 1) << std::endl;
    }
}

void SkatePark::DumpMatrices()
{

    std::cout << "\n## Points Matrix (m x m') ##" << std::endl;

    for (std::size_t i = 0; i < COMBINATIONS; i++)
    {
        if (this->m_score[i][0] == NEGATIVE_INFINITY)
            break;
        std::cout << i << " | ";
        for (std::size_t j = 0; j < COMBINATIONS; j++)
        {
            if (this->m_score[i][j] == NEGATIVE_INFINITY)
                break;

            std::cout << this->m_score[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "## Score (sections x m')" << std::endl;
    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        if (this->m_mostRadicalTrick[i][0] == NEGATIVE_INFINITY)
            break;

        std::cout << i << " | ";
        for (std::size_t j = 0; j < COMBINATIONS; j++)
        {
            if (this->m_mostRadicalTrick[i][j] == NEGATIVE_INFINITY)
                break;

            std::cout << this->m_mostRadicalTrick[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
