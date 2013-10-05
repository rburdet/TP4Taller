#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <sstream>
//Esta clase es utilizada para convertir numeros en strings
//para facilitar la comunicacion entre servidor y cliente

class Converter{
	public:
		static std::string convert(int value){
			std::string str;
			std::ostringstream converter;
			converter << value;
			str = converter.str();
			return str;
		}
};

#endif
