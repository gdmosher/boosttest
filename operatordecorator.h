// Gordon Mosher / Yichao Chen
// SID: 861266106 / 861303577
// Email: gordon.mosher@email.ucr.edu / ychen177@ucr.edu

#ifndef __OPERATORDECORATOR_H__
#define __OPERATORDECORATOR_H__
#include "component.h"  // source for Base and Operator clases
#include <math.h>

/*
class Base {
    public:
//      Constructors
        Base() {}

//      Pure Virtual Functions
        virtual double evaluate() = 0;
};

class Operator: public Base {
	protected:
		Base* left, *right;
	public:
		Operator() : Base() {};
		Operator(Base* l, Base* r) : left(l), right(r) {};
		
		Base* get_left() { return left; };
		Base* get_right() { return right; };
		
		virtual double evaluate() = 0;
};
*/


//Decorator Class
class OperatorDecorator: public Operator {
  public:
    OperatorDecorator() : Operator() {};//* operator = new Operator)
    ~OperatorDecorator();
    virtual double evaluate() = 0;
    OperatorDecorator(Base* l, Base* r) : Operator(l,r) {}; // this->left(l), this->right(r) {};
    Base* get_left()  { return this->get_left();  };
    Base* get_right() { return this->get_right(); };
  private:
    OperatorDecorator* m_wrappee;

};

class Ceil: public OperatorDecorator {
  public:
    Ceil() : OperatorDecorator() { };// * od = new OperatorDecorator);
    ~Ceil();
    Ceil(Base* left) : OperatorDecorator(left, right) {};
    double evaluate() { return ceil(this->left->evaluate()); }

};

class Abs: public OperatorDecorator {
  public:
    Abs() : OperatorDecorator() { };// * od = new OperatorDecorator);
    ~Abs();
    Abs(Base* left) : OperatorDecorator(left, right) {};
    double evaluate() { return abs(this->left->evaluate()); }

};

class Floor: public OperatorDecorator {
  public:
    Floor() : OperatorDecorator() { };// * od = new OperatorDecorator);
    ~Floor();
    Floor(Base* left) : OperatorDecorator(left, right) {};
    double evaluate() { return floor(this->left->evaluate()); }

};

/*
class Add2: public Operator {
  public:
    Add2() : Operator() { };
    ~Add2();
    Add2 (Base* left, Base* right) : Operator(left, right) {};
    double evaluate() {
		return this->left->evaluate() + this->right->evaluate();
	};
};

class Sqr2: public Operator {
  public:
    Sqr2() : Operator(){ };
    ~Sqr2();
    Sqr2 (Base* left) : Operator(left, right) {};
    double evaluate() {
		return this->left->evaluate() * this->left->evaluate();
	};
};
*/

#endif // __OPERATORDECORATOR_H___
