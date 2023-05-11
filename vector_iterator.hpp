#include <iostream>

namespace ft {

template< class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& > 
struct const_iterator_class;

template< class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& > 
struct iterator_class
{
    typedef T               value_type;
    typedef Distance        difference_type;
    typedef Pointer         pointer;
    typedef Reference       reference;

    Pointer  _iterator; 

    iterator_class () : _iterator( NULL ) {}
    iterator_class (const const_iterator_class<T>& other) : _iterator( other._iterator ) {}
    iterator_class (Pointer arg) : _iterator(arg) {}
    iterator_class (const iterator_class< T* >& other) : _iterator( other._iterator ) {}
    ~iterator_class () {}
    iterator_class<T> operator=(const iterator_class<T>& other) {_iterator = other._iterator; return *this;}
    iterator_class<T> operator=(const const_iterator_class<T>& other) {_iterator = other._iterator; return *this;}

    difference_type operator-(const iterator_class<T>& other) {return this->_iterator - other._iterator;}

    iterator_class<T>& operator++() {this->_iterator++;
        return *this;}

    iterator_class<T>& operator--() {this->_iterator--;
        return *this;}

    iterator_class<T> operator++(int) {
        pointer ret = this->_iterator;
        this->_iterator++;
        return ret;}

    iterator_class<T> operator--(int) {
        pointer ret = this->_iterator;
        this->_iterator--;
        return ret;}

    bool operator==(const iterator_class<T>& other) const {return this->_iterator == other._iterator;}
    bool operator!=(const iterator_class<T>& other) const {return this->_iterator != other._iterator;}
    bool operator>(const iterator_class<T>& other) const {return (this->_iterator > other._iterator);};
    bool operator>=(const iterator_class<T>& other) const {return (this->_iterator >= other._iterator);};
    bool operator<(const iterator_class<T>& other) const {return (this->_iterator < other._iterator);};
    bool operator<=(const iterator_class<T>& other) const {return (this->_iterator <= other._iterator);};

    bool operator==(const const_iterator_class<T>& other) const {return this->_iterator == other._iterator;}
    bool operator!=(const const_iterator_class<T>& other) const {return this->_iterator != other._iterator;}
    bool operator>(const const_iterator_class<T>& other) const {return (this->_iterator > other._iterator);};
    bool operator>=(const const_iterator_class<T>& other) const {return (this->_iterator >= other._iterator);};
    bool operator<(const const_iterator_class<T>& other) const {return (this->_iterator < other._iterator);};
    bool operator<=(const const_iterator_class<T>& other) const {return (this->_iterator <= other._iterator);};

    iterator_class<T> operator+(difference_type n) const {return _iterator + n;}
    iterator_class<T> operator-(difference_type n) const {return _iterator - n;}

    iterator_class<T> operator+=(difference_type n) {
        this->_iterator += n;
        return *this;}

    iterator_class<T> operator-=(difference_type n) {
        this->_iterator -= n;
        return *this;}

    T& operator[]( difference_type n ) const {return _iterator[n];}
    T* operator->() {return &(*this->_iterator);}
    T& operator*() {return *_iterator;}

    Pointer adress() {return _iterator;}
};

template < class T >
iterator_class<T> operator+(int n, iterator_class<T>& iter) {
  return iter + n;
};

template< class T, class Distance, class Pointer, class Reference > 
struct const_iterator_class
{
    typedef T               value_type;
    typedef Distance        difference_type;
    typedef Pointer         pointer;
    typedef Reference       reference;

    Pointer  _iterator; 

    const_iterator_class () : _iterator( NULL ) {}
    const_iterator_class (const iterator_class<T> other) : _iterator( other._iterator) {}
    const_iterator_class (const Pointer arg) : _iterator(arg) {}
    const_iterator_class (const const_iterator_class< T* >& other) : _iterator( other._iterator ) {}  
    ~const_iterator_class () {}
    const_iterator_class<T> operator=(const const_iterator_class<T>& other) {_iterator = other._iterator; return *this;}
    const_iterator_class<T> operator=(const iterator_class<T>& other) {_iterator = other._iterator; return *this;}

    difference_type operator-(const const_iterator_class<T>& other) const { return this->_iterator - other._iterator;}

    const_iterator_class<T> operator++() {
        this->_iterator++;
        return *this;}

