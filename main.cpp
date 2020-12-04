#include <iostream> 
#include <thread> 
#include <chrono>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <softPwm.h>
#include <cmath>
#include <ads1115.h>
#include <stdlib.h>
#include <unistd.h>

#define AD_BASE 160
#define OFF 0
#define ON 1

using namespace std; 

volatile bool night = false;
volatile double photocell, temp_sensor;
int warmer = OFF;

int manage_ble()
{

	int fd, c;
	char letter;
	if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		//cout << "Unable to open serial device: " << strerror (errno) << endl;
		return 1 ;
	}
	while(1)
	{
		c = serialGetchar(fd) ;
		letter = 'A' + c - 65;
		if ((letter > 'A') && (letter < 'z'))
		{
			if (warmer == ON)
			{
				warmer = OFF;
				cout << "Warmer turning OFF" << endl;
				serialGetchar(fd) ;
				serialGetchar(fd) ;
			}
			else
			{
				warmer = ON;
				cout << "Warmer turning ON" << endl;
				serialGetchar(fd) ;
				serialGetchar(fd) ;
			}
		}
	}
}

void wax_warmer()
{
	softPwmCreate(6, 0, 0); // GPIO 6 Peltier Device
	warmer = OFF;
	while(1)
	{
		if ( warmer == ON)
		{
			// Run Peltier device at level inversely proportional to temperature
			int power = (int) (100-100*float(temp_sensor)/40000);
			softPwmWrite(6, power);
		}
		else
		{
			softPwmWrite(6, 0);
		}
	}
}



void manage_lights()
{
	softPwmCreate(0, 0, 100) ; // GPIO 0 Rooftop Lights
	softPwmCreate(2, 0, 100) ; // GPIO 1 Window Candles
	
	while (1)
	{
		if(night == true)
		{
			softPwmWrite (0, 100);
			softPwmWrite(2, 50);
		}
		else
		{
			softPwmWrite (0, 50);
			softPwmWrite (2, 0);
		}
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}
}

void read_analog_ins()
{
	ads1115Setup(AD_BASE, 0x48);
	while(1)
	{
		temp_sensor = analogRead(AD_BASE+0);
		photocell = analogRead(AD_BASE+1);
		// Update night variable
		if (photocell > 16000)
		{
			night = true;
		}else{
			night = false;
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
	
	// Set up tree control switch and motor
	pinMode (1, INPUT) ;
	softPwmCreate(5, 0, 100) ; // GPIO 7 Motor
	
	// Start Threads
	thread t2(manage_ble);
	thread t3(manage_lights);
	thread t4(read_analog_ins);
	thread t5(wax_warmer);
	
	// Tree control logic
	int music = OFF;
	int ppid;
	bool flipped=false;
	while(1) 
	{
		
		//cout << digitalRead(1) << endl;
		if (digitalRead(1) == 1 && flipped==false)
		{
			flipped = true;
			softPwmWrite(5, 35);
			if (music == OFF){
				
				music = ON;
				cout << "Playing music" << endl;
				ppid=fork();
				if (ppid==0){
						music = ON;
						execlp("bash", " ", "playMusic.sh", NULL);
						execlp("\n", NULL);
					_exit(0);
					return 0;
				}
			}
		}
		else if(digitalRead(1)==0)
		{
			flipped=false;
			softPwmWrite(5, 0);
			if (music == ON){
				
				music = OFF;
					cout << "Killing music" << endl;
				system("killall omxplayer.bin");
			}
		}
		sleep(0.005);
		//std::this_thread::sleep_for(std::chrono::seconds{});
	}
}
