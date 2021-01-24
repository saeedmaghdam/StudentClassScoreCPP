#ifndef Model_StudentPoint
#define Model_StudentPoint

#include <string>

using namespace std;

namespace Sa{
	namespace Model{
		struct StudentPoint {
			string CourseId;
			string StudentId;
			string Point;
			
			StudentPoint(){
				CourseId = "";
				StudentId = "";
				Point = "";
			}
		};
	}
}

#endif
