#ifndef __GPIO_H__
#define __GPIO_H__

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using uint=unsigned int;

namespace GPIO{
	enum Dir:uint{IN,OUT};
	enum Val:uint{LOW,HIGH};

	class Pin{
		private:
			int pin;
			Dir dir;
			Val val;
		public:
			Pin(int pin);
			~Pin();
			void direct(Dir dir);
			void set(Val val);
			Val get();
	};
};

#endif
