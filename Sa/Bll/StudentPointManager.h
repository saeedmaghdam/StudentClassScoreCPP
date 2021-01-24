#ifndef Bll_StudentPointManager
#define Bll_StudentPointManager

#include <string>
#include "../Model/StudentPoint.h"

using namespace std;

namespace Sa{
	namespace Bll{
		class StudentPointManager{
			public:
				void Insert(Sa::Model::StudentPoint studentPoint){
					Sa::Helper::File db = Sa::Helper::File(dbName);	
					
					db.Append(string(studentPoint.CourseId) + "|" + string(studentPoint.StudentId) + "|" + studentPoint.Point);
				}
				
				vector<Sa::Model::StudentPoint> Get(){
					Sa::Helper::File db = Sa::Helper::File(dbName);	
					
					vector<Sa::Model::StudentPoint> result;
					
					vector<string> lines = db.GetLines();
					
					for(int i = 0; i < lines.size(); i++)
					{
						Sa::Helper::String stringHelper;
						Sa::Model::StudentPoint studentPoint;
						string line = lines[i];
						vector<string> parts = stringHelper.Split(line, '|');
						
						studentPoint.CourseId = parts[0];
						studentPoint.StudentId = parts[1];
						studentPoint.Point = parts[2];
						
						result.push_back(studentPoint);
					}
					
					return result;
				}
				
				bool IsDuplicate(Sa::Model::StudentPoint studentPoint){
					vector<Sa::Model::StudentPoint> studentPoints = Get();
					bool isDuplicate = false;
					
					for(int i = 0; i < studentPoints.size(); i++){
						if (studentPoint.CourseId.compare(studentPoints[i].CourseId) == 0 && studentPoint.StudentId.compare(studentPoints[i].StudentId) == 0){
							isDuplicate = true;
							break;
						}
					}
					
					return isDuplicate;
				}
				
			private:
				const string dbName = "student_point";
		};
	}
}

#endif
