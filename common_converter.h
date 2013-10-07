#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <sstream>
//Esta clase es utilizada para convertir numeros en strings
//y para formar mensajes con palabras y numeros
//para facilitar la comunicacion entre servidor y cliente

class Converter{
	public:
		static std::string convert(const std::string& begin,int value,const std::string& end=""){
			std::string MSG=begin;
			std::string str;
			std::ostringstream converter;
			converter << value;
			MSG.append(converter.str());
			MSG.append(end);
			return MSG;
		}
};

#endif
