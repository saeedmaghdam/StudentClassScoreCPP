#ifndef Model_Student
#define Model_Student

#include <string>

using namespace std;

namespace Sa{
	namespace Model{
		struct Student{
			string Id;
			string Name;
			
			Student(){
				Id = "";
				Name = "";
			}
		};
	}
}

#endif
