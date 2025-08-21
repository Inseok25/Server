#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

condition_variable cv;

void Producer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		cv.notify_one();

		//this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Comsumer()
{
	while (true)
	{
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {return q.empty() == false; });
		//if (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << q.size() << endl;
		}
	}
}

int main()
{
	std::thread t1(Producer);
	std::thread t2(Comsumer);

	t1.join();
	t2.join();

}