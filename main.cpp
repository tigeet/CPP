#include <iostream>
#include <algorithm>
using namespace std;
#include <iterator>
#include <cstddef>



template<typename Type>
class Iterator : public std::iterator<std::random_access_iterator_tag, Type> {
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, Type>::difference_type;
        
        Iterator() : _ptr(nullptr) {}
        Iterator(Type* rhs, Type* _l, Type* _r, Type* _b, Type* _e, long _s) : _ptr(rhs), l(_l), r(_r), b(_b), e(_e), s(_s) {}
        Iterator(const Iterator &rhs) : _ptr(rhs._ptr), l(rhs.l), r(rhs.r), b(rhs.b), e(rhs.e), s(rhs.s) {}
        ~Iterator() {}


        Iterator(Iterator&& rhs) noexcept :
            _ptr(move(rhs._ptr)), l(move(rhs.l)), r(move(rhs.r)), b(move(rhs.b)), e(move(rhs.e)), s(move(rhs.s)) {}


        // Iterator(Iterator&&rhs) noexcept {
        //     _ptr = rhs._ptr;
        //     l = rhs.l;
        //     r = rhs.r;
        //     b  = rhs.b;
        //     e = rhs.e;
        //     s = rhs.s;
        // } 
        // Iterator& operator= (Iterator&& obj)noexcept {return *this;}


        inline Iterator& operator=(Type* rhs) {_ptr = rhs; return *this;}
        inline Iterator& operator=(const Iterator &rhs) {_ptr = rhs._ptr; return *this;}
        inline Iterator& operator+=(difference_type rhs) {
            // if (_ptr + rhs >= e)

            // _ptr += rhs; return *this;
        }

        inline Iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
        inline Type& operator*() const {return *_ptr;}
        inline Type* operator->() const {return _ptr;}
        inline Type& operator[](difference_type rhs) const {
            if (l + rhs >= e)
                return b[(l - e) + rhs];
            else 
                return l[rhs];
        }
        
        inline Iterator& operator++() {
            ++_ptr; 
            if (_ptr == e)
                _ptr = b;
    
            return *this;
        }
        inline Iterator& operator--() {
            if (_ptr == b)
                _ptr = e;
            --_ptr; 
            return *this;
        }

        inline Iterator operator++(int)  {
            Iterator tmp(*this); 
            ++_ptr; 
            if (_ptr == e)
                _ptr = b;
            return tmp;
        }
        inline Iterator operator--(int) const {
            Iterator tmp(*this); 
            if (_ptr == b)
                _ptr = e;
            --_ptr; 
            return tmp;
        }

        inline Iterator operator++(void) const {
            auto tmp = *this; 
            ++_ptr; 
            if (_ptr == e)
                _ptr = b;
            return tmp;
        }
        inline Iterator operator--(void) const {
            auto tmp = *this; 
            if (_ptr == b)
                _ptr = e;
            --_ptr; 
            return tmp;
        }
        /* inline Iterator operator+(const Iterator& rhs) {return Iterator(_ptr+rhs.ptr);} */

        inline difference_type operator-(const Iterator& y) const {
            // cout << "- ";
            if (b <= _ptr && _ptr <= (r) && y._ptr < (e) && y._ptr >= (l)){
                // cout << "b x y e";
                return _ptr - b + e - y._ptr;
            }else if (b <= y._ptr && y._ptr <= (r) && _ptr < (e) && _ptr >= (l)){
                // cout << "b y x e";
                return _ptr - e + b - y._ptr;
            } else {
                // cout << "else ";
                return _ptr - y._ptr;
            }
        }

        inline Iterator operator+(difference_type rhs) const {
            if (_ptr + rhs >= e)
                return Iterator(b + (rhs - (e - _ptr)), l, r, b, e, s);
            else return Iterator(_ptr+rhs, l, r, b, e, s);
        }

        inline Iterator operator-(difference_type rhs) const {
            if (_ptr - rhs < b)
                return Iterator(e - (rhs + (b - _ptr)), l, r, b, e, s);
            else return Iterator(_ptr - rhs, l, r, b, e, s);
        }
        // friend inline Iterator operator+(difference_type lhs, const Iterator& rhs) {
        //     // cout << "+ "
        //     return Iterator(lhs+rhs._ptr, rhs.l, rhs.r, rhs.b, rhs.e, rhs.s);
        // }

        // friend inline Iterator operator-(difference_type lhs, const Iterator& rhs) {
        //     // cout << "- ";
        //     return Iterator(lhs-rhs._ptr);
        // }
        
        inline bool operator==(const Iterator& rhs) {
            // --s;
            return (_ptr == rhs._ptr);
        }

        inline bool operator!=(const Iterator& rhs)  {
            // cout << "!= ";
            // --s;
            return (_ptr != rhs._ptr );
        }


