#include "GPIO.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace GPIO{
	Pin::Pin(int pin):pin(pin){
		std::cout << "SETTING UP PIN " << pin << " ..." << std::endl;
		std::ofstream os("/sys/class/gpio/export");
		os << pin; //should I make this into a string?
		os.close();
	}

	Pin::~Pin(){
		std::cout << "CLEANING UP PIN " << pin << " ..." << std::endl;
		std::ofstream os("/sys/class/gpio/unexport");
		os << pin;
		os.close();
	}

	void Pin::direct(Dir dir){
		this->dir = dir;
		std::stringstream oss;
		oss << "/sys/class/gpio/gpio" << pin << "/direction";
		std::ofstream os(oss.str());
		os << ((dir == Dir::OUT)? "out" : "in");
		os.close();
	}
	void Pin::set(Val val){

		this->val = val;
		std::stringstream oss;
		oss << "/sys/class/gpio/gpio" << pin << "/value";
		std::cout << oss.str() << std::endl;
 
		std::ofstream os(oss.str());
 
		os << val; //(val == Val::LOW)? '0' : '1'); 
 
		os.close();
	}

	Val Pin::get(){
		if (dir == Dir::IN){
			std::stringstream iss;
			iss << "/sys/class/gpio/gpio" << pin << "/value";
			std::ifstream is(iss.str());

			int v;
			is >> v;

			val = (Val)v;
			is.close();
		}
		//otherwise simply return value
		//
		return val;
	}

}
