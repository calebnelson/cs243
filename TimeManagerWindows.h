/*
 * TimeManagerWindows.h
 *
 *  Created on: Nov 16, 2017
 *      Author: User
 */

#ifndef TIMEMANAGERWINDOWS_H_
#define TIMEMANAGERWINDOWS_H_

class TimeManager{
	private:
		LARGE_INTEGER frequency;
		LARGE_INTEGER st;
		LARGE_INTEGER ed;
		double interval = 0.0;

	public:
		void start();
		void end();
		double getInterval();
};

#endif /* TIMEMANAGERWINDOWS_H_ */
