// Gordon Mosher / Yichao Chen
// SID: 861266106 / 861303577
// Email: gordon.mosher@email.ucr.edu / ychen177@ucr.edu

#ifndef __BASEFACTORY_H__
#define __BASEFACTORY_H__
//#include <iostream>     // std::cout, std::hexfloat, ste::defaultfloat
//#include "container.h"
//#include "vector_container.h"
#include "BasePrint.h"

class BaseFactory {
    public:
        /* Constructors */
        BaseFactory() {}

        /* Pure virtual generate function */
        virtual BasePrint* generatePrint(double value) = 0;

};

class DoubleFactory: public BaseFactory {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        DoubleFactory() : BaseFactory() {};

        /*  Define generate function */
  		  BasePrint* generatePrint(double value) {
          DoublePrint* dblprt = new DoublePrint(value);
          return dblprt;
        }
};

class HexFactory: public BaseFactory {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        HexFactory() : BaseFactory() {};

        /*  Define generate function */
  		  BasePrint* generatePrint(double value) {
          HexPrint* hexprt = new HexPrint(value);
          return hexprt;
        }
};

class BinaryFactory: public BaseFactory {
    private:
        /* Value to print */
        double value;

    public:
        /* Constructors */
        BinaryFactory() : BaseFactory() {};

        /*  Define generate function */
  		  BasePrint* generatePrint(double value) {
          BinaryPrint* binprt = new  BinaryPrint(value);
          return binprt;
        }
};

#endif // __BASEFACTORY_H__

