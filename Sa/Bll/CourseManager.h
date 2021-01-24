#ifndef Bll_CourseManager
#define Bll_CourseManager

#include "../Model/Course.h"

namespace Sa{
	namespace Bll{
		class CourseManager{
			public:
				vector<Sa::Model::Course> Get(){
					vector<Sa::Model::Course> result;
					
					Sa::Model::Course c1;
					c1.Id = "1";
					c1.Name = "Math";
					result.push_back(c1);
					
					c1.Id = "2";
					c1.Name = "Algorithms";
					result.push_back(c1);
					
					c1.Id = "3";
					c1.Name = "Data Structure";
					result.push_back(c1);
					
					c1.Id = "4";
					c1.Name = "Statistics";
					result.push_back(c1);
					
					return result;					
				}
				
				Sa::Model::Course GetById(string courseId){
					Sa::Model::Course result;
					vector<Sa::Model::Course> courses = Get();
					
					for(int i = 0; i < courses.size(); i++){
						if (courses[i].Id == courseId)
						{
							result = courses[i];
							break;
						}
					}
					
					return result;
				}
				
				bool IsValid(string courseId){
					Sa::Model::Course course = GetById(courseId);
					
					if (course.Id == "")
						return false;
						
					return true;
				}
		};
	}
}

#endif
