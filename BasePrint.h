// Gordon Mosher / Yichao Chen
// SID: 861266106 / 861303577
// Email: gordon.mosher@email.ucr.edu / ychen177@ucr.edu

#ifndef __BASEPRINT_H__
#define __BASEPRINT_H__
#include <iostream>     // std::cout, std::hexfloat, ste::defaultfloat
#include <bitset>       // std::bitset
//#include "container.h"
//#include "vector_container.h"

class BasePrint {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        BasePrint();
        BasePrint(double value) {this->value=value;};

        /* Pure virtual print function */
        virtual void print() = 0;

};

class DoublePrint: public BasePrint {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        DoublePrint() : BasePrint() {};
        DoublePrint(double value) : BasePrint(value) {this->value=value;};

        /*  Define print function */
  		void print() {
        std::cout << value << " ";
//	  		for (unsigned int i = 0; i < cVector.size(); i++)
//		  	{
//			  	std::cout << cVector.at(i)->evaluate() << ' ';
//  			}
      }
};

class HexPrint: public BasePrint {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        HexPrint() : BasePrint() {};
        HexPrint(double value) : BasePrint(value) {this->value=value;};

        /*  Define print function */
  		void print() {
        std::cout.precision(5);

//        std::cout << "hexfloat:\n" << std::hexfloat;
        int ivalue = value;
        std::cout << std::hex << ivalue << " ";
//        std::cout << "defaultfloat:\n" << std::defaultfloat;

      }
};

class BinaryPrint: public BasePrint {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        BinaryPrint() : BasePrint() {};
        BinaryPrint(double value) : BasePrint(value) {this->value=value;};

        /*  Define print function */
  		void print() {
        std::bitset<16> foo (value);
        std::cout << foo << " ";

      }
};

#endif // __BASEPRINT_H__

