#include <iostream> 
#include "shared_ptr.h"
#include "myclass.h"

using namespace std;

int main() 
{ 
    easymile::shared_ptr<MyClass> ptr1(new MyClass(1122)); 
    cout << "VALUE : " <<  ptr1->getData() << endl;
	cout << "COUNT :: " << ptr1.use_count() << endl;
    { 
        easymile::shared_ptr<MyClass> ptr2 = ptr1; 
        cout << "VALUE : " <<  ptr1->getData() << endl;
		cout << "COUNT :: " << ptr1.use_count() << endl;
        ptr2->setData(5);
        cout << "VALUE : " <<  ptr1->getData() << endl;
    } 
	cout << "COUNT :: " << ptr1.use_count() << endl;
	cout << "VALUE : " <<  ptr1->getData() << endl;
  
    return 0; 
} 
