// file      : Example/ExH/BadCast/bad_cast.cpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

#include "Utility/ExH/System/Exception.hpp"

#include <iostream>

using std::cerr;
using std::endl;


struct A
{
  virtual
  ~A() {}
};

struct B
{
  void
  foo () {}
};

void
foo ()
{
  A a;

  A& ar (a);

  B& br (dynamic_cast<B&> (ar));

  br.foo ();
}

int
main ()
{
  try
  {
    foo ();
  }
  catch (Utility::ExH::System::Exception const& ex)
  {
    cerr << "Caught Utility::ExH::System::Exception: "
         << ex.what ()
         << endl;
  }
}
//$Id: bad_cast.cpp 79112 2007-07-31 09:41:46Z sowayaa $
