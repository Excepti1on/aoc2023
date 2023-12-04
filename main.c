#include <stdlib.h>

#include "day1/d1.h"
#include "day2/d2.h"
#include "day3/d3.h"
#include "day4//d4.h"

/**
 * Main Entry point, basically just executes all the days in order.
 * @return exit Code, doesnt matter.
 */
int main() {
	Day1();
	Day2();
	Day3();
	Day4();
	return EXIT_SUCCESS;
}
