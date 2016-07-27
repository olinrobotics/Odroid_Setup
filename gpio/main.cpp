#include <iostream>
#include <memory.h>
#include "GPIO.h"
#include <signal.h>
volatile bool quit = false;

void sig_handler(int){
	quit = true;
}

using namespace GPIO;

int test_out(int _pin){

	Val val = Val::LOW;

	Pin pin(_pin);

	pin.direct(Dir::OUT);

	while(!quit){
		val = ((val == Val::LOW)? Val::HIGH : Val::LOW);
		pin.set(val);
	}

	//std::cout << pin.get() << std::endl;
	//waiting...
	char garbage;
	std::cin >> garbage;

	return 0;
}

int test_in(int _pin){

	struct sigaction sig_struct;
	sig_struct.sa_handler = sig_handler;
	sig_struct.sa_flags = 0;
	sigemptyset(&sig_struct.sa_mask);
	if (sigaction(SIGINT, &sig_struct, NULL) == -1){
		return -1;
	}

	Pin pin(_pin);
	pin.direct(Dir::IN);

	while(!quit){
		std::cout << "VALUE : " << pin.get() << std::endl;
	}

	return 0;
}

int main(int argc, char* argv[]){
	if(argc != 3){
		std::cout << "USAGE : " << argv[0] << " <PIN> <IN|OUT>" << std::endl;
		return -1;
	}

	int pin = std::stoi(argv[1]);

	if(strcmp(argv[2], "IN") == 0){
		return test_in(pin);
	}else if (strcmp(argv[2], "OUT") == 0){
		return test_out(pin);
	}
}
