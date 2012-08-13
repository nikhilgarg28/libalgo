/*
* Author : Nikhil Garg
* Date   : 2010-12-31
* A templatized MinMax Queue implementation.
* Provides O(1) insert, delete, fimnMin and findMax opertions.
* Assumption : all elements pushed in queue are different. This assumption can be 
* relaxed after some extra book keeping code.
* 
* I'm pre allocating space for queues. This can also be changed by replacing vectors with STL queues.
* 
*/

#include<vector>
using namespace std;

template <class T>
class MinMaxQueue
{
	vector<T> Q, Qmax, Qmin;
	int qf, qmaxf, qminf, qb, qmaxb, qminb;
	
	public :
		
		MinMaxQueue(int N)
		{
			qf = qb = 0;       Q.resize(N);
			qmaxf = qmaxb = 0; Qmax.resize(N);
			qminf = qminb = 0; Qmin.resize(N);	
		}
		
		void push(T v)
		{
			while( qmaxf < qmaxb && Qmax[qmaxb -1] < v)	qmaxb--;
			while( qminf < qminb && Qmin[qminb -1] > v)	qminb--;
			
			Q[qb++] = v;
			Qmax[qmaxb++] = v;
			Qmin[qminb++] = v;
		}
		
		T pop()
		{
			T v = Q[qf++];
			if (v == Qmax[qmaxf])	qmaxf ++;
			if (v == Qmin[qminf])	qminf ++;
			return v;
		}

		T front()   {  return Q[qf];		}
		T getMax()  {  return Qmax[qmaxf];	}
		T getMin()  {  return Qmin[qminf];	}
		
		int size()  {  return qb - qf;		}
};
