#include <iostream>
#include <cmath>

class Triangle
{
private:
   
   //side lengths
   double sa;
   double sb;
   double sc;
   
   //Angle sizes
   double AA;
   double AB;
   double AC;
   
   bool valid();
   
   class Invalid{};
   
public:
   
   Triangle( double aa, double bb, double cc )
      :sa{aa}, sb{bb}, sc{cc}
   {
      if(!valid()) throw Invalid{};
      
      else
      {
         AA = acos( (sb*sb + sc*sc - sa*sa) / (2*sb*sc) );
         
         AB = acos( (sa*sa + sc*sc - sb*sb) / (2*sa*sc) );
            
         AC = acos( (sb*sb + sa*sa - sc*sc) / (2*sb*sa) );
      }
   };
   
   double side_1(){return sa;};
   
   double side_2(){return sb;};
   
   double side_3(){return sc;};
   
   double ang_1(){return AA;};
   
   double ang_2(){return AB;};
   
   double ang_3(){return AC;};
   
};

bool Triangle::valid()
{
   return ( sa < sb + sc &&
      sb < sa + sc &&
      sc < sa + sb &&
      sa > 0 &&
      sb > 0 &&
      sc > 0 );
}

int main()
{
   Triangle a = Triangle(3, 4, 5);
   
   std::cout << a.side_1() << " "
      << a.side_2() << " " << a.side_3() << "\n";
   
   std::cout << a.ang_1() << " " << a.ang_2() << " " << a.ang_3() << "\n";
}

