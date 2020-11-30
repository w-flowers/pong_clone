#include <iostream>
#include <random>
#include <ctime>
#include "../src/paddle.cpp"

int main()
{
   std::default_random_engine gen;
   gen.seed((int) std::time(NULL));
   std::uniform_int_distribution<int> dist(1, 100);
   
   
   Paddle test = Paddle(40, 10, 360, 10, 620, 100);
   std::cout << "angle: " << test.get_angle() << "\n";
   std::cout << "width: " << test.get_width() << "\n";
   std::cout << "thickness: " << test.get_thickness() << "\n";
   std::cout << "horizontal position: " << test.get_hori_pos() << "\n";
   std::cout << "vertical position: " << test.get_vert_pos() << "\n";
   
   int rand_test = dist(gen); 
   
   for( int i = 0; i < rand_test; ++i)
   {
      test.move_right();
   }
   
   std::cout << "new horizontal position: " << test.get_hori_pos() << "\n";
   
   rand_test = dist(gen); 
   
   for( int i = 0; i < rand_test; ++i)
   {
      test.move_left();
   }
   
   std::cout << "new horizontal position: " << test.get_hori_pos() << "\n";
   
   rand_test = dist(gen); 
   
   for( int i = 0; i < rand_test; ++i)
   {
      test.shrink_angle();
   }
   
   std::cout << "new angle: " << test.get_angle() << "\n";
   
   rand_test = dist(gen);
   for( int i = 0; i < rand_test; ++i)
   {
      test.expand_angle();
   }
   
   std::cout << "new angle: " << test.get_angle() << "\n";
}