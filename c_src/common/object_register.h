#ifndef OBJECT_REGISTER_H
#define OBJECT_REGISTER_H

#include <stdint.h>

#ifndef GOOGLE_HASH_MAP
/* Use google hash map */
#include <google/dense_hash_map>
/* dirty code begin */
#include HASH_FUN_H
#define HASH_TPL SPARSEHASH_HASH
#define HASH_MAP google::dense_hash_map
/* dirty code end */

#else

/* Use xapian wrapper for hash map */
#include "unordered_map.h"
#define HASH_TPL std::hash
#define HASH_MAP std::unordered_map
#endif


#include "xapian_config.h"
XAPIAN_ERLANG_NS_BEGIN

class ObjectBaseRegister
{
    protected:
    typedef uint32_t Counter;

    public:
    virtual ~ObjectBaseRegister() {};

    virtual void
    remove(Counter) = 0;

    virtual void*
    getVoidPointer(Counter) = 0;

    virtual Counter 
    putVoidPointer(void* obj) = 0;

    virtual void* 
    replaceWithoutCleaning(uint32_t num, void* new_obj) = 0;
};


template <class Child>
class ObjectRegister : public ObjectBaseRegister
{
    public:
    typedef 
    HASH_MAP< uint32_t, Child*, HASH_TPL<uint32_t> > Hash;

    private:
    /* Contains a number of the latest added object */
    Counter m_counter;
    Hash m_elements;

    public:

    ObjectRegister();

    Child*
    get(Counter num);

    Counter 
    put(Child* obj);

    void*
    getVoidPointer(Counter num);

    Counter 
    putVoidPointer(void* obj);

    void
    remove(Counter num);

    void* 
    replaceWithoutCleaning(uint32_t num, void* new_obj);

    Hash&
    getElements()
    {
        return m_elements;
    }

    ~ObjectRegister();
};


XAPIAN_ERLANG_NS_END
#include "object_register.hpp"

#endif
