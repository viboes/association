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

#ifndef BOOST_ASSOCIATION_BIASSOC_HPP
#define BOOST_ASSOCIATION_BIASSOC_HPP

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <boost/bimap/unconstrained_set_of.hpp>

namespace boost {

  namespace association {
    template <class Left, class Right>
    struct relation_of
    {
      Left left_;
      Right right_;
    public:
      relation_of(Left const& left, Right const& right) : left_(left), right_(right) {}

    };
    template <class Left, class Right>
    relation_of<Left, Right> make_relation_of(Left const& left, Right const& right) {
      return relation_of<Left, Right>(left, right);
    }

    template <typename T>
    struct tagged_traits {
    };

    template <typename T, typename Tag>
    struct tagged_traits<bimaps::tagged<T,Tag> > {
        typedef T type;
        typedef Tag tag;
    };

    namespace detail {


      template <class T>
      struct translate
      {
        typedef T* type;
      };
      template <class T>
      struct translate<const T>
      {
        typedef const T* type;
      };

      template <class T, class KC>
      struct key_comparator
      {
        typedef typename tagged_traits<T>::type TT;
        typedef typename translate<TT>::type first_argument_type;
        typedef typename translate<TT>::type second_argument_type;
        typedef bool result_type;
        bool operator()(const first_argument_type& x, const first_argument_type& y) const
        {
          return KC()(*x,*y);
        }
      };
      template <class Rel, class KC>
      struct key_comparator_relation
      {

        //typedef typename translate<T>::type first_argument_type;
        //typedef typename translate<T>::type second_argument_type;
        typedef Rel first_argument_type;
        typedef Rel second_argument_type;
        typedef bool result_type;
        bool operator()(Rel x, Rel y) const
        {
          return KC()(
              make_relation_of(*(x.left), *(x.right)),
              make_relation_of(*(y.left), *(y.right)));
        }
      };
      template <class Rel, class H>
      struct hash_relation
      {

        typedef Rel first_argument_type;
        typedef std::size_t result_type;
        result_type operator()(first_argument_type x) const
        {
          return H(make_relation_of(*(x.left), *(x.right)));
        }
      };

      template <>
      struct translate< ::boost::mpl::na>
      {
        typedef ::boost::mpl::na type;
      };

      template <>
      struct translate< ::boost::bimaps::left_based>
      {
        typedef ::boost::bimaps::left_based type;
      };
      template <>
      struct translate< ::boost::bimaps::right_based>
      {
        typedef ::boost::bimaps::right_based type;
      };
      template <class KC>
      struct translate< ::boost::bimaps::set_of_relation<KC> >
      {
        typedef ::boost::bimaps::set_of_relation<
            //key_comparator_relation< ::boost::bimaps::_relation, KC>
            KC
        >  type;
      };
      template <class KC>
      struct translate< ::boost::bimaps::multiset_of_relation<KC> >
      {
        typedef ::boost::bimaps::multiset_of_relation<
            //key_comparator_relation< ::boost::bimaps::_relation, KC>
            KC
        >  type;
      };
      template <class H, class E>
      struct translate< ::boost::bimaps::unordered_set_of_relation<H, E> >
      {
        typedef ::boost::bimaps::unordered_set_of_relation<
            hash_relation< ::boost::bimaps::_relation, H>,
            key_comparator_relation< ::boost::bimaps::_relation, E> >  type;
      };
      template <class H, class E>
      struct translate< ::boost::bimaps::unordered_multiset_of_relation<H, E> >
      {
        typedef ::boost::bimaps::unordered_multiset_of_relation<
            hash_relation< ::boost::bimaps::_relation, H>,
            key_comparator_relation< ::boost::bimaps::_relation, E> >  type;
      };
      template <>
      struct translate< ::boost::bimaps::list_of_relation>
      {
        typedef ::boost::bimaps::list_of_relation type;
      };
      template <>
      struct translate< ::boost::bimaps::vector_of_relation>
      {
        typedef ::boost::bimaps::vector_of_relation type;
      };
      template <>
      struct translate< ::boost::bimaps::unconstrained_set_of_relation>
      {
        typedef ::boost::bimaps::unconstrained_set_of_relation type;
      };


