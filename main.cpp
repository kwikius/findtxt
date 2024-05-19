

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <quan/fs/get_file_dir.hpp>
#include <quan/fs/get_wkg_dir.hpp>

/*
TODO. Could use extended-regex with grep -E or egrep
*/

int main(int argc, const char * argv[])
{
     if(argc <2) {
				std::cout << "useage : findtxt text [ comma-separated-extensions-list ] [ not ] \n";
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
             // -type f -> exclude directories
				 extensions = " \\( -type f -name '" + str2 + "'";
			 }
			 else {
				 extensions += " -type f -o -name '"  + str2 + "'";
			 }
			 ++count;
			 ptr = strtok(NULL,delims);
		  }
		  extensions += " \\)";
        delete [] parse;
     }else {
     		extensions = " *";
     }
     std::string invert = "";
     std::string notstr = "";
     if ( argc >= 4){
      if (!strcmp(argv[3],"not")){

         invert = "--files-without-match";
         notstr = " ! " ;
      }
     }

     std::string cmd = "find " + quan::fs::get_wkg_dir() + extensions + " -exec egrep "
         + invert + " -H -n '" + std::string (argv[1]) + "' {} \\;" ;

     std::cout << "find \"" << notstr << argv[1] << "\" in  \"" << argv[2] << "\"" << std::endl;

    if (system(cmd.c_str())){
      std::cout << "--------------------------------------------\n";
    }

}
   // std::string text = "find \( -type f -name '*.pde' -o -name '*.h' -o -name '*.cpp' \) -exec grep -H -n 'elevon1_trim' {} \;"
   //

