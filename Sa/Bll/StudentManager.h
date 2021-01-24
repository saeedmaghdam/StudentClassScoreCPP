#ifndef Bll_StudentManager
#define Bll_StudentManager

#include "../Model/Student.h"
#include "../Helper/File.h"
#include "../Helper/String.h"
#include <vector>

namespace Sa{
	namespace Bll{
		class StudentManager{
			public:				
				void Insert(Sa::Model::Student student){
					Sa::Helper::File db = Sa::Helper::File(dbName);	
					
					db.Append(string(student.Id) + "|" + string(student.Name));
				}
								
				vector<Sa::Model::Student> Get(){
					Sa::Helper::File db = Sa::Helper::File(dbName);	
					
					vector<Sa::Model::Student> result;
					
					vector<string> lines = db.GetLines();
					
					for(int i = 0; i < lines.size(); i++)
					{
						Sa::Helper::String stringHelper;
						Sa::Model::Student student;
						string line = lines[i];
						vector<string> parts = stringHelper.Split(line, '|');
						
						student.Id = parts[0];
						student.Name = parts[1];
						
						result.push_back(student);
					}
					
					return result;
				}
				
				Sa::Model::Student GetById(string studentId){
					Sa::Model::Student result;
					vector<Sa::Model::Student> students = Get();
					
					for(int i = 0; i < students.size(); i++){
						if (students[i].Id == studentId)
						{
							result = students[i];
							break;
						}
					}
					
					return result;
				}
				
				bool IsValid(string studentId){
					Sa::Model::Student student = GetById(studentId);
					
					if (student.Id == "")
						return false;
						
					return true;
				}
				
				bool IsDuplicate(Sa::Model::Student student){
					vector<Sa::Model::Student> students = Get();
					bool isDuplicate = false;
					
					for(int i = 0; i < students.size(); i++){
						if (student.Id.compare(students[i].Id) == 0){
							isDuplicate = true;
							break;
						}
					}
					
					return isDuplicate;
				}
			private:
				const string dbName = "student";
		};
	}
}

#endif
