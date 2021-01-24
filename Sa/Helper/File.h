#ifndef Helper_File
#define Helper_File

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Sa{
	namespace Helper{
		class File{
			public:
				File(string fileName){
					_fileName = fileName;
				}
				
				void Append(string line){
					fstream appendFileToWorkWith;
					
					appendFileToWorkWith.open(_fileName.c_str(), ios::in | ios::out | ios::app);

			      	// If file does not exist, Create new file
			      	if (!appendFileToWorkWith) 
			      	{
			        	appendFileToWorkWith.open(_fileName.c_str(),  fstream::in | fstream::out | fstream::trunc);
			       		appendFileToWorkWith << line << endl;
			       		appendFileToWorkWith.close();
			       	} 
			       	else   
			       	{
			       		appendFileToWorkWith << line << endl;
			        	cout<<"\n";
			        	appendFileToWorkWith.close();
			        }
				}
				
				vector<string> GetLines(){
					ifstream file(_fileName.c_str());
					string line;
					vector<string> lines;
					
					while(getline(file, line))
						lines.push_back(line);
						
					return lines;
				}
				
				void Remove(){
					Append("");
					remove(_fileName.c_str());
				}
			private:
				string _fileName;
		};
	}
}

#endif
