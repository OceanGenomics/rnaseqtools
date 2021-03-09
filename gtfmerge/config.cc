#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

double min_transcript_coverage = -1;
bool merge_coverage_as_counts = false;
bool counts_and_coverage = false;
bool print_samples = false;
int num_threads = 1;

int parse_parameters(int argc, const char ** argv)
{
	for(int i = 1; i < argc; i++)
	{
		if(string(argv[i]) == "-c")
		{
			min_transcript_coverage = atof(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-t")
		{
			num_threads = atoi(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-n")
		{
			merge_coverage_as_counts = true;
		}
		else if(string(argv[i]) == "-b")
		{
			counts_and_coverage = true;
		}
		else if(string(argv[i]) == "-w")
		{
			print_samples = true;
		}
	}

	// not compatible with each other
	if (merge_coverage_as_counts && counts_and_coverage) {
		printf("Error: -b and -n are not compatible with each other!\n");
		return 1;
	}

	return 0;
}

int print_help()
{
	printf("\n");
	printf("usage: gtfmerge union <input-gtf-list> <output-unioned-gtf> [options]\n");
	printf("\n");
	printf("options:\n");
	printf(" %-14s  %s\n", "-t <integer>",  "number of threads");
	printf(" %-14s  %s\n", "-n",  "only output number of transcript occurrences");
	printf(" %-14s  %s\n", "-b",  "output total coverage sum as well as occurrences. Not compatible with -n");
	printf(" %-14s  %s\n", "-w",  "write samples containing each transcript to <output-unioned-gtf>.samples.txt");
	return 0;
}
