
#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"

template < class T1, class T2 >    
    struct node 
    {
        public:

        node () : right(NULL), left(NULL), parent(NULL)
        {
           
        }

        ///CONSTRUCTEUR PARAMETRE///
        template<class U, class V> 
        node ( ft::pair<U,V>& pr) : element(pr), right (0), left(0), parent(0)
        {
            
        }

        template<class U, class V> 
        node ( const ft::pair<U,V>& val) :element(val), right (0), left(0), parent(0)
        {
            
        }
        
        ///CONSTRUCTEUR RECOPIE///
        template<class U, class V> 
        node ( const node<U,V>& nd)
        {
            *this = nd;
        }

        template<class U, class V>
        node<U,V> operator= ( const node<U,V>& nd)
        {
            *element = nd.element;
            *right = nd.right;
            *left = nd.left;
            *parent = nd.parent;
            return *this;
        }

        ///DESTRUCTEUR///
        ~node (void) 
        {
            
        }

        ft::pair<const T1, T2>                  element;
        node<T1, T2>                            *right;
        node<T1, T2>                            *left;
        node<T1, T2>                            *parent;
        };
#endif

