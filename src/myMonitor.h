/*
 * myMonitor.h
 *
 *  Created on: Apr 19, 2019
 *      Author: filip
 */

#ifndef MYMONITOR_H_
#define MYMONITOR_H_

#include <queue>
#include <stdio.h>
#include "simpleQue.h"
#include "monitor.h"

using namespace std;

class myMonitor :Monitor
{
	simque<int> que;
	Condition condProdEven, condProdOdd, condConsEven, condConsOdd;

	inline bool prodEvenCanProduce()
	{
		return (que.countEven()<10);
	}

	inline bool prodOddCanProduce()
	{
		return (que.countEven()>que.countOdd());
	}

	inline bool consEvenCanConsume()
	{
		return  (que.countEven()>0 && (que.front()%2==0) && (que.countEven())+(que.countOdd())>=3);
	}

	inline bool consOddCanConsume()
	{
		return (que.countOdd()>0 && (que.front()%2==1) && (que.countEven())+(que.countOdd())>=7);
	}

	inline void produce(int& next)
	{
		que.put(next);
	}

	inline int consume ()
	{
		return que.get();
	}

public:

	myMonitor() {};
	~myMonitor() {};

	void printQue()
	{
	queue<int> T;
		while (que.countEven()+que.countOdd()>0)
			{
			printf("%d ",que.front());
			T.push(que.get());
			}
		printf("\n");

		while(!T.empty()){
			que.put(T.front());
			T.pop();
		}
	}

	void prodEvenRun (int nextEven)
	{
		enter();

		if (!prodEvenCanProduce()) wait(condProdEven);

		produce(nextEven);

		printf("prodEven\n");
		printQue();

		if (!empty(condProdOdd) && prodOddCanProduce())
		{
			signal(condProdOdd);
		}
		else if (!empty(condConsOdd) && consOddCanConsume())
		{
			signal(condConsOdd);
		}
		else if (!empty(condConsEven) && consEvenCanConsume())
		{
			signal(condConsEven);
		}
		leave();
	}

	void prodOddRun (int nextOdd)
	{
		enter();

		if (!prodOddCanProduce()) wait(condProdOdd);

		produce(nextOdd);

		printf("prodOdd\n");
		printQue();

		if (!empty(condProdEven) && prodEvenCanProduce())
		{
			signal(condProdEven);
		}
		else if (!empty(condConsOdd) && consOddCanConsume())
		{
			signal(condConsOdd);
		}
		else if (!empty(condConsEven) && consEvenCanConsume())
		{
			signal(condConsEven);
		}
		leave();
	}

	void consEvenRun ()
	{
		enter();

		if (!consEvenCanConsume()) wait(condConsEven);

		consume();

		printf("consEven\n");
		printQue();

		if (!empty(condConsOdd) && consOddCanConsume())
		{
			signal(condConsOdd);
		}
		else if (!empty(condProdEven) && prodEvenCanProduce())
		{
			signal(condProdEven);
		}
		else if (!empty(condProdOdd) && prodOddCanProduce())
		{
			signal(condProdOdd);
		}
		leave();
	}

	void consOddRun ()
	{
		enter();

		if (!consOddCanConsume()) wait(condConsOdd);

		consume();

		printf("consOdd\n");
		printQue();

		if (!empty(condConsEven) && consEvenCanConsume())
		{
			signal(condConsEven);
		}
		else if (!empty(condProdOdd) && prodOddCanProduce())
		{
			signal(condProdOdd);
		}
		else if (!empty(condProdEven) && prodEvenCanProduce())
		{
			signal(condProdEven);
		}
		leave();
	}
};



#endif /* MYMONITOR_H_ */
