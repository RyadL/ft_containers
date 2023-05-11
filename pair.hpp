#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template < class T1, class T2 >
    struct pair 
    {

        public :

        typedef T1                  first_type;
        typedef T2                  second_type;

        /////FONCTIONS MEMBRES/////

            /*CLASSE DE COPLIEN*/

                /*CONSTRUCTEUR*/

                pair(void) : first(first_type()), second(second_type())
                {   
                    return ;
                };

                template<class U, class V> 
                pair (const pair<U,V>& pr) : first( pr.first ), second(pr.second)
                {
                    return ;
                };

                pair (const first_type& a, const second_type& b) : first(a), second(b)
                {                   
                    return ;
                };


                ~pair (void) 
                {

                };

                /*OPERATEUR DÁSSIGNEMENT*/
                pair& operator= ( pair& pr)
                {
                    first = pr.first;
                    second = pr.second;
                    return *this;
                }

                pair operator= ( pair pr)
                {
                    first = pr.first;
                    second = pr.second;
                    return *this;
                }

            
                /*OVERLOAD DÁSSIGNEMENT*/
                bool operator== ( const pair<T1,T2>& rhs)
                { return first==rhs.first && second==rhs.second; }

                bool operator!= ( const pair<T1,T2>& rhs)
                { return !(*this==rhs); }

                bool operator<  ( const pair<T1,T2>& rhs )
                { return first<rhs.first || (!(rhs.first<first) && second<rhs.second); }

                bool operator<= ( const pair<T1,T2>& rhs)
                { return !(rhs<*this); }

                bool operator>  ( const pair<T1,T2>& rhs)
                { return rhs<*this; }

                bool operator>= (const pair<T1,T2>& rhs)
                { return !(*this<rhs); }

            first_type                  first;
            second_type                 second;
        };

}

#endif