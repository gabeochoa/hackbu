#ifndef QFETCHER_H
#define QFETCHER_H

#include <pebble.h>
#include <questionwindow.h>
	
struct question
{
		char* q;
		char* answers[4];
		char* correctanswer;
		struct question* next_q;
};

struct deck
{
	 char* category;
	 struct question questions[10];
};


	
#endif 