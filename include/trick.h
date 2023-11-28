/*
 * Filename: trick.h
 * Created on: November 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef TRICK_H_
#define TRICK_H_

#include <cstdint>

/**
 * @brief Class representing a skateboarding trick with associated score and execution
 * time
 */
class Trick
{
    private:
        int32_t  m_score;         ///< Trick's score
        uint32_t m_executionTime; ///< Trick's execution time

    public:
        /**
         * @brief Default constructor for the Trick class
         */
        Trick();

        /**
         * @brief Constructor for the Trick class
         * @param score The score of this trick
         * @param execTime The execution time of this trick
         */
        Trick(int32_t score, uint32_t execTime);

        /**
         * @brief Destructor for the Trick class
         */
        ~Trick();

        /**
         * @brief Set the score for the trick.
         * @param score The score value to be set
         */
        void SetScore(int32_t score);

        /**
         * @brief Set the execution time for the trick
         * @param execTime The execution time value to be set
         */
        void SetExecutionTime(uint32_t execTime);

        /**
         * @brief Get the score of the trick
         * @return The score of the trick
         */
        int32_t GetScore();

        /**
         * @brief Get the execution time of the trick
         * @return The execution time of the trick in seconds
         */
        uint32_t GetExecutionTime();
};

#endif // TRICK_H_
