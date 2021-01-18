/*
 * Macros.h
 *
 * Created: 10/31/2019 9:01:54 PM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef MACROS_H_
#define MACROS_H_

	#define SETBIT(R,B)			((R) |= (1<<(B)))
	#define CLEARBIT(R,B)		((R) &=~(1<<(B)))
	#define TOGGLEBIT(R,B)		((R) ^= (1<<(B)))
	#define READBIT(R,B)		(((R) & (1<<(B)))>>(B))



#endif /* MACROS_H_ */	