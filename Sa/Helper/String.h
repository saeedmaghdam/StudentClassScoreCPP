#ifndef Helper_String
#define Helper_String

#include <string>
#include <vector>

using namespace std;

namespace Sa{
	namespace Helper{
		class String{
			public:
				vector<string> Split(string input, char seperator){
					vector<string> parts;
					int index = 0;
					int count = 0;
					for(int i = 0; i < input.length(); i++)
					{
						if (input[i] == '|'){
							parts.push_back(input.substr(index, count));
							index += count + 1;
							count = 0;
							
							continue;
						} 
						
						count++;
					}
					if (index < input.length()){
						parts.push_back(input.substr(index, input.length() - 1));
					}
					
					return parts;
				}
		};
	}
}

#endif
