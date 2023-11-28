/*
 * Filename: skatepark.h
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef SKATEPARK_H_
#define SKATEPARK_H_

#include "skatepark_section.h"
#include "trick.h"
#include "vector.h"
#include <cstdint>
#include <limits>

constexpr uint16_t MAX_TRICKS        = 1e1;
constexpr uint16_t MAX_SECTIONS      = 1e2;
constexpr int64_t  NEGATIVE_INFINITY = std::numeric_limits<int64_t>::min();

/**
 * @brief Class representing a Skate Park with tricks, sections, and a memoization table
 * for optimization
 */
class SkatePark
{
    private:
        Vector<Trick>           m_tricks;   ///< Vector of tricks in the skate park
        Vector<Section>         m_sections; ///< Vector of sections in the skate park
        Vector<Vector<int64_t>> m_cache;    ///< Memoization table for dynamic
                                            ///< programming optimization

        Vector<Vector<bool>>
            m_tricksInSections; ///< vector of vectors indicating whether trick
                                ///< j was performed in section i

        int64_t CalculateMaxScore(uint16_t trickID, uint16_t sectionID);

    public:
        /**
         * @brief Default constructor for the SkatePark class
         */
        SkatePark();

        /**
         * @brief Destructor for the SkatePark class
         */
        ~SkatePark();

        /**
         * @brief Adds a new trick to the skate park
         * @param trickScore The score of the trick to be added
         * @param trickExecTime The execution time of the trick to be added
         */
        void AddTrick(int32_t trickScore, uint32_t trickExecTime);

        /**
         * @brief Adds a new section to the skate park
         * @param sectionBonus The bonus of the section to be added
         * @param sectionTraversalTime The traversal time of the section to be added
         */
        void AddSection(uint16_t sectionBonus, uint32_t sectionTraversalTime);

        int64_t GetMaxScore();

        void ShowTricksList();
};

#endif // SKATEPARK_H_
