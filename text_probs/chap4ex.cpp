#include "std_lib_facilities.h"

double convert_to_cm(double val, string unit);

int main()
{
   cout << "Please enter a value and a unit (m, cm, in or ft) seperated by a space. \n";
   
   string unit = " ";
   
   double i = 0;
   
   while(!(cin >> i >> unit) || ( unit != "m" && 
            unit != "cm" && 
            unit != "in" &&
            unit != "ft" ) ) cout << "Please try again.\n";
   
   double small = i;
   
   string small_unit = unit;
   
   double large = i;
   
   string large_unit = unit;
   
   double sum = convert_to_cm(i, unit)/100.0; //convert to m
   
   int no_vals = 1;
   
   vector<double> vals = {convert_to_cm(i, unit) / 100.0};
   
   cout << "The new value is : " << i << " " << unit << ".\n";
   
   cout << "Please enter a value and a unit (m, cm, in or ft) seperated by a space. \n";
   
   while( cin >> i >> unit )
   {
      cout << "The new value is : " << i << " " << unit << ".\n";
      if( unit != "m" && 
         unit != "cm" && 
         unit != "in" &&
         unit != "ft" )
            cout << unit << " is not a valid unit.\n";
      
      else
      {
         if( convert_to_cm( i, unit ) < convert_to_cm( small, small_unit ) )
         {
            small = i;
            
            small_unit = unit;
         
            cout << "The smallest so far!\n";
         }
      
         else if( convert_to_cm( i, unit ) > convert_to_cm( large, large_unit ) )
         {
            large = i;
            
            large_unit = unit;
         
            cout << "The largest so far!\n";
         }
         
         sum += convert_to_cm( i, unit )/100;
         
         ++no_vals;
         
         vals.push_back(convert_to_cm(i, unit) / 100.0);
         
         cout << "Please enter a value and a unit (m, cm, in or ft) seperated by a space. \n";
      }
   }
   
   cout << "Smallest value: " << small << small_unit << "\n"
      << "Largest value: " << large << large_unit << "\n"
      << "Sum of values: " << sum << "m\n"
      << "Number of values: " << no_vals << "\n";
   
   sort(vals);
   
   for(int i = 0; i < vals.size(); ++i) cout << vals[i] << "\n"; 
   
   return 0;
}

double convert_to_cm(double val, string unit)
{
   double newval = 0;
   
   if(unit == "cm") newval = val;
   
   else if(unit == "m") newval = 100*val; //100cm = 1m
   
   else if(unit == "in") newval = 2.54*val; //1 inch = 2.54cm
   
   else if(unit == "ft") newval = 12*2.54*val; // 1 foot = 12 * 2.54cm
   
   else cout << "Invalid units.\n";
   
   return newval;
}
