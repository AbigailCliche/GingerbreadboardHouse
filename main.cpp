#include <iostream> 
#include <thread> 
#include <chrono>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <softPwm.h>
#include <cmath>

using namespace std; 

bool is_night()
{
	while(1)
	{
		cout << "I'm in is_night()!"<< endl;
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}
	return true;
}


int manage_ble()
{
	/**while(1)
	{
		cout << "I'm in manage_ble()!"<< endl;
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}**/
	int fd;
	if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		//cout << "Unable to open serial device: " << strerror (errno) << endl;
		return 1 ;
	}
	while(1)
	{
		serialPutchar (fd, 'a') ;
	}
}

viod manage_lights()
{
	softPwmCreate(0, 0, 100) ; // GPIO 0 Rooftop Lights
	softPwmCreate(1, 0, 100) ; // GPIO 1 Window Candles
	
	while (1)
	{
		if (night)
		{
			softPwmWrite (0, 20);
		}
		else
		{
			softPwmWrite (0, (100*rand()/float(RAND_MAX)));
		}
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}
}

int main()
{
	wiringPiSetup () ;
	if (wiringPiSetup () == -1)
	{
		//cout << "Unable to start wiringPi: " << strerror (errno) << endl ;
		return 1 ;
	}
	// Start Threads
	std::thread t1(is_night);
	std::thread t2(manage_ble);
	while(1) 
	{
		cout << "I'm in main()!"<< endl;
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}
	t1.join();
	t2.join();
}