    const_iterator_class<T> operator--() {this->_iterator--;
        return *this;}

    const_iterator_class<T> operator++(int) {
        const_iterator_class<T> ret(this->_iterator);
        this->_iterator++;
        return ret;}

    const_iterator_class<T> operator--(int) {
        const_iterator_class<T> ret(this->_iterator);
        this->_iterator--;
        return ret;}

    bool operator==(const const_iterator_class<T>& other) const {return this->_iterator == other._iterator;}
    bool operator!=(const const_iterator_class<T>& other) const {return this->_iterator != other._iterator;}
    bool operator>(const const_iterator_class<T>& other) const {return (this->_iterator > other._iterator);};
    bool operator>=(const const_iterator_class<T>& other) const {return (this->_iterator >= other._iterator);};
    bool operator<(const const_iterator_class<T>& other) const {return (this->_iterator < other._iterator);};
    bool operator<=(const const_iterator_class<T>& other) const {return (this->_iterator <= other._iterator);};

    bool operator==(const iterator_class<T>& other) const {return this->_iterator == other._iterator;}
    bool operator!=(const iterator_class<T>& other) const {return this->_iterator != other._iterator;}
    bool operator>(const iterator_class<T>& other) const {return (this->_iterator > other._iterator);};
    bool operator>=(const iterator_class<T>& other) const {return (this->_iterator >= other._iterator);};
    bool operator<(const iterator_class<T>& other) const {return (this->_iterator < other._iterator);};
    bool operator<=(const iterator_class<T>& other) const {return (this->_iterator <= other._iterator);};

    const_iterator_class<T> operator+(difference_type n) const {return _iterator + n;}
    const_iterator_class<T> operator-(difference_type n) const {return _iterator - n;}

    const_iterator_class<T> operator+=(difference_type n) {
        this->_iterator += n;
        return *this;}

    const_iterator_class<T> operator-=(difference_type n) {
        this->_iterator -= n;
        return *this;}

    const T* operator->() const {return &(*this->_iterator);}

    const T operator*() const {return *_iterator;}
};

    template< class Iter >
    class const_reverse_iterator_vector;

    template< class Iter >
    class reverse_iterator_vector
    {
        public :
        

        typedef Iter                                                                        iterator_type;    
        typedef typename iterator_traits<Iter>::value_type                                  value_type;
        typedef typename iterator_traits<Iter>::difference_type                             difference_type;
        typedef typename iterator_traits<Iter>::reference                                   reference;
        typedef typename iterator_traits<Iter>::pointer                                     pointer;
        

        reverse_iterator_vector() : current()
        {
            return ;
        }

        explicit reverse_iterator_vector( iterator_type x )
        {
            current = x;
            return ;
        }

        template< class U > 
        reverse_iterator_vector( const reverse_iterator_vector<U>& other )
        {
            *this = other;
        }

        template< class U > 
        reverse_iterator_vector& operator=( const reverse_iterator_vector<U>& other )
        {
            this->current = other.base();
            return *this;
        }

        difference_type operator-(const reverse_iterator_vector<Iter>& other) {return this->base() - other.base();}


        value_type& operator*() const
        {
            iterator_type tmp(current);
            --tmp;
            return (*tmp);
        }

        value_type* operator->() const
        {
            iterator_type tmp(current);
            --tmp;
            return &(*tmp);
        }

        reference operator[]( difference_type n ) const
        {
            return base()[-n-1];
        }

        reverse_iterator_vector& operator++()
        {
            current--;
            return *this;
        }

        reverse_iterator_vector& operator--()
        {
            current++;
            return *this;
        }

        reverse_iterator_vector operator++(int)
        {
            reverse_iterator_vector ret(*this);
            current--;
            return ret;
        }

        reverse_iterator_vector operator--(int)
        {
            reverse_iterator_vector ret(*this);
            current++;
            return ret;
        }

        reverse_iterator_vector operator+( difference_type n ) const
        {
            reverse_iterator_vector ret(current - n);
            return ret;
        }

        reverse_iterator_vector operator-( difference_type n ) const
        {
            reverse_iterator_vector ret(current + n);
            return ret;
        }

        reverse_iterator_vector& operator+=( difference_type n )
        {
            current -= n;
			return *this;
        }

