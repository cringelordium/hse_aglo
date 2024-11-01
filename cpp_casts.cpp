#include <iostream>

struct A{
    A():a(0), b(0){}
  int a;
  int b;
};
struct B : A{
    B():A(), g(0){}
    int g;
};
struct D{
    D():f(0){}
    float f;
};
struct C : A, D{
    C() : A(), D(), d(0){}
    double d;
};

int main(){
    C* pC = new C;
    A* pA = static_cast<A*>(pC);
    D* pD = static_cast<D*> (pC);
    B* pB = static_cast<B*> (pA);
    std::cout << &(pB->g) << " " << pD << " " << pA << std::endl;
    pB->g = 100;
    std::cout << pC->a << " " << pC->b << " " << pC->f << std::endl;
    return 0;
}

