#include <iostream>
#include "tabbporo.h"
using namespace std;

int
main(void)
{
/***************************************************/
/***************** RESTA, NIVELES 	           */
/***************************************************/
  TABBPoro a,b, resta;
  TVectorPoro vec;

  TPoro p1(1,2,1,(char *) "rojo");
  TPoro p2(1,2,2,(char *) "rojo");
  TPoro p3(1,2,3,(char *) "rojo");

  a.Insertar(p2);
  a.Insertar(p1);
  a.Insertar(p3);

  b.Insertar(p1);

  resta = a-b;

  vec = resta.Niveles();

  cout <<"Niveles Resta: "<< vec << endl;

  return 1; 

}
