#include <stdlib.h>

#include "day1/d1.h"
#include "day10/d10.h"
#include "day11/d11.h"
#include "day12/d12.h"
#include "day13/d13.h"
#include "day14/d14.h"
#include "day15/d15.h"
#include "day16/d16.h"
#include "day18/d18.h"
#include "day2/d2.h"
#include "day3/d3.h"
#include "day4/d4.h"
#include "day5/d5.h"
#include "day6/d6.h"
#include "day7/d7.h"
#include "day8/d8.h"
#include "day9/d9.h"

/**
 * Main Entry point, basically just executes all the days in order.
 * @return exit Code, doesnt matter.
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        Day1();
        Day2();
        Day3();
        Day4();
        // Day5();
        Day6();
        Day7();
        Day8();
        Day9();
        Day10();
        Day11();
        Day12();
        Day13();
        Day14();
        Day15();
        Day16();
        Day18();
        return EXIT_SUCCESS;
    }

    while ((++argv)[0]) {
        switch (strtol(argv[0], NULL, 0)) {
            case 1:
                Day1();
                break;
            case 2:
                Day2();
                break;
            case 3:
                Day3();
                break;
            case 4:
                Day4();
                break;
            case 5:
                Day5();
                break;
            case 6:
                Day6();
                break;
            case 7:
                Day7();
                break;
            case 8:
                Day8();
                break;
            case 9:
                Day9();
                break;
            case 10:
                Day10();
                break;
            case 11:
                Day11();
                break;
            case 12:
                Day12();
                break;
            case 13:
                Day13();
                break;
            case 14:
                Day14();
                break;
            case 15:
                Day15();
                break;
            case 16:
                Day16();
                break;
            case 18:
                Day18();
                break;
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}
