#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "day1/d1.h"
#include "day2/d2.h"
#include "day3/d3.h"
#include "day4//d4.h"

/**
 * Main Entry point, basically just executes all the days in order.
 * @return exit Code, doesnt matter.
 */
int main(int argc, char* argv[]) {
	if (argc == 1)
	{
		Day1();
		Day2();
		Day3();
		Day4();
		return EXIT_SUCCESS;
	}
	
	while ((++argv)[0]){
			switch (argv[0][0]){
			case '1':
				Day1();
				break;

			case '2':
				Day2();
				break;

			case '3':
				Day3();
				break;

			case '4':
				Day4();
				break;
			
			default:
				break;
			}
	}
	
	return EXIT_SUCCESS;
}