        inline bool operator>(const Iterator& y) const {
            // return *_ptr > *y._ptr;
            if (l <= _ptr && _ptr <= r && l <= y._ptr && y._ptr <= r)
                return _ptr > y._ptr;
            else
            if (b <= _ptr && _ptr < (r) && y._ptr < (e) && y._ptr >= (l))
                return true;
            else if (b <= y._ptr && y._ptr < (r) && _ptr < (e) && _ptr >= (l))
                return false;
            else {
                return _ptr > y._ptr;
            }
        }

        inline bool operator<(const Iterator& y) const {
            // return *_ptr < *y._ptr;
            if (l <= _ptr && _ptr <= r && l <= y._ptr && y._ptr <= r)
                return _ptr < y._ptr;
            else if (b <= _ptr && _ptr < (r) && y._ptr < (e) && y._ptr >= (l))
                return false;
            else if (b <= y._ptr && y._ptr < (r) && _ptr < (e) && _ptr >= (l))
                return true;
            else 
                return _ptr < y._ptr;
        }

        inline bool operator>=(const Iterator& y) const {
            // return *_ptr >= *y._ptr;
            if (l <= _ptr && _ptr <= r && l <= y._ptr && y._ptr <= r)
                return _ptr >= y._ptr;
            else
            if (b <= _ptr && _ptr < (r) && y._ptr < (e) && y._ptr >= (l))
                return true;
            else if (b <= y._ptr && y._ptr < (r) && _ptr < (e) && _ptr >= (l))
                return false;
            else {
                return _ptr >= y._ptr;
            }
        }

        inline bool operator<=(const Iterator& y) const {
            // return *_ptr <= *y._ptr;
            if (l <= _ptr && _ptr <= r && l <= y._ptr && y._ptr <= r)
                return _ptr <= y._ptr;
            else
            if (b <= _ptr && _ptr < (r) && y._ptr < (e) && y._ptr >= (l))
                return false;
            else if (b <= y._ptr && y._ptr < (r) && _ptr < (e) && _ptr >= (l))
                return true;
            else {
                return _ptr <= y._ptr;
            }
        }


        void swap(Iterator& y) {
            swap(*_ptr, y->_ptr);
        }

    private:
        Type* _ptr;
        Type* l; Type* r;
        Type* b; Type* e;
        long s;
};


template<typename T>
class Container {
    public:

    typedef  T                                      value_type;
    typedef  std::size_t                            size_type;
    typedef  std::ptrdiff_t                         difference_type;
    typedef  value_type&                            reference;
    typedef  const value_type&                      const_reference;
    typedef  value_type*                            pointer;
    typedef  const value_type*                      const_pointer;
    typedef  Iterator<T>                                iterator;
    typedef  const Iterator<T>                          const_iterator;
    typedef  std::reverse_iterator<iterator>        reverse_iterator;
    typedef  std::reverse_iterator<const_iterator>  const_reverse_iterator;

    int sz = 5;
    T *array;
    Container() {
        array = new T[sz + 1];
    }
    int l = 0;
    int r = 0;
    int s = 0;
    int b = 0; int e = sz + 1;
    // iterator begin() { return Iterator<T>(&m_data[0], &m_data[sz], s, &m_data[l]); }
    // iterator end()   { return Iterator<T>(&m_data[0], &m_data[sz], s, &m_data[r]); }
    iterator begin() { return Iterator<T>(&array[l], array + l, array + r, array + b, array + e, s); }
    iterator end()   { return Iterator<T>(&array[r], array + l, array + r, array + b, array + e, s); }
    
    void push_back(T t) {
        if (s == sz)
            l = (++l) % (sz + 1);
        else 
            ++s;
        array[r] = t;
        r = (++r) % (sz + 1);
    }

    void delete_back() {
        r = (--r) % (sz + 1);
        --s; 
    }


    void delete_front() {
        l = (++l) % (sz + 1);
        --s;
    }

    T front() {
        return *begin();
    }

    T back() {
        return *(--end());
    }

    T& operator[](int n) {
       return begin()[n];
    }

    void push_front(T t) {
        l = (--l) % (sz + 1);
        if (s == sz)
            r = (--r) % (sz + 1);
        else 
            ++s;
        array[l] = t;
    }


    void resize(int n) {
        T *tmp = new T[n  + 1];
        int i = 0;
        for (auto it = begin(); it != end(); ++it, ++i)
            tmp[i] = *it;
        tmp[i] = *end();
        array = tmp;
        l = 0;
        r = i;
        e = n;
        sz = n;
    }
};




template<class A, class T>
A find_not (A first, A last, const T& val) {
    while (first != last) {
        if (*first!=val) return first;
        ++first;
    }
    return last;
}



#include<vector>
int main() {
    Container<int> c = Container<int>();
    

    srand(11);
    for (int i = 1; i <= 10; ++i) {
        c.push_back(rand()% 100);
    }
    cout << *c.end() << "\n";

    for (int i = 0; i < 6; ++i)
        cout << c.array[i] << " ";
    
    cout << "\n";
    

    for (auto i: c)
        cout << i << " ";


    cout << "\nsort:\n";
    reverse(c.begin(), c.end());
    // sort(c.begin(), c.end());
    for (auto i: c)
        cout << i << " ";
}