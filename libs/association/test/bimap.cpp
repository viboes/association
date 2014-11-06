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

#include <boost/association/biassoc.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <iostream>
#include "./PersonCompanyEx.hpp"

using namespace boost;
using namespace boost::bimaps;
using namespace boost::association;

//#define BIMAP
#ifdef BIMAP
typedef bimap<
                  tagged< Person*,   employee> ,
    multiset_of<  tagged< Company*,  employer> >,
    with_info<    tagged< Contract*, contract> >
> Employment;

typedef bimap<
    multiset_of<  tagged< Person*,              consultant> >,
    multiset_of<  tagged< Company*,             client> >,
    set_of_relation<>,
    with_info<    tagged< ConsultancyContract*, contract> >
> Consultancy;

#else
class Employment : public extrinsic<Employment,
                  tagged< Person*,   employee>  ,
    multiset_of<  tagged< Company*,  employer> >,
    set_of_relation<>,
    with_info<    tagged< Contract*, contract> >
>
{};

class Consultancy : public extrinsic<Consultancy,
      multiset_of<  tagged< Person*,              consultant> >,
      multiset_of<  tagged< Company*,             client> >,
      set_of_relation<>,
      with_info<    tagged< ConsultancyContract*, contract> >
> {};


#endif


int main()
{
  Person John("John"), Jane("Jane");
  Company Dell("Dell"), HP("HP");
  Contract JohnContract(100);
  ConsultancyContract JaneContractD(20, 2);
  ConsultancyContract JaneContractH(30, 3);

#ifdef BIMAP
  Employment employment;
  Consultancy consultancy;
#else
  Employment& employment=Employment::assoc();
  Consultancy& consultancy=Consultancy::assoc();
#endif
  employment.insert(Employment::value_type(&John, &Dell, &JohnContract));

  consultancy.insert(Consultancy::value_type(&Jane, &Dell, &JaneContractD));
  employment.insert(Employment::value_type(&Jane, &Dell, &JaneContractD));

  std::cout << "=========================" <<std::endl ;
  {
    for (auto p = employment.begin(); p != employment.end(); ++p)
    {
      std::cout
      << "employee: " << *(p->get<employee>()) << std::endl
      << "employer: " << *(p->get<employer>()) << std::endl
      << "Salary:   " << p->get<contract>()->Salary << std::endl;
    }
  }
  std::cout << "---------------------------" <<std::endl ;
  {
    for (auto p = consultancy.begin(); p != consultancy.end(); ++p)
    {
      std::cout
      << "client:     " << *(p->get<client>()) << std::endl
      << "consultant: " << *(p->get<consultant>()) << std::endl
      << "Salary:     "   << p->get<contract>()->Salary << std::endl
      << "Hours:      " << p->get<contract>()->Hours << std::endl
          ;
    }
  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
  consultancy.insert(Consultancy::value_type(&Jane, &HP, &JaneContractH));
  //employment.insert(Employment::value_type(&Jane, &HP, &JaneContractH));
  std::cout << "=========================" <<std::endl ;
  {
    for (auto p = employment.begin(); p != employment.end(); ++p)
    {
      std::cout
      << "employee: " << *(p->get<employee>()) << std::endl
      << "employer: " << *(p->get<employer>()) << std::endl
      << "Salary:   " << p->get<contract>()->Salary << std::endl
      ;
    }
  }
  std::cout << "---------------------------" <<std::endl ;
  {
    for (auto p = consultancy.begin(); p != consultancy.end(); ++p)
    {
      std::cout
      << "client:     " << *(p->get<client>()) << std::endl
      << "consultant: " << *(p->get<consultant>()) << std::endl
      << "Salary:     "   << p->get<contract>()->Salary << std::endl
      << "Hours:      " << p->get<contract>()->Hours << std::endl
          ;
    }
  }
//  {
//    auto rng = consultancy.by<consultant> ().equal_range(&Jane);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->second) << std::endl
//      << "consultant: " << *(p->first) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
  consultancy.erase(Consultancy::value_type(&Jane, &Dell,0));
  std::cout << "=========================" <<std::endl ;
  {
    for (auto p = employment.begin(); p != employment.end(); ++p)
    {
      std::cout
      << "employee: " << *(p->get<employee>()) << std::endl
      << "employer: " << *(p->get<employer>()) << std::endl
      << "Salary:   " << p->get<contract>()->Salary << std::endl
      ;
    }
  }
  std::cout << "---------------------------" <<std::endl ;
  {
    for (auto p = consultancy.begin(); p != consultancy.end(); ++p)
    {
      std::cout
      << "client:     " << *(p->get<client>()) << std::endl
      << "consultant: " << *(p->get<consultant>()) << std::endl
      << "Salary:     "   << p->get<contract>()->Salary << std::endl
      << "Hours:      " << p->get<contract>()->Hours << std::endl
          ;
    }
  }
//  {
//    auto rng = consultancy.by<consultant> ().equal_range(&Jane);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->second) << std::endl
//      << "consultant: " << *(p->first) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = employment.by<employer> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "employee: " << *(p->second) << std::endl
//      << "employer: " << *(p->first) << std::endl
//      << "Salary:   " << p->info->Salary << std::endl;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&Dell);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
//  std::cout << "---------------------------" <<std::endl ;
//  {
//    auto rng = consultancy.by<client> ().equal_range(&HP);
//
//    for (auto p = rng.first; p != rng.second; ++p)
//    {
//      std::cout
//      << "client:     " << *(p->first) << std::endl
//      << "consultant: " << *(p->second) << std::endl
//      << "Salary:     "   << p->info->Salary << std::endl
//      << "Hours:      " << p->info->Hours << std::endl
//          ;
//    }
//  }
  return 0;
}
