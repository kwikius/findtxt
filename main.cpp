

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <quan/fs/get_file_dir.hpp>
#include <quan/fs/get_wkg_dir.hpp>

int main(int argc, const char * argv[])
{
     if(argc <2) {
				std::cout << "useage : findtxt text [ comma-separated-extensions-list ] \n";
           return 0;
      }

     std::string extensions = "";

     if (argc >= 3){
		  std::size_t const len = strlen(argv[2]) + 1;
		  char* parse = new char [len];
		  strcpy (parse,argv[2]);
		  const char delims[] = ", \t";
		  
		  const char* ptr = strtok(parse,delims);
		  int count = 0;
		  while(ptr !=0) {
			 std::string str2 = ptr;
			 if(count == 0){
				 extensions = " \\( -name '" + str2 + "'";
			 }
			 else {
				 extensions += " -o -name '"  + str2 + "'";
			 }
			 ++count;
			 ptr =  strtok(NULL,delims);
		  }
		  extensions += " \\)";
        delete [] parse;
     }else {
     		extensions = " *";
     }   
     std::string cmd = "find " +  quan::fs::get_wkg_dir() + extensions + " -exec grep -H -n '" + std::string (argv[1]) + "' {} \\;" ;

     std::cout << "find \""  << argv[1] << "\" in  \"" << argv[2] << "\"" <<std::endl;

     system(cmd.c_str());
     
}
   // std::string text = "find \( -name '*.pde' -o -name '*.h' -o -name '*.cpp' \) -exec grep -H -n 'elevon1_trim' {} \;"
   //