
/********************************************************************************
* Pong Clone - Physics (physics.cpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/physics.hpp"

Field_Grid::Field_Grid( const Field& field, int rows, int columns )
   : num_rows {rows}, num_cols {cols}, field_sqrs {} 
{
   field_sqrs.reserve( num_rows * num_cols );

   //INSERT code to initialise field squares
   int remaining_height = field.get_y_dim();

   int remaining_width = field.get_x_dim();

   int current_x = 0;

   int current_y = 0;

   int new_h = 0;

   int new_w = 0;

   for( int i = 0; i < num_rows * num_cols ; i++ )
   {
      if( i % num_cols )
      {
         current_x = 0;

         current_y += new_h;

         new_h = remaining_height / (num_rows - i / num_rows );

         remaining_height -= new_h;

         remaining_width = field.get_x_dim();
      }

      new_w = remaining_width / ( num_cols - i % num_colss );

      remaining_width -= new_w;

      field_sqrs.emplace_back( {{}, {}, {}, {current_x, current_y}, new_w, new_h} ); //MUST BE EDITED

      current_x += new_w;
   }

   for( int i = 0; i < field.get_ball_vec_size(); i++ )
   {
      assign_ball_to_squares( field.get_ball( i ) );
   }

   for( int i = 0; i < field.boundary.get_lines_size(); i++ )
   {
      assign_line_to_squares( field.boundary.get_line( i ) );
   }
   //insert similar things for paddles once implemented
}

void Field_Grid::assign_ball_to_squares( const Ball& ball)
{
   struct position ball_p = ball.get_position();
   
   std::vector<int> cols {};

   // Check if line is within radius of vert dividers
   for( i = 1; i < num_cols; i++ )
   {
      if( abs( ball_p.x - field_sqrs[i].pos.x ) <= ball.get_radius() )
      {
         cols.push_back( i - 1 );

         cols.push_back( i );

         break;
      }
   }
   
   // Find unique column containing ball centre if it isn't on divider
   if( cols.empty() )
   {
      for( i = 0; i < num_cols; i++ )
      {
         if( ball_p.x < field_sqrs[i].pos.x + field_sqrs[i].w )
         {
            cols.push_back( i );

            break;
         }
      }
   }

   std::vector<int> rows {};

   // Check if line is within radius of horizontal dividers
   for( i = 1; i < num_rows; i++ )
   {
      if( abs( ball_p.y - field_sqrs[num_cols*i].pos.y ) <= ball.get_radius() )
      {
         rows.push_back( i - 1 );

         rows.push_back( i );

         break;
      }
   }

   // Find unique row containing ball centre if it isn't on divider
   if( rows.empty() )
   {
      for( i = 0; i < num_rows; i++ )
      {
         if( ball_p.y < field_sqrs[num_cols*i].pos.y + field_sqrs[num_cols*i].h)
         {
            rows.push_back( i );

            break;
         }
      }
   }

   int invalid_index = -1;

   // This section exists to determine if a ball is in all four squares or only
   // three squares. Relies on fact that cols[0] is less than cols[1].
   if( cols.size() == 2 && rows.size() == 2 )
   {
      //find row and column index of ball centre
      int bc_row = 0;

      int bc_col = 0;

      //find row and column of square diagonal to ball
      int d_row = 0;

      int d_col = 0;

      int mid_x = field_sqrs[ cols[0] ].pos.x + field_sqrs[ cols[0] ].w ;

      int mid_y =  field_sqrs[ num_cols * rows[0] ].pos.y 
         + field_sqrs[ num_cols * rows[0] ].h;

      if( ball_p.x < mid_x )
      {
         bc_col = cols[0];

         d_col = cols[1];
      }
      else
      {
         bc_col = cols[1];

         d_col = cols[0];
      }
      if( ball_p.y < mid_y )
      {
         bc_row = rows[0];

         d_row = rows[1];
      }
      else
      {
         bc_row = rows[1];

         d_row = rows[0];
      }

      struct position middle_corner = field_sqrs[ cols[1] + num_cols * rows[1] ].pos;

      // Distance from centre is less than or equal to ball radius
      // Means ball is in fourth square
      if( square_int( ball_p.x - middle_corner.x ) 
            + square_int( ball_p.y - middle_corner.y )
            <= square_int( ball.get_radius() ) )
      {
         for( int i : cols )
         {
            for( int j : rows )
            {
               field_sqrs[i + j*num_cols].balls.push_back( &ball );
            }
         }
      }

      //Ball is not in fourth square
      else
      {
         for( int i : cols )
         {
            for( int j : rows )
            {
               if( i != d_col || j != d_row )
               {
                  field_sqrs[i + j*num_cols].balls.push_back( &ball );
               }
            }
         }
      }
   }

   // Case where ball is only on one or no dividers
   else
   {
      for( int i : cols )
      {
         for( int j : rows )
         {
            field_sqrs[i + j*num_cols].balls.push_back( &ball );
         }
      }
   }
}

void Field_Grid::assign_line_to_squares( const Line& line)
{

}

void Physics::bounce( Ball& ball, float edge_angle )
{
      float newangle = 2 * edge_angle - ball.vel_angle();
      
      ball.set_velocity( 
            //x value
            static_cast<int>( lroundf( ball.get_speed() * cosf( newangle ) ) ),

            //y value
            static_cast<int>( lroundf( ball.get_speed() * sinf( newangle ) ) )
            );
      
      return;
}

void Physics::collide_ball_point( Ball& ball, struct position pos )
{
   int dx = ball.get_position().x - pos.x;

   int dy = ball.get_position().y - pos.y;

   int br = ball.get_radius();

   if( square_int( dy ) + square_int( dx ) <= br * br )
   {
      // Compute angle of perpendicular to line from centre of ball to point and
      // pass to bounce method of ball

      ball.bounce( 
            ( atan2f( static_cast<float>( dy ), static_cast<float>( dx ) )
            + this_pi / 2.0 ) 
            );
   }
}

bool Physics::is_colliding_bl( Ball& ball, const Line& line )
{
   struct positionf curr_pos { static_cast<float>( ball.get_position().x ), 
      static_cast<float>( ball.get_position().y ) };

   int x1 = line.get_p1().x;

   int x2 = line.get_p2().x;

   int y1 = line.get_p1().y;

   int y2 = line.get_p2().y;

   Line_Eq l_e { (y2 - y1), ( -(x2 - x1) ), {x1, y1} };

   //check if within radius of line
   if( sqrd_dist_pt_ln( curr_pos, l_e ) <=
         square_float( (float) ball.get_radius() ) )
   {
      float xm = ( x1 + x2 ) / 2.0;

      float ym = ( y1 + y2 ) / 2.0;

      //normal equation at midpoint of line
      Line_Eq n_e { ( x2 - x1 ), ( y2 - y1 ), {xm, ym} };

      return ( sqrd_dist_pt_ln( curr_pos, n_e ) <=
            square_float( ym - y1 ) + square_float( xm - x1 ) );
   }
}

void Physics::collide_ball_line( Ball& ball, const Line_Object& line_o )
{
   if( is_colliding_bl( ball, line_o.line ) )
   {
      switch( line_o.get_type() )
      {
         case edge:

            ball.bounce( line_o.line.get_line_angle() );
            
            break;

         case goal:

            //Insert goal code here
            break;

         case paddle:

            //Insert paddle code here
            break;
      }
   }
   else 
   {
      collide_ball_point( ball, line_o.line.get_p1() );

      collide_ball_point( ball, line_o.line.get_p2() );
   }
}

void Physics::collide_balls( Ball& ball1, Ball& ball2 )
{
   int dy = ball1.get_position().y - ball2.get_position().y;

   int dx = ball1.get_position().x - ball2.get_position().x;

   if( square_int( dx ) + square_int( dy ) <=
         square_int( ball1.get_radius() + ball2.get_radius() ) )
   {
      //bounce off perpendicular to line joining centres of b1 and b2
      float normal_angle = 
         ( atan2f( static_cast<float>( dy ), static_cast<float>( dx ) )
           + this_pi / 2.0 ); 

      ball1.bounce( normal_angle );

      ball2.bounce( normal_angle );
   }
}

float Physics::sqrd_dist_pt_ln( struct positionf pos, Line_Eq line )
{
   float ax_by_c = line.a * ( pos.x - line.p.x ) + 
      line.b * ( pos.y - line.p.y );

   return square_float( ax_by_c ) / ( line.a*line.a + line.b*line.b );
}
