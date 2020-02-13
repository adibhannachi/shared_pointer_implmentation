#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "shared_ptr.h"

TEST_CASE( "SHARED POINTER TEST ", "[SHARED POINTER]" ) 
{
  easymile::shared_ptr<int> ptr1(new int(151));
  REQUIRE( ptr1.use_count() == 1 );
  {
    easymile::shared_ptr<int> ptr2 = ptr1;
    REQUIRE(ptr2.get() == ptr1.get() );
    REQUIRE( ptr1.use_count() == 2 );
  }
  REQUIRE( ptr1.use_count() == 1 );
  ptr1.~shared_ptr();
  REQUIRE( ptr1.use_count() == 0 );
  easymile::shared_ptr<int> sp(new int (5)); 
  sp.reset (new int(2)); 
  REQUIRE( sp.use_count() == 1 );
  *(sp)=10;
  REQUIRE( *sp == 10 );
  sp.reset (new int);
  *sp=20;
  REQUIRE( sp.use_count() == 1 );
  REQUIRE( *sp == 20 );
  easymile::shared_ptr<int> ptr4(new int(151)); 
  easymile::shared_ptr<int> ptr3(ptr4);
  REQUIRE(ptr3.get() == ptr4.get() );
  REQUIRE( ptr3.use_count() == 2 );
  easymile::shared_ptr<int>&& ptr5(std::move(ptr3));
  REQUIRE( ptr5.use_count() == 2 );
  REQUIRE(ptr3.get() == ptr5.get() );
}
