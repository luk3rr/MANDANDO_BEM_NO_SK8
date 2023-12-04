/*
 * Filename: main.cc
 * Created on: November  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "skatepark.h"
#include "vector.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    uint16_t numSections, numTricks, sectionBonus;
    uint32_t sectionTraversalTime, trickExecutionTime;
    int32_t  trickScore;

    std::cin >> numSections >> numTricks;

    SkatePark sk8Park;

    for (std::size_t i = 0; i < numSections; i++)
    {
        std::cin >> sectionBonus >> sectionTraversalTime;
        sk8Park.AddSection(sectionBonus, sectionTraversalTime);
    }

    for (std::size_t i = 0; i < numTricks; i++)
    {
        std::cin >> trickScore >> trickExecutionTime;
        sk8Park.AddTrick(trickScore, trickExecutionTime);
    }

    std::cout << sk8Park.FindMostFuckingRadicalTrick() << std::endl;
    sk8Park.ShowTricksList();

    return EXIT_SUCCESS;
}
