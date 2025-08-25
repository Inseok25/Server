#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

#include <future>

int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100'000; i++)
	{
		sum += i;
	}

	return sum;
}

void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("Secret Message");
}

void TaskWorker(std::packaged_task<int64(void)>&& task)
{
	task();
}

int main()
{
	//동기(synchronous) 실행
	//int64 sum = Calculate();
	//cout << sum << endl;
	{
		std::future<int64> future = std::async(std::launch::async, Calculate);

		//future.wait_for(std::chrono::microseconds(1));
		int64 sum = future.get();
	

		class Knight
		{
		public:
			int64 GetHp() {return 100;	};
		};

		Knight knight;

		std::future<int64> future2 = std::async(std::launch::async, &Knight::GetHp, knight);


	}

	{
		std::promise<string> promise;
		std::future<string> future = promise.get_future();

		thread t(PromiseWorker, std::move(promise));

		string message = future.get();
		cout << message << endl;

		t.join();
	}

	{
		std::packaged_task<int64(void)> task(Calculate);
		std::future<int64> future = task.get_future();

		std::thread t(TaskWorker, std::move(task));

		int64 sum = future.get();
		cout << sum << endl;

		t.join();
	}
}