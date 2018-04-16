#ifndef __NONCOPYABLE_HPP_INCLUDE__
#define __NONCOPYABLE_HPP_INCLUDE__

class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}

private:
    noncopyable( const noncopyable& );
    const noncopyable& operator=( const noncopyable& );
};

#endif
