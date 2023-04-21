// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mutex evMutex1;
condition_variable cv1;

shared_mutex evMutex2;
condition_variable_any cv2;

void MyThread1(int id)
{
	SafeWrite("Thread", id, "start");
	unique_lock<mutex> ul(evMutex1);
//	cv1.wait(ul, [id] {SafeWrite("cv1 wait completed", id); return true; });
	cv1.wait(ul);

	SafeWrite("Thread", id, "cv capture");
	Sleep(1000);
	SafeWrite("Thread", id, "end");

	cv1.notify_one();
}

void MyThread2(int id)
{
	SafeWrite("Thread", id, "start");
	shared_lock<shared_mutex> ul(evMutex2);
	cv2.wait(ul);

	SafeWrite("Thread", id, "cv capture");
	Sleep(1000);
	SafeWrite("Thread", id, "end");
}

void start1()
{
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread1, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
//	cv1.notify_all();
	cv1.notify_one();
	_getch();
}

void start2()
{
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread2, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
	cv2.notify_all();
	_getch();
}

template<typename T> void generate(vector<T>& v, int n)
{
	default_random_engine rnd;
	random_device dev;
	uniform_real_distribution<double> distr(0, 100);
	rnd.seed(dev());

	v.clear();
	for (int i = 0; i < n; i++)
	{
		v.push_back(distr(rnd));
	}
}

// выборочное среднее для диапазона значений
template<typename T>
double mean(T begin, T end)
{
	return accumulate(begin, end, 0.0) / double(end - begin);
}


// выборочная дисперсия (несмещенная) для диапазона значений
tuple<double, double, size_t> mean_and_variance(vector<double>::const_iterator begin, vector<double>::const_iterator end)
{
	const double a = mean(begin, end);
	const size_t N = end - begin;

	return make_tuple(a,
		accumulate(begin, end, 0.0,				// расчет дисперсии
			[&a, &N](const double& accumulator, const double& y) -> double
			{
				return accumulator + double((y - a) * (y - a)) / double(N - 1);
			}),
		N);
}


void threaded_calc(const vector<double>& v, int nThreads)
{
	const auto t1 = chrono::steady_clock::now();
	vector<future<tuple<double, double, size_t>>> future_res(nThreads);
	double mean = 0;
	double variance = 0;

	cout << endl << nThreads << " threads: " << endl;

	size_t count = v.size() / nThreads;
	for (int i = 0; i < nThreads; i++)
	{
		if (i < nThreads - 1)
			future_res[i] = async(std::launch::async, mean_and_variance, v.begin() + i * count, v.begin() + (i + 1) * count);
		else
			future_res[i] = async(std::launch::async, mean_and_variance, v.begin() + i * count, v.end());
	}

	for (auto& r : future_res)
	{
		auto [m, v, n] = r.get();
		cout << m << "\t" << v << "\t" << n << endl;
		mean += m;
		variance += v * n;
	}

	mean /= nThreads;
	variance /= v.size();

	const auto t2 = chrono::steady_clock::now();
	const auto msec = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	cout << msec << " msec" << endl << mean << endl << variance << endl << endl;
}


void start3()
{
	int nMax = thread::hardware_concurrency();

	vector<double> v;
	generate(v, 10000000);

	auto [mean, variance, n] = mean_and_variance(v.begin(), v.end());
	cout << mean << ", " << variance << endl;
	for (int n = 1; n <= nMax * 2; n++)
	{
		threaded_calc(v, n);
	}

}

CWinApp theApp;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
//			start1();
//			start2();
			start3();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
