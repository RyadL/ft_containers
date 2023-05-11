#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include "node.hpp"
#include <iostream>
#include <vector>
   
        
namespace ft {

    template < class Key, class T, class Compare = std::less<Key> ,  class Parithmetic = std::ptrdiff_t>
    class const_iterator_map;

    template<typename _Iterator>
    struct iterator_traits
    {
        typedef typename _Iterator::value_type              value_type;
        typedef typename _Iterator::difference_type         difference_type;
        typedef typename _Iterator::pointer                 pointer;
        typedef typename _Iterator::reference               reference;
    };

    template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
        typedef _Tp                                         value_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef _Tp*                                        pointer;
        typedef _Tp&                                        reference;
    };
    template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
        typedef _Tp                                         value_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef const _Tp*                                  pointer;
        typedef const _Tp&                                  reference;
    };
    
    template < class Key, class T, class Compare = std::less<Key> ,  class Parithmetic = std::ptrdiff_t>
    class iterator_map
    {

        public :

        typedef Parithmetic                                         difference_type;
        typedef ft::pair<const Key, T>                              value_type;
        typedef value_type&                                         reference;
        typedef value_type*                                         pointer;
        typedef Compare                                             key_compare;

            class value_compare 
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>

                friend class iterator_map;
                protected:

                Compare comp;
                value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

                public:

                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                  return comp(x.first, y.first);
                }       
            };

        
        //defaut-constrcutible
        iterator_map () : ret(0)
        {
        }
        
        // default-constructible
        template<class U, class V> 
        iterator_map (node<U,V>& nd )
        {
            ret = &nd;
        }

        // default-constructible
        template<class U, class V> 
        iterator_map ( node<U,V> *nd)
        {
            ret = nd;
        }

        // copy-constructr
        template<class U, class V>
        iterator_map (const iterator_map<U, V> &it)
        {
            *this = it;
        }

        // destructor
        ~iterator_map ()
        {
        }

        iterator_map<Key, T> operator=(iterator_map<Key, T> it) 
        {
            ret = it.ret;
            return *this;
        }

        iterator_map<Key, T> operator=(const_iterator_map<Key, T> it) 
        {
            ret = it.ret;
            return *this;
        }

        bool operator==(iterator_map<Key, T> it) const
        {
            if ((this->ret) == (it.ret))
                return true;
            return false;
        }

        bool operator!=(iterator_map<Key, T> it) const
        {
            if (*this == it)
                return false;

            return true;
        }


        iterator_map<Key, T>& operator++( )
        {
            node<Key, T>      *ship;
            ship = this->ret;

            if (ship->right)
            {
                ship = ship->right;
                while (ship->left)
                    ship = ship->left;
                this->ret = ship;
                return (*this);
            }            

            node<Key, T>      *ship_follow = ship;

            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->right && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*this);
        }


        iterator_map<Key, T> operator++(int)
        {
            node<Key, T>      *ship(this->ret);
            node<Key, T>      *ship2(this->ret);

            if (ship->right)
            {
                ship = ship->right;
                while (ship->left)
                    ship = ship->left;
                this->ret = ship;
                return (*ship2);
            }            

            node<Key, T>      *ship_follow = ship;

            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->right && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*ship2);
        }

        iterator_map<Key, T> operator--( int )
        {
            node<Key, T>      *ship;
            node<Key, T>      *ship2(this->ret);
            ship = this->ret;

            if (ship->left)
            {
                ship = ship->left;
                while (ship->right)
                    ship = ship->right;
                this->ret = ship;
                return (*ship2);
            }            

            node<Key, T>      *ship_follow = ship;
            
            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->left && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*ship2);
        }


        iterator_map<Key, T>& operator--()
        {
            node<Key, T>      *ship;
            ship = this->ret;

            if (ship->left)
            {
                ship = ship->left;
                while (ship->right)
                    ship = ship->right;
                this->ret = ship;
                return (*this);
            }            

            node<Key, T>      *ship_follow = ship;
            
            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->left && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*this);
        }


        
        ft::pair<const Key, T>* operator->() const
        {
            return &ret->element;
        }

        ft::pair<const Key, T> operator*() const
        {
            return (*ret).element;
        }

        key_compare key_comp() const
        {
            return my_compare;
        }

        value_compare value_comp() const
        {
            return value_compare (my_compare);
        }

        node< Key, T>    *ret;
        Compare          my_compare;
    };

    template < class Key, class T, class Compare ,  class Parithmetic>
    class const_iterator_map
    {

        public :

        typedef Parithmetic                                         difference_type;
        typedef ft::pair<const Key, T>                              value_type;
        typedef value_type&                                         reference;
        typedef value_type*                                         pointer;
        typedef Compare                                             key_compare;

            class value_compare 
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>

                friend class const_iterator_map;
                protected:

                Compare comp;
                value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

                public:

                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                  return comp(x.first, y.first);
                }       
            };

        
        //defaut-constrcutible
        const_iterator_map () : ret(NULL)
        {
        }
        
        // default-constructible
        template<class U, class V> 
        const_iterator_map ( node<U,V>& nd)
        {
            ret = &nd;
        }

        template<class U, class V> 
        const_iterator_map ( iterator_map <U,V> it)
        {
            ret = it.ret;
        }

        template<class U, class V> 
        const_iterator_map ( node<U,V> *nd)
        {
            ret = nd;
        }

        // copy-constructr
        template<class U, class V>
        const_iterator_map (const const_iterator_map<U, V> &it)
        {
            *this = it;
        }

        // destructor
        ~const_iterator_map ()
        {
        }

        const const_iterator_map<Key, T> operator=(const_iterator_map<Key, T> it) 
        {
            ret = it.ret;
            return *this;
        }

        bool operator==(const_iterator_map<Key, T> it) 
        {

            if ((this->ret) == (it.ret))
                return true;
            return false;
        }

        bool operator!=(const_iterator_map<Key, T> it) 
        {
            if (*this == it)
                return false;

            return true;
        }


        const const_iterator_map<Key, T>& operator++( )
        {
            node<Key, T>      *ship;
            ship = this->ret;

            if (ship->right)
            {
                ship = ship->right;
                while (ship->left)
                    ship = ship->left;
                this->ret = ship;
                return (*this);
            }            

            node<Key, T>      *ship_follow = ship;

            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->right && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*this);
        }


        const const_iterator_map<Key, T> operator++(int)
        {
            node<Key, T>      *ship;
            node<Key, T>      *ship2(this->ret);
            ship = this->ret;

            if (ship->right)
            {
                ship = ship->right;
                while (ship->left)
                    ship = ship->left;
                this->ret = ship;
                return (*ship2);
            }            

            node<Key, T>      *ship_follow = ship;

            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->right && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*ship2);
        }

        const const_iterator_map<Key, T> operator--( int )
        {
            node<Key, T>      *ship;
            node<Key, T>      *ship2(this->ret);
            ship = this->ret;

            if (ship->left)
            {
                ship = ship->left;
                while (ship->right)
                    ship = ship->right;
                this->ret = ship;
                return (*ship2);
            }            

            node<Key, T>      *ship_follow = ship;
            
            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->left && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*ship2);
        }


        const const_iterator_map<Key, T>& operator--()
        {
            node<Key, T>      *ship;
            ship = this->ret;

            if (ship->left)
            {
                ship = ship->left;
                while (ship->right)
                    ship = ship->right;
                this->ret = ship;
                return (*this);
            }            

            node<Key, T>      *ship_follow = ship;
            
            ship = ship->parent;
            while (ship != NULL && ship_follow == ship->left && ship->parent) 
            {
                ship_follow = ship;
                ship = ship->parent;
            }
            this->ret = ship;
            return (*this);
        }
        
        const ft::pair<const Key, T>*  operator->() const
        {
            if (ret)
            {
                return &(ret->element);
            }
            return NULL;
        }

        const ft::pair<const Key, T> operator*() const
        {
            return (*ret).element;
        }

        key_compare key_comp() const
        {
            return my_compare;
        }

        value_compare value_comp() const
        {
            return value_compare (my_compare);
        }

        node< Key, T>    *ret;
        Compare          my_compare;
    };

    template< class Iter >
    class const_reverse_iterator;


    template< class Iter >
    class reverse_iterator
    {
        public :
        

        typedef Iter                                                                        iterator_type;    
        typedef typename iterator_traits<Iter>::value_type                                  value_type;
        typedef typename iterator_traits<Iter>::difference_type                             difference_type;
        typedef typename iterator_traits<Iter>::reference                                   reference;
        typedef typename iterator_traits<Iter>::pointer                                     pointer;
        

        reverse_iterator() : current()
        {
            return ;
        }

        explicit reverse_iterator( iterator_type x )
        {
            current = x;
            return ;
        }

        template< class U > 
        reverse_iterator( const reverse_iterator<U>& other )
        {
            *this = other;
        }

        template< class U > 
        reverse_iterator& operator=( const reverse_iterator<U>& other )
        {
            this->current = other.base();
            return *this;
        }


        

        value_type& operator*() const
        {
            Iter retour = --this->base();
            return (retour.ret->element);
        }

        value_type* operator->() const
        {
            return &(operator*());
        }

        

        reference operator[]( difference_type n ) const
        {
            return base()[-n-1];
        }

        reverse_iterator& operator++()
        {
            current--;
            return *this;
        }

        reverse_iterator& operator--()
        {
            current++;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator ret(*this);
            current--;
            return ret;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator ret(*this);
            current++;
            return ret;
        }

        reverse_iterator operator+( difference_type n ) const
        {
            reverse_iterator ret(current - n);
            return ret;
        }

        reverse_iterator operator-( difference_type n ) const
        {
            reverse_iterator ret(current + n);
            return ret;
        }

        reverse_iterator& operator+=( difference_type n )
        {
            current -= n;
			return *this;
        }

        reverse_iterator& operator-=( difference_type n )
        {
            current += n;
			return *this;
        }

        template< class Iterator2 > 
        bool operator == ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator == ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() != rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() != rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        iterator_type base() const
        {
            return this->current;
        }

        Iter current;
    };

    template < class Iter >
    reverse_iterator<Iter> operator+(int n, reverse_iterator<Iter>& iter) {return iter + n;}

    template< class Iter >
    class const_reverse_iterator
    {
        public :
        

        typedef Iter                                                                        iterator_type;    
        typedef typename iterator_traits<Iter>::value_type                                  value_type;
        typedef typename iterator_traits<Iter>::difference_type                             difference_type;
        typedef typename iterator_traits<Iter>::reference                                   reference;
        typedef typename iterator_traits<Iter>::pointer                                     pointer;
        

        const_reverse_iterator() : current()
        {
            return ;
        }

        explicit const_reverse_iterator ( const iterator_type x )
        {
            current = x;
            return ;
        }


        template< class U > 
        const_reverse_iterator( const const_reverse_iterator<U>& other )
        {
            *this = other;
        }

        template< class U, class V > 
        const_reverse_iterator( const_iterator_map<U, V>& other )
        {
            current = other;
        }

        template< class U, class V > 
        const_reverse_iterator( const Iter & other )
        {
            current = other;
        }

        template< class U > 
        const_reverse_iterator( const reverse_iterator<U>& other )
        {
            *this = other;
        }

        template< class U > 
        const_reverse_iterator( const iterator_type& other )
        {
            *this = other;
        }

        template< class U > 
        const const_reverse_iterator& operator=( const reverse_iterator<U>& other )
        {
            this->current = other.base();
            return *this;
        }

        const value_type& operator*() const
        {
            Iter retour = this->base();
            retour--;
            return (retour.ret->element);
        }

        const value_type* operator->() const
        {
            return &(operator*());
        }

        const reference operator[]( difference_type n ) const
        {
            return base()[-n-1];
        }

        const const_reverse_iterator& operator++()
        {
            current--;
            return *this;
        }

        const const_reverse_iterator& operator--()
        {
            current++;
            return *this;
        }

        const const_reverse_iterator operator++(int)
        {
            const_reverse_iterator ret(*this);
            current--;
            return ret;
        }

        const const_reverse_iterator operator--(int)
        {
            const_reverse_iterator ret(*this);
            current++;
            return ret;
        }

        difference_type operator-(const const_reverse_iterator& other) {return (this->current - other.base()) * - 1;}

        const_reverse_iterator operator+( difference_type n ) const
        {
            const_reverse_iterator ret(current - n);
            return ret;
        }

        const_reverse_iterator operator-( difference_type n ) const
        {
            const_reverse_iterator ret(current + n);
            return ret;
        }

        const_reverse_iterator& operator+=( difference_type n )
        {
            current -= n;
			return *this;
        }

        const_reverse_iterator& operator-=( difference_type n )
        {
            current += n;
			return *this;
        }

        template< class Iterator2 > 
        bool operator == ( const const_reverse_iterator<Iterator2>& rhs ) const{return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator == ( const reverse_iterator<Iterator2>& rhs ) const{return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() != rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const reverse_iterator<Iterator2>& rhs ) const{return this->base() != rhs.base();}
        
        template< class Iterator2 > 
        bool operator < ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const const_reverse_iterator<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const reverse_iterator<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        const iterator_type base() const
        {
            return this->current;
        }

        Iter current;
    };
}
    

#endif