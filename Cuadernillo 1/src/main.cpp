#include <iostream>

using namespace std;

#include "tporo.h"
#include "tvectorporo.h"
#include "tlistaporo.h"


int
main()
{
{
  TPoro a(1, 2, 3, (char*) "rojo");

  cout << a << endl;
}
{
  TPoro a(1, 2, 3, (char*) "rojo");
  TVectorPoro v(5);

  v[1] = a;
  v[2] = a;
  v[3] = a;
  v[4] = a;
  v[5] = a;

  cout << v << endl;
}
{
  TPoro p(1, 1, 1), q(2, 2, 2), r(3, 3, 3);
  TListaPoro a;

  a.Insertar(p); a.Insertar(q); a.Insertar(r);

  cout << a << endl;
}

}