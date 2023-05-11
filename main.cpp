#include <vector>
#include <map>
#include <stack>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include <iostream>
#include <utility>
#include <sys/time.h>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;


int main ()
{
    /*struct timeval tp0;
    gettimeofday(&tp0, NULL);
    long int ms0 = tp0.tv_usec;*/



    //////////////////////////////////////////////    VECTOR     ///////////////////////////////////////////////

    // CONSTRUCTOR + BASIC ELEMENT
    {

        vector<int> vec;
        vec.insert(vec.begin(), 15, 68);

        vector<int> vec2(vec);

        vector<int> vec3(42, 98);
        std::cout << "vec contains:" << std::endl;
        for (vector<int>::iterator it = vec.begin() ; it != vec.end(); ++it)
            std::cout << ' ' << *it << std::endl;

        std::cout << "vec2 contains:" << std::endl;
        for (vector<int>::iterator it = vec2.begin() ; it != vec2.end(); ++it)
            std::cout << ' ' << *it << std::endl;

        std::cout << "vec3 contains:" << std::endl;
        for (vector<int>::iterator it = vec3.begin() ; it != vec3.end(); ++it)
            std::cout << ' ' << *it << std::endl;




        vector<int> myvector;
        for (int i=1; i <= 10; i++) 
            myvector.push_back(i * 3);
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        myvector.insert(myvector.begin()+ 2, 3, 888);
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        vector<int> myvector2 (myvector);
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector2.begin() ; it != myvector2.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        vector<int> myvector3 (myvector);
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector3.begin() ; it != myvector3.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        myvector3.pop_back();
        myvector3.pop_back();
        myvector3.pop_back();
        myvector3.pop_back();
        myvector3.pop_back();
        myvector3.pop_back();
        myvector3.pop_back();
    
        myvector2 = myvector3;
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector2.begin() ; it != myvector2.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector3.begin() ; it != myvector3.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        myvector.assign(myvector3.begin(), myvector3.end());
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        myvector.assign(8, 15);
    
        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        std::cout << "Capacity = " << myvector.capacity() << " Size = " << myvector.size() <<std::endl;
    }

    //ITERATOR
    {   
        vector<int> myvector;
        myvector.push_back (50);
        myvector.push_back (156);
        myvector.push_back (325);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (23);
        myvector.push_back (38);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (5);
        myvector.push_back (8);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        
        while (!myvector.empty())
        {
          myvector.pop_back();
        }

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
          std::cout << ' ' << myvector[i];
        std::cout << '\n';

        for (vector<int>::size_type i=1; i<10; i++) 
            myvector.push_back( i * 3);

        myvector.resize(4);
        myvector.resize(7, 59);
        myvector.resize(14, 78);

        vector<int> myvector2;
        for (vector<int>::size_type i=1; i<14; i++) 
            myvector2.push_back( i * 4);

        std::cout << "myvector contains:";
        for (vector<int>::size_type i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        myvector.swap(myvector2);

        std::cout << "myvector contains:";
        for (vector<int>::size_type i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        myvector.swap(myvector2);

        std::cout << "myvector contains:";
        for (vector<int>::size_type i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        std::cout << "size = " << myvector.size() << std::endl;
        std::cout << "size2 = " << myvector2.size() << std::endl;

        std::cout << "cap = " << myvector.capacity() << std::endl;
        std::cout << "cap2 = " << myvector2.capacity() << std::endl;
    }

    //REVERSE ITERATOR
    {   
        vector<int> myvector;
        myvector.push_back (50);
        myvector.push_back (156);
        myvector.push_back (325);

        
        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;

        myvector.clear();
        myvector.push_back (23);
        myvector.push_back (38);

        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;

        myvector.clear();
        myvector.push_back (5);
        myvector.push_back (8);

        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;
        
        while (!myvector.empty())
        {
          myvector.pop_back();
        }

        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;

        for (vector<int>::size_type i=1; i<10; i++) 
            myvector.push_back( i * 3);

        myvector.resize(4);
        myvector.resize(7, 59);
        myvector.resize(14, 78);

        vector<int> myvector2;
        for (vector<int>::size_type i=1; i<14; i++) 
            myvector2.push_back( i * 4);

        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        myvector.swap(myvector2);

        std::cout << "myvector contains:";
        for (vector<int>::reverse_iterator it = myvector.rbegin() ; it != myvector.rend(); ++it)
            std::cout << ' ' << *it << std::endl;

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        myvector.swap(myvector2);

        std::cout << "myvector contains:";
        for (vector<int>::size_type i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<myvector2.size();i++)
            std::cout << ' ' << myvector2[i];
        std::cout << '\n';

        std::cout << "size = " << myvector.size() << std::endl;
        std::cout << "size2 = " << myvector2.size() << std::endl;

        std::cout << "cap = " << myvector.capacity() << std::endl;
        std::cout << "cap2 = " << myvector2.capacity() << std::endl;
    }

    //SWAP
    {
	    vector<int> test;
	    for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	    vector<int> test_copy(test);
	    for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	    
	    std::cout << "myvector contains:";
        for (vector<int>::size_type i=0;i<test.size();i++)
            std::cout << ' ' << test[i];
        std::cout << '\n';

        std::cout << "myvector2 contains:";
        for (vector<int>::size_type i=0;i<test_copy.size();i++)
            std::cout << ' ' << test_copy[i];
        std::cout << '\n';
    }


    //////////////////////////////////////////////    MAP     ///////////////////////////////////////////////

    //CONSTRUCTOR

    map<int, const char*> mymap;

    mymap.insert(make_pair<int, const char*> (1, "Bonjour"));
    mymap.insert(make_pair<int, const char*> (2, "je"));
    mymap.insert(make_pair<int, const char*> (3, "suis"));
    mymap.insert(make_pair<int, const char*> (4, "un"));
    mymap.insert(make_pair<int, const char*> (5, "test"));
    mymap.insert(make_pair<int, const char*> (6, "de"));
    mymap.insert(make_pair<int, const char*> (7, "mon"));
    mymap.insert(make_pair<int, const char*> (8, "container"));
    mymap.insert(make_pair<int, const char*> (9, "map"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;


    map<int, const char*> mymap2 (mymap);
    std::cout << "mymap2 contains:";
    for (map<int, const char*>::iterator it = mymap2.begin(); it != mymap2.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

    map<int, const char*> mymap3;

    mymap2.swap(mymap3);

    std::cout << "mymap2 contains:";
    for (map<int, const char*>::iterator it = mymap2.begin(); it != mymap2.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

    std::cout << "mymap3 contains:";
    for (map<int, const char*>::iterator it = mymap3.begin(); it != mymap3.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;



    map<int, const char*>::iterator mit;
	map<int, const char*>::iterator it;
	
	it = mymap.lower_bound(3);
	
    std::cout << std::endl;
	std::cout << "mymap.lower_bound(\"3\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	
    it = mymap.lower_bound(5);
	
	std::cout << "mymap.lower_bound(\"5\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;

    it = mymap.lower_bound(4);
	
	std::cout << "mymap.lower_bound(\"4\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;

    it = mymap.lower_bound(1);
	
	std::cout << "mymap.lower_bound(\"1\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;

    it = mymap.lower_bound(8);
	
	std::cout << "mymap.lower_bound(\"8\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	
	std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.erase(6);

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.erase(7);

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	
	mymap.clear();

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.clear();

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap[3] = "poire";

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.insert(make_pair<int, const char*> (19, "encore"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.insert(make_pair<int, const char*> (17, "un"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.insert(make_pair<int, const char*> (16, "autre"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.insert(make_pair<int, const char*> (45, "test"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap.insert(make_pair<int, const char*> (98, "wafegg"));

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;

	mymap[45] = "essaie";

    std::cout << "mymap contains:";
    for (map<int, const char*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << ' ' << it->second;
    std::cout << std::endl;


    //////////////////////////////////////////////    STACK     ///////////////////////////////////////////////

    //CONSTRUCTOR


    stack<const char *> mystack;

	std::cout << "mystack.empty(): " << mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
    
	mystack.push("s");
	std::cout << "mystack.push(42)" << std::endl;
	std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	mystack.push("t");
	std::cout << "mystack.push(2)" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	mystack.pop();
	std::cout << "mystack.pop()" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << std::endl;

	stack<const char*, ft::vector<const char *> > mystack2;

	std::cout << std::endl;

	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	mystack2.push("s");

	std::cout << "mystack2.push(42)" << std::endl;
	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	mystack2.push("t");

	std::cout << "mystack2.push(2)" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	mystack2.pop();
	std::cout << "mystack2.pop()" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << std::endl;

	stack<const char *>	cpystack = mystack;
	std::cout << std::endl;

	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
	cpystack.push("a");
	std::cout << "cpystack.push(7)" << std::endl;
	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;


    /*struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_usec;
        

    std::cout << ms - ms0 << std::endl;*/
    
        


  return 0;
}