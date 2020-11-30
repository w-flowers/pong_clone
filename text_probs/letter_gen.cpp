#include "std_lib_facilities.h"

int main()
{
   cout << "Please enter the recipients name:\n";
   
   string first_name = "";
   
   cin >> first_name;
   
   cout << "Dear " << first_name << ",\n";
   
   cout << "This is a letter\n"
      
      << "I hope it finds you well\n"
         
      << "More words. Hmmn.\n"
         
      << "Your friend, what were they called?\n";
   
   string friends_name = "";
   
   cin >> friends_name;
   
   cout << "Have you seen "
      
      << friends_name << " lately?\n";
}