#ifndef Helper_UI
#define Helper_UI

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include "../Model/Student.h"
#include "../Bll/StudentManager.h"
#include "../Bll/CourseManager.h";
#include "../Bll/StudentPointManager.h";

using namespace std;

namespace Sa{
	namespace Helper{
		class UI{
			public:
				Initialize(){
					MainForm();
					HandleMainFormMenu();
				}
				
			private:
				void MainForm(){
					Clear();
					TopMargin();
					
					cout << "\t\t1) New student" << endl << endl;
					cout << "\t\t2) New point" << endl << endl;
					cout << "\t\t3) Report" << endl << endl;
					cout << "\t\t9) Factory reset (!!!)" << endl << endl;
					cout << "\t\t0) Exit" << endl << endl;
				}
				
				void HandleMainFormMenu(){
					char ch;
					do {
						ch = getch(); 
						
						switch (ch){
							case '1':
								NewStudentForm();
								break;
							case '2':
								NewStudentPointForm();
								break;
							case '3':
								ReportForm();
								break;
							case '9':
								Sa::Helper::File file = Sa::Helper::File("student");
								file.Remove();
								
								file = Sa::Helper::File("student_point");
								file.Remove();
								
								break;
						}
					} while (ch != '0');
				}
				
				void NewStudentForm(){
					Sa::Model::Student student;
					Sa::Bll::StudentManager studentManager;
					
					Clear();
					cout << endl << endl << "\t\t*** To cancel process, enter -1 ***";
					TopMargin();
					
					cout << "\t\tStudent Id: ";
					cin >> student.Id;
					cout << endl << endl;
					
					if (student.Id == "-1"){
						MainForm();
						return;
					}	
					
					if (studentManager.IsDuplicate(student)){
						cout << "\t\tStudent id exists. try again ...";
						getch();
						
						MainForm();
						
						return;
					}
					
					cout << "\t\tFull name: ";
					cin >> student.Name;
					cout << endl << endl;
					
					if (student.Name == "-1"){
						MainForm();
						return;
					}	
					
					Clear();
					TopMargin();
					
					studentManager.Insert(student);
					
					cout << "\t\tStudent inserted successfully!";
					
					getch();
					
					MainForm();
				}
				
				void CourseSelectMenu(){
					Sa::Bll::CourseManager courseManager;
					
					Clear();
					TopMargin();
					
					cout << "\t\tSelect course: " << endl << endl;
					
					vector<Sa::Model::Course> courses = courseManager.Get();
					for (int i = 0; i < courses.size(); i++)
						cout << "\t\t" << courses[i].Id << ") " << courses[i].Name << endl << endl;
						
					cout << "\t\t0) Cancel";
				}
				
				void NewStudentPointForm(){
					Sa::Bll::CourseManager courseManager;
					
					CourseSelectMenu();
					
					char ch;
					do {
						ch = getch(); 
						
						string courseId(1, ch);
						if (courseManager.IsValid(courseId)){
							NewStudentPointStep2Form(courseId);
							break;
						}
					} while (ch != '0');
					
					MainForm();
				}
				
				void NewStudentPointStep2Form(string courseId){
					Sa::Bll::CourseManager courseManager;
					Sa::Bll::StudentManager studentManager;
					Sa::Bll::StudentPointManager studentPointManager;
					
					do{
						string studentId;
						string point;
						
						Clear();
						cout << endl << endl << "\t\t*** To cancel process, enter -1 ***";
						TopMargin();
						
						cout << "\t\tStudent Id: ";
						cin >> studentId;
						if (studentId == "-1")
							break;
							
						Sa::Model::StudentPoint studentPoint;
						studentPoint.CourseId = courseId;
						studentPoint.StudentId = studentId;
						
						if (studentPointManager.IsDuplicate(studentPoint)){
							cout << "\t\tYou've entered point to this student id before.";
							getch();
							continue;
						}
						
						if (!studentManager.IsValid(studentId)){
							cout << "\t\tStudent id is not valid! Try again ..." << endl;
							getch();
							
							continue;
						}
						
						Sa::Model::Student student = studentManager.GetById(studentId);
						cout << "\t\t" << student.Name << endl << endl << "\t\tPoint: ";
						cin >> point;
						if (studentId == "-1")
							break;
						
						Clear();
						TopMargin();
						
						studentPoint.Point = point;
						
						studentPointManager.Insert(studentPoint);
						
						cout << "\t\tPoint inserted successfully! try another one ...";
						
						getch();
					} while (true);
				}
				
