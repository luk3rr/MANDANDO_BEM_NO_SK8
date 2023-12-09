/*
 * Filename: skatepark_section.h
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef SKATEPARK_SECTION_H_
#define SKATEPARK_SECTION_H_

#include <cstdint>

/**
 * @brief Class representing a section in a skatepark with bonus and traversal time
 */
class Section
{
    private:
        uint16_t m_bonus;         ///< Bonus associated with the section
        uint32_t m_traversalTime; ///< Traversal time for the section

    public:
        /**
         * @brief Default constructor for the Section class
         */
        Section();

        /**
         * @brief Parameterized constructor for the Section class
         * @param bonus Bonus value for the section
         * @param traversalTime Traversal time for the section in seconds
         */
        Section(int16_t bonus, uint32_t traversalTime);

        /**
         * @brief Destructor for the Section class
         */
        ~Section();

        /**
         * @brief Set the bonus for the section
         * @param bonus Bonus value to be set
         */
        void SetBonus(uint16_t bonus);

        /**
         * @brief Set the traversal time for the section
         * @param traversalTime Traversal time value to be set
         */
        void SetTraversalTime(uint32_t traversalTime);

        /**
         * @brief Get the bonus of the section
         * @return The bonus of the section
         */
        int16_t GetBonus();

        /**
         * @brief Get the traversal time of the section
         * @return The traversal time of the section in seconds
         */
        uint32_t GetTraversalTime();
};

#endif // SKATEPARK_SECTION_H_
