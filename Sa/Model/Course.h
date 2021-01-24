#ifndef Model_Course
#define Model_Course

#include <string>

using namespace std;

namespace Sa{
	namespace Model{
		struct Course {
			string Id;
			string Name;
			
			Course(){
				Id = "";
				Name = "";
			}
		};
	}
}

#endif