      template <class T, class Tag>
      struct translate< ::boost::bimaps::tagged<T, Tag> >
      {
        typedef ::boost::bimaps::tagged<typename translate<T>::type, Tag> type;
      };

      template <class T, class KC>
      struct translate< ::boost::bimaps::set_of<T, KC> >
      {
        typedef ::boost::bimaps::set_of<typename translate<T>::type, key_comparator<T, KC> > type;
      };
      template <class T, class KC>
      struct translate< ::boost::bimaps::multiset_of<T, KC> >
      {
        typedef ::boost::bimaps::multiset_of<typename translate<T>::type, key_comparator<T, KC> > type;
      };

      template <class T, class H, class E>
      struct translate< ::boost::bimaps::unordered_set_of<T, H, E> >
      {
        typedef ::boost::bimaps::unordered_set_of<typename translate<T>::type, H, E> type;
      };
      template <class T, class H, class E>
      struct translate< ::boost::bimaps::unordered_multiset_of<T, H, E> >
      {
        typedef ::boost::bimaps::unordered_multiset_of<typename translate<T>::type, H, E> type;
      };

      template <class T>
      struct translate< ::boost::bimaps::list_of<T> >
      {
        typedef ::boost::bimaps::list_of<typename translate<T>::type> type;
      };
      template <class T>
      struct translate< ::boost::bimaps::vector_of<T> >
      {
        typedef ::boost::bimaps::vector_of<typename translate<T>::type> type;
      };
      template <class T>
      struct translate< ::boost::bimaps::unconstrained_set_of<T> >
      {
        typedef ::boost::bimaps::unconstrained_set_of<typename translate<T>::type> type;
      };

      template <class T>
      struct translate< ::boost::bimaps::with_info<T> >
      {
        typedef ::boost::bimaps::with_info<typename translate<T>::type> type;
      };

      template
      <
          class KeyTypeA, class KeyTypeB,
          class AP1 = ::boost::mpl::na,
          class AP2 = ::boost::mpl::na,
          class AP3 = ::boost::mpl::na
      >
      struct base_type
      {
        typedef bimaps::bimap<
            KeyTypeA,
            KeyTypeB,
            AP1,
            AP2,
            AP3
        > type;
//        typedef bimaps::bimap<
//            typename translate<KeyTypeA>::type,
//            typename translate<KeyTypeB>::type,
//            typename translate<AP1>::type,
//            typename translate<AP2>::type,
//            typename translate<AP3>::type
//        > type;
      };

    }

    /**
     *
    class A : public extrinsic<
        A,
        LeftCollectionType, RightCollectionType
        [ , SetTypeOfRelation  ]  // Default to left_based
        [ , with_info< Info >  ]  // Default to no info
        [ , Allocator          ]  // Default to std::allocator<>
    >
    {
    };
    */
    template
    <
        class Final,
        class KeyTypeA, class KeyTypeB,
        class AP1 = ::boost::mpl::na,
        class AP2 = ::boost::mpl::na,
        class AP3 = ::boost::mpl::na
    >    class extrinsic : public detail::base_type<KeyTypeA, KeyTypeB, AP1,AP2,AP3>::type
    {
      typedef typename detail::base_type<KeyTypeA, KeyTypeB, AP1,AP2,AP3>::type base_type;
      //typedef typename bimaps::bimap<KeyTypeA, KeyTypeB, AP1,AP2,AP3>::type dummy_type;
      static Final instance;
    protected:
      extrinsic() : base_type() {}
    public:
      typedef Final final_type;
      static Final& assoc()
      {
        return instance;
      }
    };
    template
    <
        class Final,
        class KeyTypeA, class KeyTypeB,
        class AP1,
        class AP2,
        class AP3
    >
    typename extrinsic<Final,KeyTypeA, KeyTypeB, AP1,AP2,AP3>::final_type extrinsic<Final,KeyTypeA, KeyTypeB, AP1,AP2,AP3>::instance;

  }
}

#endif
