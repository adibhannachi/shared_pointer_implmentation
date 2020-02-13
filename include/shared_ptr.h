#include <sstream>
#include <exception>

using namespace std; 

namespace easymile {

  template <class T>
  class shared_ptr
  {
  public:
    /**
    * Constructs a shared_ptr with ptr as the pointer to the managed object.
    */
    explicit shared_ptr(T* ptr= nullptr) 
    { 
      m_ptr = ptr; 
        m_counter = new long(); 
      *m_counter = 0; 
      if (ptr) { 
        (*m_counter)++; 
      } else {
        throw  exception();
      }
    };
    
    /**
    * destroye and deallocate the memory of the object when the last remaining 
    * shared_ptr owning the object is destroyed 
    */
    ~shared_ptr() 
    { 
      if (m_counter) {
        (*m_counter)--;
      }
      if (m_counter && ((*m_counter) == 0) && m_ptr) { 
        delete m_ptr; 
        delete m_counter;
        m_ptr = nullptr;
        m_counter = nullptr;
      } 
    };

    /**
    * Constructs a shared_ptr which shares ownership of the object managed by rhs.
    * If rhs manages no object, *this manages no object too. 
    * */
    shared_ptr(const shared_ptr& rhs)
    {
      m_ptr = rhs.m_ptr; 
      m_counter = rhs.m_counter; 
      if (m_counter)
        (*m_counter)++; 
    };

    /**
    * Return the value number of shared_ptr instances managing the current object 
    **/
    long use_count() const{
      if (m_counter)
        return (*m_counter);
      return 0;
    };

    /**
    * Returns the stored pointer
    */
    T* get() const{ 
        return m_ptr; 
      };
      
    /**
     * Dereferences the stored pointer.
     * The behavior is undefined if the stored pointer is null.
     * */
    T& operator*() const{
      if (m_ptr == nullptr)
        throw  exception();
      return *m_ptr;
    };
    
    /**
     * The stored pointer
     * */
    T* operator->() const{
      return m_ptr;
    };

    void swap(shared_ptr& ptr)
    {
      std::swap(m_ptr, ptr.m_ptr);
      std::swap(m_counter, ptr.m_counter);
    }
    
    /**
     * Replaces the managed object with an object pointed to by ptr.
     **/
    void reset(T* ptr)
    {
      if (get() != ptr)
      {
        shared_ptr tmp(ptr);
        swap(tmp);
      }
      *m_counter = 1;
    }

    /**
     * Shares ownership of the object managed by rhs.
     * If rhs manages no object, *this manages no object too.
     * COPY ASSIGNEMENT 
     * */
    shared_ptr& operator=(const shared_ptr& rhs)
    {
      if (&rhs != this)
      {
        shared_ptr tmp(rhs);
        m_ptr = tmp.mptr;
        (*m_counter)= tmp.use_count();
      }
      return *this;
    };

    /**
    * Move-constructs a shared_ptr from rhs.
    * After the construction, *this contains a copy of the previous state of rhs
    * rhs is empty and its stored pointer is null.
    * MOVE CONSTRUCTOR
    **/
    shared_ptr(shared_ptr&& rhs)
    {
      m_ptr = rhs.m_ptr;
      *m_counter = rhs->m_counter;
      rhs->m_counter = nullptr;
      rhs.m_ptr = nullptr;
    };

    /**
     * Move-assigns a shared_ptr from r.
     * After the assignment, *this contains a copy of the previous state of rhs, and rhs is empty.
     * MOVE ASSIGNEMENT
     * */
    shared_ptr& operator=(shared_ptr&& rhs)
    { 
      if (&rhs != this)
      {
        if (m_counter && m_ptr)
        {
          delete m_ptr; 
          delete m_counter;
        }
        m_ptr = rhs.m_ptr;
        m_counter = rhs.m_counter;
      }
      rhs.m_counter = nullptr;
      rhs.m_ptr = nullptr;
      return *this;
    };
    
    friend ostream& operator<<(ostream& os, shared_ptr<T>& sp)
    { 
      os << "Address pointed : " << sp.get() << endl;
      cout << *(sp.m_counter) << endl;
    }

  private:
    long *m_counter{};
    T    *m_ptr;
  };


}
