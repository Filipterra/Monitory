//============================================================================
// Name        : Monitors.cpp
// Author      : Filip Przybysz
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "myMonitor.h"

using namespace std;

int PROD_EVEN_NUM=5;
int PROD_ODD_NUM=5;
int CONS_EVEN_NUM=5;
int CONS_ODD_NUM=5;

void thProdEven (myMonitor* mon)
{
	int nextEven=0;
	while(1) {
		mon->prodEvenRun(nextEven);
		nextEven=(nextEven+2)%100;
		srand (time(NULL));
		this_thread::sleep_for(std::chrono::milliseconds((rand()%1000+500)));
	};
}

void thProdOdd (myMonitor* mon)
{
	int nextOdd=1;
	while(1) {
		mon->prodOddRun(nextOdd);
		nextOdd=(nextOdd+2)%100;
		srand (time(NULL));
		this_thread::sleep_for(std::chrono::milliseconds((rand()%1000+500)));
	};
}

void thConsEven (myMonitor* mon)
{
	while(1) {
		mon->consEvenRun();
		srand (time(NULL));
		this_thread::sleep_for(std::chrono::milliseconds((rand()%1000+500)));
	};
}

void thConsOdd (myMonitor* mon)
{
	while(1) {
		mon->consOddRun();
		srand (time(NULL));
		this_thread::sleep_for(std::chrono::milliseconds((rand()%1000+500)));
	};
}

int main() {

	myMonitor queMon;

		thread PE[PROD_EVEN_NUM], PO[PROD_ODD_NUM], CE[CONS_EVEN_NUM], CO[CONS_ODD_NUM];

		for (int i=0; i<PROD_ODD_NUM; ++i)
		{
			PO[i]=thread(thProdOdd, &queMon);
		}
		for (int i=0; i<PROD_EVEN_NUM; ++i)
		{
			PE[i]=thread(thProdEven, &queMon);
		}
		for (int i=0; i<CONS_EVEN_NUM; ++i)
		{
			CE[i]=thread(thConsEven, &queMon);
		}
		for (int i=0; i<CONS_ODD_NUM; ++i)
		{
			CO[i]=thread(thConsOdd, &queMon);
		}

		for (int i=0; i<PROD_EVEN_NUM; ++i)
		{
			PE[i].join();
		}
		for (int i=0; i<PROD_ODD_NUM; ++i)
		{
			PO[i].join();
		}
		for (int i=0; i<CONS_EVEN_NUM; ++i)
		{
			CE[i].join();
		}
		for (int i=0; i<CONS_ODD_NUM; ++i)
		{
			CO[i].join();
		}

	return 0;
}
