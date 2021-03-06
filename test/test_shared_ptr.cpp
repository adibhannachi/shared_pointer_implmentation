#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "shared_ptr.h"
#include "myclass.h"


SCENARIO( "SHARED POINTER TEST ", "[SHARED POINTER]" ) {

    GIVEN( "A SHARED POINTER" ) {
		easymile::shared_ptr<MyClass> ptr1(new MyClass(151));
        REQUIRE( ptr1.use_count() == 1 );

        WHEN( "MAKE ANOTHER SHARED POINTER" ) {
			{
				easymile::shared_ptr<MyClass> ptr2 = ptr1;
				THEN( "COUNTER INCREESE" ) {
					REQUIRE(ptr2.get() == ptr1.get() );
					REQUIRE( ptr1.use_count() == 2 );
				}
				THEN( "BOTH POINTER POINT TO THE SOME INSTANCE" ) {
					REQUIRE(ptr2.get() == ptr1.get());
				}
			}
			
			WHEN( "IMPLICIT CALL TO  ~shared pointer" ) {
				THEN( "COUNTER DECREESE" ) {
					REQUIRE( ptr1.use_count() == 1 );
				}
			}
        }
		
		WHEN( "MAKE EXPLICIT CALL TO ~shared pointer" ) {
			ptr1.~shared_ptr();
			THEN( "COUNTER INCREESE" ) {
				REQUIRE( ptr1.use_count() == 0 );
			}
		}
	}
	
	GIVEN( "A SHARED POINTER To AN INSTANCE WITH DATA 5" ) {
		easymile::shared_ptr<MyClass> ptr1(new MyClass(5)); 
		REQUIRE( ptr1.use_count() == 1 );
		THEN( "VALUE ACCEDED BY OPERATOR -> IS 5" ) {
			REQUIRE( ptr1->getData() == 5 );
			
		}
		
		WHEN( "MAKE RESET BY VALUE 2" ) {
			ptr1.reset (new MyClass(2)); 
			THEN( "VALUE IS 2" ) {
				REQUIRE( ptr1->getData() == 2 );
			}
			THEN( "COUNTER IS 1" ) {
				REQUIRE( ptr1.use_count() == 1 );
			}
		}
	}
	
	GIVEN( "A SHARED POINTER FOR A SHARED POINTER" ) {
		easymile::shared_ptr<MyClass> ptr3(new MyClass(151));
		REQUIRE( ptr3.use_count() == 1 );

		easymile::shared_ptr<MyClass> ptr4(ptr3);
		REQUIRE( ptr3.use_count() == 2 );
		
		WHEN( "A SHARED POINTER BY MOVE CONSTRUCTOR" ) {
			easymile::shared_ptr<MyClass> ptr5(std::move(ptr3));
			THEN( "COUNTER WILL STILL 2" ) {
				REQUIRE( ptr5.use_count() == 2 );
			}
			THEN( "INITIAL POINTER WILL BE NULL" ) {
				REQUIRE( ptr3.use_count() == 0 );
				REQUIRE( ptr3.get() == nullptr );
			}
		}
		
		WHEN( "A SHARED POINTER BY MOVE ASSIGNEMENT" ) {
			ptr4 = std::move(ptr3);
			THEN( "INITIAL POINTER WILL BE NULL" ) {
				REQUIRE( ptr3.use_count() == 0 );
				REQUIRE( ptr3.get() == nullptr );
			}
		}
	}
}
