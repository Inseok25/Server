#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>


atomic<bool> flag;

int main()
{
	flag = false;

	flag.store(true, memory_order_seq_cst);

	bool val = flag.load(memory_order_seq_cst);

	{
		bool prev = flag.exchange(true);
	}

	{
		bool expected = false;
		bool desired = true;
		flag.compare_exchange_strong(expected, desired);

		if (flag == expected)
		{
			flag = desired;
			return true;
		}
		else
		{
			expected = flag;
			return false;
		}
		while (true)
		{
			bool expected = false;
			bool desired = true;
			flag.compare_exchange_weak(expected, desired);
		}
	}

}