				void ReportForm(){
					Sa::Bll::CourseManager courseManager;
					
					CourseSelectMenu();
					
					char ch;
					do {
						ch = getch(); 
						
						string courseId(1, ch);
						if (courseManager.IsValid(courseId)){
							ReportStep2Form(courseId);
							break;
						}
					} while (ch != '0');
					
					MainForm();
				}
				
				void ReportStep2Form(string courseId){
					Sa::Bll::CourseManager courseManager;
					Sa::Bll::StudentManager studentManager;
					Sa::Bll::StudentPointManager studentPointManager;
					
					Clear();
					
					cout << "=========================================================" << endl;
					cout << courseManager.GetById(courseId).Name << endl;
					cout << "=========================================================" << endl;
					gotoxy(0, 3);
					cout << "Student Id";
					gotoxy(20, 3);
					cout << "Full name";
					gotoxy(40, 3);
					cout << "Point";
					gotoxy(0, 4);
					
					vector<Sa::Model::StudentPoint> studentPoints = studentPointManager.Get();
					
					double passedSum = 0;
					double notPassedSum = 0;
					int passedCount = 0;
					int notPassedCount = 0;
					int reportStartRow = 4;
					for(int i = 0; i < studentPoints.size(); i++){
						Sa::Model::StudentPoint studentPoint = studentPoints[i];
						Sa::Model::Course course = courseManager.GetById(studentPoint.CourseId);
						
						if (course.Id != courseId)
							continue;
							
						Sa::Model::Student student = studentManager.GetById(studentPoint.StudentId);
						
						gotoxy(0, reportStartRow);
						cout << student.Id;
						gotoxy(20, reportStartRow);
						cout << student.Name;
						gotoxy(40, reportStartRow);
						cout << studentPoint.Point;
						
						double doublePoint;
					    sscanf ( studentPoint.Point.c_str(), "%lf" , &doublePoint);
						
						if (doublePoint > 12){
							passedSum += doublePoint;
							passedCount++;
						}
						else{
							notPassedSum += doublePoint;
							notPassedCount++;
						}
						
						reportStartRow++;
					}
					
					if (studentPoints.size() > 0){
						cout << endl << "=========================================================" << endl;
						if (passedCount > 0)
							cout << "Passed average: " << passedSum / passedCount << endl;
						
						if (notPassedCount > 0)
							cout << "Not passed average: " << notPassedSum / notPassedCount << endl;
					}
					
					getch();
					
					MainForm();
				}
				
				void TopMargin(){
					cout << endl << endl << endl << endl << endl << endl;
				}
				
				void Clear()
				{
				#if defined _WIN32
				    system("cls");
				    //clrscr(); // including header file : conio.h
				#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
				    system("clear");
				    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
				#elif defined (__APPLE__)
				    system("clear");
				#endif
				}
				
				void gotoxy( int column, int line )
				{
					COORD coord;
					coord.X = column;
					coord.Y = line;
					SetConsoleCursorPosition(
				  		GetStdHandle( STD_OUTPUT_HANDLE ),
				  		coord
					);
				}
				
				int wherex()
				{
					CONSOLE_SCREEN_BUFFER_INFO csbi;
				  	if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
				    	return -1;
				  	return csbi.dwCursorPosition.X;
				}
				
				int wherey()
				{
					CONSOLE_SCREEN_BUFFER_INFO csbi;
				  	if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &csbi))
				    	return -1;
				  	return csbi.dwCursorPosition.Y;
				}
		};
	}
}

#endif
