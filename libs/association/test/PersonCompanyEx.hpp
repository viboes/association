//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2010.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/association for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSOCIATION_TEST_PERSONCPMPANYEX_HPP
#define BOOST_ASSOCIATION_TEST_PERSONCPMPANYEX_HPP

#include <iostream>
#include <string>

struct Person;
struct Company;

struct Person
{
  Person(std::string const& n) : Name(n) {}
  std::string Name;
  bool operator<(Person const& rhs) const {return Name < rhs.Name; }
};

struct Company
{
  Company(std::string const& n) : Name(n) {}
  std::string Name;
  bool operator<(Company const& rhs) const {return Name < rhs.Name; }
};

template <typename OSTREAM>
OSTREAM& operator<<(OSTREAM& os, Person const& p)
{
  os << p.Name;
  return os;
}
template <typename OSTREAM>
OSTREAM& operator<<(OSTREAM& os, Company const& p)
{
  os << p.Name;
  return os;
}

struct employee
{
};
struct employer
{
};
struct contract
{
};
struct consultant
{
};
struct client
{
};
struct owner
{
};
struct company
{
};
struct boss
{
};
struct subordinate
{
};

struct Contract
{
  Contract(int s) :
    Salary(s)
  {
  }
  int Salary;
};

struct ConsultancyContract: Contract
{
  ConsultancyContract(int s, int h) :
    Contract(s), Hours(h)
  {
  }
  int Hours;
};

#endif