        reverse_iterator_vector& operator-=( difference_type n )
        {
            current += n;
			return *this;
        }

        template< class Iterator2 > 
        bool operator == ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator == ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() != rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() != rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        iterator_type base() const
        {
            return this->current;
        }

        Iter current;
    };

    




    template < class Iter >
    reverse_iterator_vector<Iter> operator+(int n, reverse_iterator_vector<Iter>& iter) {return iter + n;}

        template< class Iter >
        class const_reverse_iterator_vector
    {
        public :
        

        typedef Iter                                                                        iterator_type;    
        typedef typename iterator_traits<Iter>::value_type                                  value_type;
        typedef typename iterator_traits<Iter>::difference_type                             difference_type;
        typedef typename iterator_traits<Iter>::reference                                   reference;
        typedef typename iterator_traits<Iter>::pointer                                     pointer;
        

        const_reverse_iterator_vector() : current()
        {
            return ;
        }

        explicit const_reverse_iterator_vector ( const iterator_type x )
        {
            current = x;
            return ;
        }


        template< class U > 
        const_reverse_iterator_vector( const const_reverse_iterator_vector<U>& other )
        {
            *this = other;
        }

        template< class U, class V > 
        const_reverse_iterator_vector( const_iterator_map<U, V>& other )
        {
            current = other;
        }

        template< class U, class V > 
        const_reverse_iterator_vector( const Iter & other )
        {
            current = other;
        }

        template< class U > 
        const_reverse_iterator_vector( const reverse_iterator_vector<U>& other )
        {
            *this = other;
        }

        template< class U > 
        const_reverse_iterator_vector( const iterator_type& other )
        {
            *this = other;
        }

        template< class U > 
        const const_reverse_iterator_vector& operator=( const reverse_iterator_vector<U>& other )
        {
            this->current = other.base();
            return *this;
        }

        const value_type& operator*() const
        {
            iterator_type tmp(current);
            --tmp;
            return (*tmp);
        }

        const value_type* operator->() const
        {
            iterator_type tmp(current);
            --tmp;
            return &(*tmp);
        }

        

        const reference operator[]( difference_type n ) const
        {
            return base()[-n-1];
        }

        const const_reverse_iterator_vector& operator++()
        {
            current--;
            return *this;
        }

        const const_reverse_iterator_vector& operator--()
        {
            current++;
            return *this;
        }

        const const_reverse_iterator_vector operator++(int)
        {
            const_reverse_iterator_vector ret(*this);
            current--;
            return ret;
        }

        const const_reverse_iterator_vector operator--(int)
        {
            const_reverse_iterator_vector ret(*this);
            current++;
            return ret;
        }

        difference_type operator-(const const_reverse_iterator_vector& other) {return (this->current - other.base()) * - 1;}

        const_reverse_iterator_vector operator+( difference_type n ) const
        {
            const_reverse_iterator_vector ret(current - n);
            return ret;
        }

        const_reverse_iterator_vector operator-( difference_type n ) const
        {
            const_reverse_iterator_vector ret(current + n);
            return ret;
        }

        const_reverse_iterator_vector& operator+=( difference_type n )
        {
            current -= n;
			return *this;
        }

        const_reverse_iterator_vector& operator-=( difference_type n )
        {
            current += n;
			return *this;
        }

        template< class Iterator2 > 
        bool operator == ( const const_reverse_iterator_vector<Iterator2>& rhs ) const{return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator == ( const reverse_iterator_vector<Iterator2>& rhs ) const{return this->base() == rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() != rhs.base();}
        template< class Iterator2 > 
        bool operator != ( const reverse_iterator_vector<Iterator2>& rhs ) const{return this->base() != rhs.base();}
        
        template< class Iterator2 > 
        bool operator < ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const const_reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        template< class Iterator2 > 
        bool operator < ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() > rhs.base();}
        template< class Iterator2 > 
        bool operator <= ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() >= rhs.base();}
        template< class Iterator2 > 
        bool operator > ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() < rhs.base();}
        template< class Iterator2 >
        bool operator >= ( const reverse_iterator_vector<Iterator2>& rhs ) const {return this->base() <= rhs.base();}

        const iterator_type base() const
        {
            return this->current;
        }

        Iter current;
    };





}