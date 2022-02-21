#ifndef __TIME_HPP_
#define __TIME_HPP_
#define __SHE_TEST_

#ifdef __SHE_TEST_
#include <iostream>
#endif // __SHE_TEST

#include <random>
#include <time.h>

class countdown
{
public:
	countdown():m_begin_time(0),m_end_time(0) {};
	~countdown() {};
public:
	//返回一个150-300之间的随机数
	int getRandomTime() {
		std::random_device rd;
		return (rd() % 150 + 150);
	}
	
	void beginTag() {
		m_begin_time = clock();
	}

	void endTag(){
		m_end_time = clock();
	}

	int getTimeDifference() {
		return int(m_end_time - m_begin_time);
	}

	void clear(){
		m_begin_time = 0;
		m_end_time = 0;
	}

private:
	clock_t m_begin_time;
	clock_t m_end_time;
};




#endif // !__TIME_HPP_
