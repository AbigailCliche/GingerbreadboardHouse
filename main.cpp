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
	/**while(1)
	{
		cout << "I'm in manage_ble()!"<< endl;
		std::this_thread::sleep_for(std::chrono::microseconds{});
	}**/
	int fd, c;
	if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		//cout << "Unable to open serial device: " << strerror (errno) << endl;
		return 1 ;
	}
	while(1)
	{
		c = serialGetchar(fd) ;
		cout << c << endl;
	}
}

void wax_warmer()
{
	softPwmCreate(6, 0, 100); // GPIO  Peltier Device
	warmer = ON;
	while(1)
	{
		int power = (int) (100-100*float(temp_sensor)/40000);
		if ( warmer == ON)
		{
			softPwmWrite(6, 20);
		}
		else
		{
			softPwmWrite(6, 00);
		}
	}
}



void manage_lights()
{
	softPwmCreate(0, 0, 100) ; // GPIO 0 Rooftop Lights
	softPwmCreate(2, 0, 100) ; // GPIO 1 Window Candles
	
	while (1)
	{
		//cout << "Night: " << night << endl;
		if(night == true)
		{
			softPwmWrite (0, 10);
			softPwmWrite(2, 50);
			//softPwmWrite(2, (100*rand()/float(RAND_MAX)));
		}
		else
		{
			softPwmWrite (0, 100);
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
		//if (temp_sensor > 22000)  // TODO: Find real threshold value
		//{
		//	warmer = ON;
		//}else{
		//	warmer = OFF;
		//}
		photocell = analogRead(AD_BASE+1);
		//cout << "Photocell: " << photocell << endl;
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
	//pinMode (5, OUTPUT) ;
	//pullUpDnControl (1,PUD_DOWN) ;
	softPwmCreate(5, 0, 100) ; // GPIO 7 Motor
	
	// Start Threads
	thread t2(manage_ble);
	thread t3(manage_lights);
	thread t4(read_analog_ins);
	
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
					//if (music == OFF){
						music = ON;
						execlp("bash", " ", "playMusic.sh", NULL);
						execlp("\n", NULL);
					//}
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
				//if((ppid=fork())==0){
					cout << "Killing music" << endl;
					//execlp("bash", " ", "killMusic.sh");
					//execlp("bash", " ", "killMusic.sh");
					//return 0;
				//}
				system("killall omxplayer.bin");
			}
		}
		//cout << "I'm in main()!"<< endl;
		sleep(0.005);
		std::this_thread::sleep_for(std::chrono::seconds{});
	}
	
	//t2.join();
	//t3.join();
}
