/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:24:10 by rlanani           #+#    #+#             */
/*   Updated: 2022/10/27 15:45:00 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_HPP
#define VECTOR_HPP


#include <memory>
#include <stddef.h>
#include <iostream>
#include "utils.cpp"
#include "bidirectional_iterator.hpp"
#include "vector_iterator.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace ft
{
    template < class T, class Alloc=std::allocator<T> >
    class vector {

        public :

        /////MEMBER TYPE/////

        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;

        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

        typedef ft::iterator_class<T>                                       iterator;
        typedef ft::const_iterator_class<T>                                 const_iterator;
        typedef typename ft::reverse_iterator_vector <iterator>             reverse_iterator;
        typedef typename ft::const_reverse_iterator_vector <iterator>       const_reverse_iterator;

        typedef size_t                                              size_type;
        typedef int                                                 difference_type;

        /////ATTRIBUTS////ß

        size_type           _size_allocated;
        size_type           _number_elements;
        allocator_type      _my_allocator;
        T*                  _array;

        /////FONCTIONS MEMBRES/////

            /*CLASSE DE COPLIEN*/

                /*CONSTRUCTEUR*/

                explicit vector (const allocator_type& alloc = allocator_type()) : _size_allocated(0), _number_elements(0), _my_allocator (alloc), _array (NULL) {};

                explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size_allocated(n), _number_elements(n), _my_allocator (alloc), _array(_my_allocator.allocate ( n ))
                {
                    for (size_type i = 0; i < _number_elements ; i++)
                        _my_allocator.construct( _array + i , val );
                };

                template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false ) : _my_allocator (alloc)
                {
                    int ct2 = 0;

                    InputIterator tmp = first;

                    
                    while (first++ != last)
                        ct2++;

                    this->_size_allocated = ct2;
                    this->_number_elements = ct2;
                    this->_array = this->_my_allocator.allocate(ct2);

                    for (size_type i = 0; i < _number_elements ; i++)
                        _my_allocator.construct(this->_array + i, *tmp++);
                };

                vector (const vector& x) : _size_allocated(0), _number_elements(0),_array (NULL)
                {
                    int ct2 = x.end() - x.begin();

                    this->_size_allocated = ct2;
                    this->_number_elements = ct2;
                    this->_array = this->_my_allocator.allocate(ct2);

                    for (size_type i = 0; i < _number_elements ; i++)
                        _my_allocator.construct(this->_array + i, *(x.begin() + i));
                }


                /*DESTRUCTEUR*/
                ~vector()
                {       
                    this->clear();
                    _my_allocator.deallocate(_array, this->_size_allocated);
                };


                /*OVERLOAD OPERATEUR ASSIGNEMENT*/
                vector& operator= (const vector& x)
                {
                    if (this->_array != NULL)
                        this->clear();

                    this->assign(x.begin(), x.end());

                    return *this;
                }

            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
            {
                if (this->size())
                    clear();
                for ( ;first != last; first++)
                {
                    this->push_back(*first);
                }
            }

            void assign (size_type n, const value_type& val)
            {       
                if (this->size())
                    clear();
                _my_allocator.deallocate(_array, _size_allocated);
                _array = _my_allocator.allocate ( n );
                _number_elements = n;
                _size_allocated = n;
                for (iterator it = this->begin() ; it != this->end(); ++it)
                    _my_allocator.construct( it.adress() , val );
            }

            /*ITERATEUR*/

            iterator begin() {return _array;}
            const_iterator begin() const {return _array;}

            iterator end() {return (_array + _number_elements);}
            const_iterator end() const {return (_array + _number_elements);}
            
            //RBEGIN//
            reverse_iterator rbegin() { return reverse_iterator(iterator(this->end()));}
            const_reverse_iterator rbegin() const { return (this->end());}

            //REND//
            reverse_iterator rend() { return reverse_iterator(this->begin());}
            const_reverse_iterator rend() const { return (this->begin());}

            /*CAPACITE*/
            size_type size() const {return _number_elements;}
            size_type max_size() const {return _my_allocator.max_size();}
            size_type capacity() const {return _size_allocated;}
            bool empty() const {
                if (_number_elements == 0)
                    return true;
                return false;
            }

            void reserve (size_type n)
            {
                if (n < _size_allocated)
                    return ;
                if (n > max_size())
				        throw(std::length_error("vector::reserve"));
                T*            _array_replace = NULL;

                _array_replace = _my_allocator.allocate ( n );
                memset((void*) _array_replace, 0, sizeof(T) * n );

                for (size_type i = 0; i < n; i++)
                    if (i < this->size())
                        this->_my_allocator.construct(_array_replace + i, this->_array[i]);

                for (iterator it = this->begin() ; it != this->end(); ++it)
                        _my_allocator.destroy(it.adress());       
                _my_allocator.deallocate(_array, _size_allocated);




                _array = _array_replace;
                _size_allocated = n;



                return ;    
            }

            /*ELEMENT ACCESS*/
            reference operator[] (size_type n)
            {
                if (n < 0 || n >= _number_elements)
                    throw std::out_of_range ("OOR");
                return _array[n];
            }

            reference at (size_type n)  
            {
                if (n < 0 || n >= _number_elements)
                    throw std::out_of_range ("OOR");
                return _array[n];
            }

            const_reference at (size_type n) const
            {
                if (n < 0 || n >= _number_elements)
                    throw std::out_of_range ("OOR");
                return _array[n];
            }

            reference front()
            {
                return (_array[0]);
            }

            const_reference front() const
            {
                return (_array[0]);
            }

            reference back()
            {
                return (_array[_number_elements - 1]);
            }

            const_reference back() const
            {
                return (_array[_number_elements - 1]);
            }

            value_type* data() //const value_type* data() const noexcept;
            {
                return (_array);
            }



            /*MODIFIERS*/

            void clear ()
            {
                for (iterator it = this->begin() ; it != this->end(); ++it)
                    _my_allocator.destroy(it.adress());
                _number_elements = 0;
            }

            iterator insert (iterator position, const value_type& val)
            {

                int ct2 = std::distance(position.adress(), this->end().adress());

                if (position == this->end())
                {
                    this->push_back(val);
                    return (this->end().adress() - 1);
                }

                if (this->size() + 1 > this->capacity())
                    this->reserve(this->size() + 1);

                for (int i = 0; i != ct2; i++)
                {
                    if (i == 0)
                        _my_allocator.construct( this->_array + (this->_number_elements - i) , this->_array[this->_number_elements - (i + 1)]);
                    else
                        this->_array[this->_number_elements - i] = this->_array[this->_number_elements - (i + 1)];
                }
                    
                this->_array[this->_number_elements - ct2] = val;
                this->_number_elements++;
        
                iterator        ret(this->end() - (ct2 + 1));

                return ret;
            }

            void insert (iterator position, size_type n, const value_type& val )
            {

                //std::cout << "test 222222222222222 = " << std::endl;
                int ct2 = std::distance(position.adress(), this->end().adress());




                if (this->size() + n > this->capacity() * 2 && n > 0)
                {
                    this->reserve(this->capacity() + n);
                }
                else if (this->size() + n < this->capacity() * 2 && this->size() + n > this->capacity() && n > 0)
                {
                    this->reserve(this->size() * 2);
                }


                if ( this->size()+ n > this->capacity())
                    this->reserve(this->capacity() + n);

                
                for (; n ; n--)
                {
                    if (ct2 == 0)
                    {
                        this->push_back(val);
                        continue;
                    }

                    for (int i = 0; i != ct2; i++ )
                    {
                        if (i == 0)
                            _my_allocator.construct( this->_array + (this->_number_elements - i) , this->_array[this->_number_elements - (i + 1)]);
                        else
                            this->_array[this->_number_elements - i] = this->_array[this->_number_elements - (i + 1)];
                    }
                    this->_array[this->_number_elements - ct2] = val;
                    this->_number_elements++;
                }

                return;
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
            {    
                int ct2 = std::distance(position.adress(), this->end().adress());
                int ct3 = 0;
                InputIterator count1 = first;
                InputIterator count2 = last;

                if (first == last)
                    return;

                /*value_type      swaped_value;
                value_type      swaped_value2;*/

                while (count1 != count2)
                {
                    count1++;
                    ct3++;
                }

                
                    if (this->size() + ct3 > this->capacity() * 2 && ct3 > 0)
                    {
                        this->reserve(this->capacity() + ct3);
                    }
                    else if (this->size() + ct3 < this->capacity() * 2 && this->size() + ct3 > this->capacity() && ct3 > 0)
                    {
                        if (this->size() == 0)
                            this->reserve(1);
                        this->reserve(this->size() * 2);
                    }

                    if ( this->size() + ct3 > this->capacity())
                        this->reserve(this->capacity() + ct3);


                
                while (first != last)
                {
                    if (ct2 == 0)
                    {
                        this->push_back(*first);
                        first++;
                        continue;
                    }

                    for (int i = 0; i != ct2; i++ )
                    {
                        if (i == 0)
                            _my_allocator.construct( this->_array + (this->_number_elements - i) , this->_array[this->_number_elements - (i + 1)]);
                        else
                            this->_array[this->_number_elements - i] = this->_array[this->_number_elements - (i + 1)];
                    }
                    this->_array[this->_number_elements - ct2] = *first;
                    this->_number_elements++;

                    /*for (iterator   ship = begin(); ship != end(); ship++)
                    {
                        if (this->end() - ct2 == ship)
                        {
                            std::cout << "oui" << std::endl;
                            swaped_value = *ship;
                            *ship = *first;
                            ship++;
                        
                            while (ship != this->end())
                            {
                                swaped_value2 = *ship;
                                *ship = swaped_value;
                                swaped_value = swaped_value2;
                                ship++;
                            }
                            this->push_back(swaped_value);
                        }
                    }*/



                    first++;
                }
                return;
            }

            iterator erase (iterator position)
            {
                if (position == this->end())
                    return NULL;
                    
                T* _array_replace;
                int i = 0;
                
                _array_replace = _my_allocator.allocate(this->capacity());
                
                iterator        it_replace = _array_replace;

                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it != position)
                    {
                        _my_allocator.construct( it_replace.adress(), *it);
                        it_replace++;
                    }
                    else
                        i = std::distance(_array, it.adress());
                }

                for (iterator it = this->begin() ; it != this->end(); ++it)
                        _my_allocator.destroy(it.adress());
                _my_allocator.deallocate (_array, _size_allocated);
                
                _array = _array_replace;
                _number_elements--;

                return this->begin().adress() + i;
            }
            
            iterator erase (iterator first, iterator last)
            {
                int ct1 = std::distance(first.adress(), last.adress());
                int ct2 = std::distance(this->begin().adress(), first.adress());

                
                for (; ct1 ; --ct1)
                {
                    this->erase(this->begin() + ct2);
                }
                return this->begin() + ct2;
            }

            void push_back (const value_type& val)
            {
                if (size() + 1 <= capacity())
                {
                    _my_allocator.construct(_array + size(), val);
                    _number_elements++;
                    return ;
                }

                if (size() + 1 > capacity())
                {
                    reserve(capacity() * 2);

                    if (capacity() == 0)
                        reserve(1);

                    _my_allocator.construct(_array + size(), val);
                    _number_elements++;
                    return ;
                }
            }

            void pop_back ()
            {
                if (this->_number_elements)
                {
                    _my_allocator.destroy((--this->end()).adress());
                    this->_number_elements--;
                }
            }

            void resize (size_type n, value_type val = value_type())
            {
                if (n == 0) {
                    for (iterator it = this->begin() ; it != this->end(); ++it)
                        _my_allocator.destroy(it.adress());
                    this->_number_elements = 0;
                    return;
                }

                if (n < this->size())
                {
                    for (iterator it = --this->end(); this->size() != n; it--)
                    {
                        _my_allocator.destroy (it.adress());
                        this->_number_elements--;
                    }
                    return ;
                }

                if (n > this->size() && n <= this->capacity())
                {
                    while (this->size() != n)
                        this->push_back(val);
                    return ;
                }

                if (n > this->size() && n > this->capacity())
                {
                    if (this->capacity() * 2 < n)
                        this->reserve(n);
                    while (this->size() != n)
                        this->push_back(val);
                    return ;
                }
            }

            void swap (vector& x)
            {
                T* swap = this->_array;
                this->_array = x._array;
                x._array = swap;

                size_type swap2 = this->_size_allocated;
                this->_size_allocated = x._size_allocated;
                x._size_allocated = swap2;

                size_type swap3 = this->_number_elements;
                this->_number_elements = x._number_elements;
                x._number_elements = swap3;
            }
    };

    template < class T, class Alloc >
    bool operator==(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      if (lhs.size() != rhs.size()) {
        return false;
      }
      return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    };

    template < class T, class Alloc >
    bool operator!=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      return !(lhs == rhs);
    };

    template < class T, class Alloc >
    bool operator<(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template < class T, class Alloc >
    bool operator<=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      return (!(rhs < lhs));
    };

    template < class T, class Alloc >
    bool operator>(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      return (rhs < lhs);
    };

    template < class T, class Alloc >
    bool operator>=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs) 
    {
      return (!(lhs < rhs));
    };

    template < class T, class Alloc >
    void swap(vector< T, Alloc >& x, vector< T, Alloc >& y) 
    {
      x.swap(y);
    };
}


#endif
