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
#include <cmath>
#include <cstdint>
#include <limits>

constexpr uint16_t MAX_TRICKS   = 1e1;
constexpr uint16_t MAX_SECTIONS = 1e2;

constexpr int64_t NEGATIVE_INFINITY = std::numeric_limits<int64_t>::min();
const uint16_t    COMBINATIONS      = std::pow(2, MAX_TRICKS);

constexpr uint16_t BIT_MASK_ONE = 0x0001; // 0000000000000001

constexpr bool DEBUG = false;

/**
 * @brief Class representing a Skate Park with tricks, sections, and a memoization table
 * for optimization
 */
class SkatePark
{
    private:
        Vector<Trick>   m_tricks;   ///< Vector of tricks in the skate park
        Vector<Section> m_sections; ///< Vector of sections in the skate park

        // Memoization tables for dynamic programming optimization
        Vector<Vector<int64_t>> m_score; ///< Given that we performed trick i, what
                                         ///< score does trick j have
        Vector<Vector<int64_t>>
            m_mostRadicalTrick; ///< Memoization table used in the search for the set of
                                ///< tricks in each section that will yield the most
                                ///< points

        Vector<Vector<uint16_t>>
            m_trickPermutations; ///< The set of trick i contains which tricks

        Vector<int64_t>
            m_trickDurations; ///< Stores the total duration of the set of tricks i

        // Set of tricks performed in each section
        Vector<uint16_t> m_tricksPerSections;

        /**
         * @brief Given that we performed the trick set 'previousTrick' in the previous
         *section, how many points can we achieve by performing the 'currentTrick' set?
         * @param currentTrick Trick set we intend to perform now
         * @param previousTrick Trick set we performed in the previous section
         *
         * NOTE: In case of repetition of tricks performed in the previous section,
         *       the score in the current section will be halved
         **/
        void StoreScore(uint16_t currentTrick, uint16_t previousTrick);

        /**
         * @brief Applies dynamic programming to find the highest score
         *        we can achieve in the skate park
         * @param section Section considered in the current calculation
         * @param trickSet Trick set we intend to perform in this section
         * @return Maximum possible score in the current section
         **/
        int64_t FindMostRadicalTrick(uint16_t section, uint16_t trickSet);

        /**
         * @brief Generates and stores the permutation of tricks
         **/
        void GenerateTrickPermutations();

        /**
         * @brief Given the trick set, stores the time required to perform it
         * @param trickSet Trick set for which the duration will be calculated
         **/
        void StoreTrickDuration(uint16_t trickSet);

        /**
         * @brief Given the section and the trick set, determines if this trick set
         *        can be performed within the maximum travel time of the section
         * @param section Section considered in the calculation
         * @param trickSet Trick set considered in the calculation
         **/
        bool IsTimeWithinSectionLimit(uint16_t section, uint16_t trickSet);

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

        /**
         * @brief Employs dynamic programming to find the most badass trick that can be
         *        performed on this skate park.
         * @return The score of the most badass trick.
         **/
        int64_t FindMostFuckingRadicalTrick();

        /**
         * @brief Prints the set of tricks that were performed in each section.
         **/
        void ShowTricksList();

        /**
         * @brief Prints the matrices on the screen for debugging purposes.
         **/
        void DumpMatrices();
};

#endif // SKATEPARK_H_
