#include <iostream>
#include <limits>
#include "pair.hpp"
#include "node.hpp"
#include "bidirectional_iterator.hpp"
#include <stdlib.h>

namespace ft {

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
            return ( pair<T1,T2>(x,y) );
    };

////////////////////////////////////////////////   MAP   ///////////////////////////////////////////////////////

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > > 
class map 
    {
        public :

        typedef Key                                                                     key_type;    
        typedef T                                                                       mapped_type;
        typedef pair<const Key, T>                                                      value_type;
        typedef std::size_t                                                             size_type;
        typedef std::ptrdiff_t                                                          difference_type;
        typedef Compare                                                                 key_compare;
        typedef Allocator                                                               allocator_type;
        typedef value_type&                                                             reference;
        typedef const value_type&                                                       const_reference;                                     
        typedef typename Allocator::pointer                                             pointer;
        typedef typename Allocator::const_pointer                                       const_pointer;
        typedef iterator_map<Key, T>                                                    iterator; 	                                        
        typedef const_iterator_map<Key, T> 	                                            const_iterator;
        typedef reverse_iterator<iterator>                                          reverse_iterator;
        typedef const_reverse_iterator<iterator>  	                                    const_reverse_iterator;
        
        typedef typename Allocator::template rebind<node<Key, T> >::other               node_allocator;
            
            class value_compare 
            {   
                friend class map;
        
                protected:

                Compare comp;
                value_compare (Compare c) : comp(c) {}  

                public:

                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                  return comp(x.first, y.first);
                }
                       
            };


        //CONSTRUCTOR//
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                my_compare = comp;
                my_allocator = alloc;
                root = NULL;

                typename Allocator::template rebind<node<Key, T> >::other test;

                super_root = my_node_allocator.allocate(1);
                my_node_allocator.construct(super_root, node<Key, T> ());

                size_map = 0;
            }


            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                my_compare = comp;
                my_allocator = alloc;
                root = NULL;

                typename Allocator::template rebind<node<Key, T> >::other test;

                super_root = my_node_allocator.allocate(1);
                my_node_allocator.construct(super_root, node<Key, T> ());

                size_map = 0;
                this->insert(first, last);
            }

            map (const map& x)
            {
                my_compare = x.my_compare;
                my_allocator = x.my_allocator;
                typename Allocator::template rebind<node<Key, T> >::other test;
                super_root = my_node_allocator.allocate(1);
                my_node_allocator.construct(super_root, node<Key, T> ());
                root = NULL;
                size_map = 0;
                *this = x;
            }

        //DESTRUCTOR//
            ~map (void) 
            {
                clear();
                my_node_allocator.destroy(this->super_root);
                this->my_node_allocator.deallocate(this->super_root, 1);
            };

        
        //OPERATOR=//
            map& operator=( const map& other )
            {
                clear();

                if (other.size() > 0)
			        this->insert(other.begin(), other.end());
                
                return *this;
            }

        //OPERATORS//
        bool operator==(const map& other) const
        {
            std::less<T> my_compare2;
            const_iterator b_t = begin();
            const_iterator b_o = other.begin();

            for (; b_t != end() && b_o != other.end(); b_t++, b_o++ )
            {
                if ((value_comp()(b_t.ret->element, b_o.ret->element) || value_comp()(b_o.ret->element, b_t.ret->element)))
                    return false;
                if ((my_compare2(b_t.ret->element.second, b_o.ret->element.second)) || my_compare2(b_o.ret->element.second, b_t.ret->element.second))
                    return false;
            }
            if (b_o != other.end() ||  b_t != end())
                return false;
            return true;
        }
        bool operator<(const map& other) const
        {
            std::less<T> my_compare2;
            const_iterator b_t = begin();
            const_iterator b_o = other.begin();

            for (; b_t != end() && b_o != other.end(); b_t++, b_o++ )
            {
                if ((value_comp()(b_t.ret->element, b_o.ret->element) || value_comp()(b_o.ret->element, b_t.ret->element)))
                {
                    if (value_comp()(b_t.ret->element, b_o.ret->element))
                        return true;
                    return false;
                }
                if ((my_compare2(b_t.ret->element.second, b_o.ret->element.second)) || my_compare2(b_o.ret->element.second, b_t.ret->element.second))
                {
                    if (my_compare2(b_t.ret->element.second, b_o.ret->element.second))
                        return true;
                    return false;
                }

            }
            if (b_t == end() && b_o != other.end())
                return true;

            if (b_t != end() && b_o == other.end())
                return false;

            return false;
        }

        bool operator<=(const map& other) const
        {
            if (*this < other || *this == other)
                return true;

            return false;
        }

        bool operator>(const map& other) const
        {
            std::less<T> my_compare2;
            const_iterator b_t = begin();
            const_iterator b_o = other.begin();

            for (; b_t != end() && b_o != other.end(); b_t++, b_o++ )
            {
                if ((value_comp()(b_t.ret->element, b_o.ret->element) || value_comp()(b_o.ret->element, b_t.ret->element)))
                {
                    if (value_comp()(b_o.ret->element, b_t.ret->element))
                        return true;
                    return false;
                }
                if ((my_compare2(b_t.ret->element.second, b_o.ret->element.second)) || my_compare2(b_o.ret->element.second, b_t.ret->element.second))
                {
                    if (my_compare2(b_o.ret->element.second, b_t.ret->element.second))
                        return true;
                    return false;
                }
            }
            if (b_t == end() && b_o != other.end())
                return false;

            if (b_t != end() && b_o == other.end())
                return true;

            return false;
        }

        bool operator>=(const map& other) const
        {
            if (*this > other || *this == other)
                return true;

            return false;
        }

        bool operator!=(const map& other) const
        {
            if (*this == other)
                return false;
            return true;
        }
        //GET_ALLOCATOR//

            allocator_type get_allocator() const
            {
                return my_allocator;
            }

        //**************************************ELEMENT ACCESS************************************//
        //AT//

        T& at( const Key& key )
        {
            return ((find (key))->second);
        } 	
        
        const T& at( const Key& key ) const
        {
            return ( (find(key))->second);
        }

        //OPERATOR []//

        T& operator[]( const Key& key )
        {
            return insert(ft::make_pair(key, T())).first->second;
        }

        //**************************************ITERATOR************************************//
        //BEGIN//

        iterator begin()
        { 
            if (size_map == 0)
                return super_root;

            node<Key, T>      *ship;
            ship = root;

            while (ship && ship->left)
                ship = ship->left;

            return ship;
        }

        const_iterator begin() const
        {
            if (size_map == 0)
                return super_root;

            node<Key, T>      *ship;
            ship = root;

            while (ship && ship->left)
                ship = ship->left;
            
            return ship;
        }

        //END//
        iterator end()
        {
            return super_root;
        }

        const_iterator end() const
        {
            return super_root;
        }

        //RBEGIN//
        reverse_iterator rbegin() {
            reverse_iterator ret(end());
            return ret;
        }

        const_reverse_iterator rbegin() const {
            return end(); }

        //REND//
        reverse_iterator rend()
        {
            reverse_iterator ret(begin());
            return ret;
        }

        const_reverse_iterator rend() const
        {return begin();}


        //**************************************CAPACITY************************************//
        //EMPTY//
        bool empty() const
        {
            if (size_map == 0)
                return true;

            return false;
        }

        //SIZE//
        size_type size() const
        {
            return size_map;
        }

        //MAX_SIZE//
        size_type max_size(void) const
		{
			return (std::numeric_limits<size_type>::max() / (sizeof(node<key_type, mapped_type>)));
		}

        //**************************************MODIFIERS************************************//
        //CLEAR//
        void clear()
        {
            if (this->size() > 0)
			    this->erase(this->begin(), this->end());
        }

        //INSERT//
        pair<iterator,bool> insert (const value_type& val)
        {
            if (size_map == 0)
            {
                node<Key, T>      *ret = my_node_allocator.allocate(1);
                my_node_allocator.construct(ret, node<Key, T> (val));
                size_map++;
                
                super_root->parent = NULL;
                super_root->left = ret;
                super_root->right = ret;
                ret->parent = super_root;
                ret->left = NULL;
                ret->right = NULL;
                root = ret;

                return (pair<iterator, bool> (root, true));
            }

            if (size_map > 0)
            {
                iterator find_pair = find (val.first);
                if (find (val.first).ret != super_root)
                    return (pair<iterator, bool> (find_pair.ret, false));
            }

            node<Key, T>      *ship = root;

            while (42)
            {
                if (value_comp()(val, (ship->element)))
                {
                    if (ship->left)
                    {
                        ship = ship->left;
                        continue;
                    }
                    if (!ship->left)
                        break;
                }
                if (!value_comp()(val,(ship->element)))
                {
                    if (ship->right)
                    {
                        ship = ship->right;
                        continue;
                    }
                    if (!ship->right)
                        break;
                }
            }

            node<Key, T>      *insertion = my_node_allocator.allocate(1);    
            my_node_allocator.construct(insertion, node<Key, T> (val));

            if (value_comp()(val, ship->element))
            {
                ship->left = insertion;
            }
            if (!value_comp()(val, ship->element))
            {
                ship->right = insertion;
            }
            insertion->parent = ship;
            size_map++;
            return (pair<iterator, bool> (insertion, true));
        }

        iterator insert (iterator position, const value_type& val)
        {
            position++;
            insert(val);
            return find(val.first);
        }

        template <class InputIterator>
	    void insert (InputIterator first, InputIterator last)
	    {
            if (first == last)
            {
                return;
            }
		    while (42)
		    {
		        insert(*first);
		        first++;
                if (first == last)
                    return;
		    }
	    };

        //ERASE//
        void erase( iterator pos )
        {
            size_map--;

            if ((!pos.ret->right) && (!pos.ret->left))
            {
                if (pos.ret == root)
                {
                    my_node_allocator.destroy(pos.ret);
                    my_node_allocator.deallocate(pos.ret, 1);
                    root = NULL;
                    return;
                }
                if (pos.ret->parent->right == pos.ret)
                {
                    pos.ret->parent->right = NULL;
                }
                if (pos.ret->parent->left == pos.ret)
                {
                    pos.ret->parent->left = NULL;
                }
                my_node_allocator.destroy(pos.ret);
                my_node_allocator.deallocate(pos.ret, 1);
                return;
            }

            if ((!pos.ret->right && pos.ret->left) || (pos.ret->right && !pos.ret->left))
            {

                if (pos.ret->parent->left == pos.ret && pos.ret->parent->right == pos.ret)
                {
                    if (pos.ret->right)
                    {
                        root = pos.ret->right;
                        pos.ret->parent->left = pos.ret->right;
                        pos.ret->parent->right = pos.ret->right;
                        pos.ret->right->parent = pos.ret->parent;
                    }
                    if (pos.ret->left)
                    {
                        root = pos.ret->left;
                        pos.ret->parent->left = pos.ret->left;
                        pos.ret->parent->right = pos.ret->left;
                        pos.ret->left->parent = pos.ret->parent;
                    }
                    my_node_allocator.destroy(pos.ret);
                    my_node_allocator.deallocate(pos.ret, 1);
                    return;
                }
                
                if (pos.ret->parent->right == pos.ret)
                {
                    if (pos.ret->right)
                    {
                        pos.ret->parent->right = pos.ret->right;
                        pos.ret->right->parent = pos.ret->parent;
                    }
                    if (pos.ret->left)
                    {
                        pos.ret->parent->right = pos.ret->left;
                        pos.ret->left->parent = pos.ret->parent;
                    }
                    my_node_allocator.destroy(pos.ret);
                    my_node_allocator.deallocate(pos.ret, 1);
                    return;
                }
                if (pos.ret->parent->left == pos.ret)
                {
                    if (pos.ret->right)
                    {
                        pos.ret->parent->left = pos.ret->right;
                        pos.ret->right->parent = pos.ret->parent;
                    }
                    if (pos.ret->left)
                    {
                        pos.ret->parent->left = pos.ret->left;
                        pos.ret->left->parent = pos.ret->parent;
                    }
                    my_node_allocator.destroy(pos.ret);
                    my_node_allocator.deallocate(pos.ret, 1);
                    return;
                }
            }


            if ((pos.ret->right && pos.ret->left))
            {

                node<Key, T>      *ship = pos.ret->right;

                while (ship->left)
                    ship = ship->left;


                if (ship->parent->right == ship && ship->parent != pos.ret && (pos.ret != root || size_map > 3))
                {
                    ship->parent->right = NULL;
                }
                if (ship->parent->left == ship && ship->parent != pos.ret && (pos.ret != root || size_map > 3))
                {
                    ship->parent->left = NULL;
                }

                if (pos.ret == root)
                    root = ship;
                
                ship->parent = pos.ret->parent;

                if (pos.ret->left != ship)
                {
                    ship->left = pos.ret->left;
                    pos.ret->left->parent = ship;

                }
                if (pos.ret->right != ship)
                {
                    ship->right = pos.ret->right;
                    pos.ret->right->parent = ship;
                }
                if (pos.ret->parent->right == pos.ret)
                    pos.ret->parent->right = ship;
                if (pos.ret->parent->left == pos.ret)
                    pos.ret->parent->left = ship;

                my_node_allocator.destroy(pos.ret);
                my_node_allocator.deallocate(pos.ret, 1);
                return;
            }
            return;
        }


        void erase( iterator first, iterator last )
        {
            iterator previous;

            while (first != last)
            {
                previous = first;
                first++;
                erase(previous);
            }
            return;
        }

        size_type erase( const Key& key )
        {
            iterator to_erase = find(key);

            if (to_erase.ret != super_root)
            {
                erase(find(key));
                return (1);
            }
            return (0);
        }

        void swap (map &x)
		{
            node<Key, T>     *tmp;
            size_type   size_tmp;

            if (x == *this)
                return ;

            tmp = x.root;
            x.root = root;
            root = tmp;

            tmp = x.super_root;
            x.super_root = super_root;
            super_root = tmp;
            
            size_tmp = x.size_map;
            x.size_map = size_map;
            size_map = size_tmp;
		}
            


        //************************************** LOOKUP ************************************//

        //COUNT//
        size_type count( const Key& key ) const
        {
            
            size_type count = 0;
            pair<Key, T>     compar(key, T());
            for (const_iterator it = begin(); it != end(); it++)
            {
                if (!value_comp()(it.ret->element, compar) && !value_comp()(compar, it.ret->element))
                {
                    count++;
                }
            }
            return count; 
        }
        //FIND//
        iterator find( const Key& key )
        {
            pair<Key, T>     compar(key, T());
            for (iterator it = begin(); it != end(); it++)
            {
                if (!value_comp()(it.ret->element, compar) && !value_comp()(compar, it.ret->element))
                {
                    return it;
                }
            }
            return super_root; 
        }
        const_iterator find( const Key& key ) const
        {
            pair<Key, T>     compar(key, T());
            for (const_iterator it = begin(); it != end(); it++)
            {
                if (!value_comp()(it.ret->element, compar) && !value_comp()(compar, it.ret->element))
                {
                    return it;
                }
            }
            return super_root; 
        }
        //EQUAL RANGE//
        pair<iterator, iterator> equal_range (const key_type& k)
		{ 
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); 
        }
        pair<const_iterator, const_iterator> equal_range (const key_type& k) const
		{ 
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); 
        }
    
        //LOWER_BOUND//
        iterator lower_bound( const Key& key )
        {
            pair<Key, T>     compar(key, T());
            for (iterator it = begin(); it != end(); it++)
                if (value_comp()(compar, it.ret->element) || (!value_comp()(it.ret->element, compar) && !value_comp()(compar, it.ret->element)))
                {
                    return it;
                }
            return super_root; 
        }
        const_iterator lower_bound( const Key& key ) const
        {
            pair<Key, T>     compar(key, T());
            for (const_iterator it = begin(); it != end(); it++)
                if (!value_comp()(it.ret->element, compar) || (!value_comp()(it.ret->element, compar) && !value_comp()(compar, it.ret->element)))
                    return it;
            return super_root; 
        }

        //UPPER_BOUND//
        iterator upper_bound( const Key& key )
        {
            pair<Key, T>     compar(key, T());
            for (iterator it = begin(); it != end(); it++)
                if ((!value_comp()(it.ret->element, compar) && value_comp()(compar, it.ret->element)))
                {
                    return it;
                }
            return super_root; 
        }
        const_iterator upper_bound( const Key& key ) const
        {
            pair<Key, T>     compar(key, T());
            for (const_iterator it = begin(); it != end(); it++)
            {
                if ((!value_comp()(it.ret->element, compar) && value_comp()(compar, it.ret->element)))
                {
                    return it;
                }
            }
            return super_root;
        }

        //************************************** OBSERVERS ************************************//
        //KEY COMP//
        key_compare key_comp() const
        {
            return my_compare;
        }
        //VALUE COMP//
        value_compare value_comp() const
        {
            return value_compare (my_compare);
        }

    allocator_type                      my_allocator;
    Compare                             my_compare;
    node<Key, T>                        *root;
    node<Key, T>                        *super_root;
    size_type                           size_map;
    node_allocator                      my_node_allocator;
};

    template< class Key, class T>
    void swap (map<Key, T> &rhs, map<Key,T> &lhs)
	{
        node<Key, T>     *tmp;
        size_t   size_tmp;
        
        if (lhs == rhs)
            return ;
        
        tmp = lhs.root;
        lhs.root = rhs.root;
        rhs.root = tmp;

        tmp = lhs.super_root;
        lhs.super_root = rhs.super_root;
        rhs.super_root = tmp;
        
        size_tmp = lhs.size_map;
        lhs.size_map = rhs.size_map;
        rhs.size_map = size_tmp;
	}


    
}