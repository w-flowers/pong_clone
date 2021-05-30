
/********************************************************************************
* Pong Clone - Field (field.cpp) 
*
* DESCRIPTION
*
* Author: William Flowers
********************************************************************************/

#include "../inc/field.hpp"

Field_Grid::Field_Grid( std::vector<Ball>& balls, Boundary& boundary, 
      int field_x_dim, int field_y_dim, int rows, int columns )
   : num_rows {rows}, num_cols {columns}, field_sqrs {} 
{
   field_sqrs.reserve( num_rows * num_cols );

   //INSERT code to initialise field squares
   int remaining_height = field_y_dim;

   int remaining_width = field_x_dim;

   int current_x = 0;

   int current_y = 0;

   int new_h = 0;

   int new_w = 0;

   for( int i = 0; i < num_rows * num_cols ; i++ )
   {
      if( !( i % num_cols ) )
      {
         current_x = 0;

         current_y += new_h;

         new_h = remaining_height / (num_rows - i / num_rows );

         remaining_height -= new_h;

         remaining_width = field_x_dim;
      }

      new_w = remaining_width / ( num_cols - i % num_cols );

      remaining_width -= new_w;

      field_sqrs.emplace_back( Field_Square() );

      field_sqrs.back().pos = {current_x, current_y};

      field_sqrs.back().w = new_w;

      field_sqrs.back().h = new_h;

      current_x += new_w;
   }

   for( Ball& ball : balls)
   {
      assign_ball_to_squares( ball );
   }

   for( int i = 0; i < boundary.get_lines_size(); i++ )
   {
      assign_line_to_squares( boundary.get_line( i ) );
   }
   //insert similar things for paddles once implemented
}

void Field_Grid::assign_ball_to_squares( Ball& ball )
{
   positiond min_x = ball.get_position();

   min_x.x -= static_cast<float>( ball.get_radius() );

   positiond max_x = ball.get_position();

   max_x.x += static_cast<float>( ball.get_radius() );

   positiond min_y = ball.get_position();

   min_y.y -= static_cast<float>( ball.get_radius() );

   positiond max_y = ball.get_position();

   max_y.y += static_cast<float>( ball.get_radius() );

   std::vector<int> ball_squares {};

   ball_squares.reserve(32);


   /* OLD ALGORITHM
   struct positiond ball_p = ball.get_position();
   
   std::vector<int> cols {};

   // Check if line is within radius of vert dividers
   for( int i = 1; i < num_cols; i++ )
   {
      if( abs( ball_p.x - static_cast<double>( field_sqrs[i].pos.x ) ) <= 
            static_cast<double>( ball.get_radius() ) )
      {
         cols.push_back( i - 1 );

         cols.push_back( i );

         break;
      }
   }
   
   // Find unique column containing ball centre if it isn't on divider
   if( cols.empty() )
   {
      for( int i = 0; i < num_cols; i++ )
      {
         if( ball_p.x < 
               static_cast<double>( field_sqrs[i].pos.x + field_sqrs[i].w ) )
         {
            cols.push_back( i );

            break;
         }
      }
   }

   std::vector<int> rows {};

   // Check if line is within radius of horizontal dividers
   for( int i = 1; i < num_rows; i++ )
   {
      if( abs( ball_p.y - static_cast<double>( field_sqrs[num_cols*i].pos.y ) ) 
            <= static_cast<double>( ball.get_radius() ) )
      {
         rows.push_back( i - 1 );

         rows.push_back( i );

         break;
      }
   }

   // Find unique row containing ball centre if it isn't on divider
   if( rows.empty() )
   {
      for( int i = 0; i < num_rows; i++ )
      {
         if( ball_p.y < 
               static_cast<double>( field_sqrs[num_cols*i].pos.y + 
                  field_sqrs[num_cols*i].h )
               )
         {
            rows.push_back( i );

            break;
         }
      }
   }

   // This section exists to determine if a ball is in all four squares or only
   // three squares. Relies on fact that cols[0] is less than cols[1].
   if( cols.size() == 2 && rows.size() == 2 )
   {
      //find row and column of square diagonal to ball
      int d_row = 0;

      int d_col = 0;

      double mid_x = static_cast<double>(
            field_sqrs[ cols[0] ].pos.x + field_sqrs[ cols[0] ].w );

      double mid_y = static_cast<double>( field_sqrs[ num_cols * rows[0] ].pos.y
         + field_sqrs[ num_cols * rows[0] ].h );

      if( ball_p.x < mid_x )
      {
         d_col = cols[1];
      }
      else
      {
         d_col = cols[0];
      }
      if( ball_p.y < mid_y )
      {
         d_row = rows[1];
      }
      else
      {
         d_row = rows[0];
      }

      struct positiond middle_corner = { static_cast<double>( 
            field_sqrs[ cols[1] + num_cols * rows[1] ].pos.x ),
                       static_cast<double>( 
                             field_sqrs[ cols[1] + num_cols * rows[1] ].pos.y )
      };

      // Distance from centre is less than or equal to ball radius
      // Means ball is in fourth square
      if( square_d( ball_p.x - middle_corner.x ) 
            + square_d( ball_p.y - middle_corner.y )
            <= square_d( static_cast<double>( ball.get_radius() ) ) )
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
   */
}

bool Field_Grid::point_in_square( struct positionf p, Field_Square& f )
{
   return ( static_cast<float>( f.pos.x ) <= p.x &&
            static_cast<float>( f.pos.y ) <= p.y &&
            p.x <= static_cast<float>( f.pos.x + f.w ) &&
            p.y <= static_cast<float>( f.pos.y + f.h ) );
}

void Field_Grid::find_squares_of_point( struct positionf p,
      std::vector<int> indexes )
{
   //Horizontal search

   std::vector<int> x_inds {};

   std::vector<int> y_inds {};

   int ub = num_cols;

   int lb = 0;

   int mid = ( ub + lb ) / 2 ;

   while( !point_in_square( p, field_sqrs.at( mid ) ) )
   {
      if( static_cast<float( field_sqrs.at( mid ).pos.x ) > p.x )
      {
         ub = mid;
      }

      else
      {
         lb = mid + 1;
      }

      mid = ( ub + lb ) / 2;
   }

   x_inds.push_back( mid );

   if( p.x == static_cast<float>( field_sqrs.at( mid ).pos.x ) )
   {
      x_inds.push_back( mid - 1 );
   }

   else if ( p.x == static_cast<float>( field_sqrs.at( mid ).pos.x + 
           field_sqrs.at( mid ).w ) )
   {
      x_inds.push_back( mid + 1 );
   }

   // Vertical Search

   int ub = num_rows;

   int lb = 0;

   int mid = ( ub + lb ) / 2 ;

   while( !point_in_square( p, field_sqrs.at( mid * num_cols ) ) )
   {
      if( static_cast<float>( field_sqrs.at( mid * num_cols ).pos.y ) > p.y )
      {
         ub = mid;
      }

      else
      {
         lb = mid + 1;
      }

      mid = ( ub + lb ) / 2;
   }

   y_inds.push_back( mid );

   if( p.y == static_cast<float>( field_sqrs.at( num_cols * mid ).pos.y ) )
   {
      y_inds.push_back( mid - 1 );
   }

   else if ( p.y == static_cast<float>( field_sqrs.at( num_cols * mid ).pos.y +
           field_sqrs.at( num_cols * mid ).h ) )
   {
      y_inds.push_back( mid + 1 );
   }

   for( int x_ind : x_inds )
   {
      for( int y_ind : y_inds )
      {
         indexes.push_back( num_cols * y_ind + x_ind );
      }
   }
}

void Field_Grid::assign_line_to_squares( Line_Object& line)
{
   struct positiond lp1 = {
      static_cast<double>( line.line.get_p1().x ),
      static_cast<double>( line.line.get_p1().y )
   };
   
   struct positiond lp2 = {
      static_cast<double>( line.line.get_p2().x ),
      static_cast<double>( line.line.get_p2().y )
   };

   // Ensure that lp1 is to the left of lp2 in x, and closer to top if equal
   if( lp1.x > lp2.x || ( lp1.x == lp2.x && lp1.y > lp2.y ) )
   {
      struct positiond dummy = lp2;

      lp2 = lp1;

      lp1 = dummy;
   }

   std::vector<struct positiond> crossing_pts { lp1 };

   Line_Eq l_e { ( lp1.y - lp2.y ), ( lp2.x - lp1.x ),
      { ( lp1.x ), (lp1.y ) } };

   // Find points where line changes columns
   for( int i = 0; i < num_cols; i++ )
   {
      if( lp1.x == lp2.x ) break;
      
      while( static_cast<double>( field_sqrs[i].pos.x + field_sqrs[i].w ) <= lp1.x )
      {
        i++;

        if( i >= num_cols ) break;
      } 

      if( i >= num_cols ) break;

      double v_intcpt = static_cast<double>( field_sqrs[i].pos.x + field_sqrs[i].w );

      if( v_intcpt >= lp2.x || approx_equal_anglesd( v_intcpt, lp2.x )) break;

      else
      {
         crossing_pts.push_back({v_intcpt, 
               ( ( (-l_e.a) / (l_e.b) ) * (v_intcpt - l_e.p.x) + l_e.p.y ) }
              );
      }
   }

   crossing_pts.push_back( lp2 );

   //At this point, crossing points is sorted by x, ascending

   double y_min = ( lp1.y < lp2.y ) ? lp1.y: lp2.y;

   double y_max = ( lp1.y > lp2.y ) ? lp1.y: lp2.y;

   // Find where line crosses into new row  if distinct from existing crossings
   for( int i = 0; i < num_rows; i++ )
   {
      if( lp1.y == lp2.y ) break;
      
      while( static_cast<double>( field_sqrs[num_cols*i].pos.y 
               + field_sqrs[num_cols*i].h ) 
            <= y_min )
      {
        i++;

        if( i >= num_rows ) break;
      } 

      if( i >= num_rows ) break;

      double h_intcpt = static_cast<double>( 
            field_sqrs[num_cols*i].pos.y + field_sqrs[num_cols*i].h );

      if( h_intcpt >= y_max ) 
      {
         break;
      }

      else
      {
         double new_x = ( (- l_e.b) / (l_e.a) * (h_intcpt - l_e.p.y) + l_e.p.x );

         for( int i = 1; i < crossing_pts.size(); i++ )
         {
            // Note: last element acts as a sentinal for this condition
            if( crossing_pts[i].x > new_x )
            {
               auto new_It = crossing_pts.begin() + i;

               crossing_pts.insert( new_It, {new_x, h_intcpt} );

               break;
            }
            else if( approx_equal_anglesd( new_x, crossing_pts[i].x ) )
            {
               break;
            }
         }
      }
   }

   // Find midpoints of crossing points and use to find which squares line is
   // contained in.
   for( int i = 1; i < crossing_pts.size(); i++ )
   {
      struct positiond midpoint = 
      { ( crossing_pts[i-1].x + crossing_pts[i].x ) / 2.0, 
         ( crossing_pts[i-1].y + crossing_pts[i].y ) / 2.0 };

      int mp_row = 0;

      int mp_col = 0;

      for( int i = 0; i < num_rows; i++ )
      {
         if( midpoint.y 
               <= static_cast<double>( field_sqrs[ num_cols * i ].pos.y 
                  + field_sqrs[ num_cols * i ].h ) )
         {
            mp_row = i;

            break;
         }
      }

      for( int i = 0; i < num_cols; i++ )
      {
         if( midpoint.x <= 
               static_cast<double>( 
                  field_sqrs[ i ].pos.x + field_sqrs[ i ].w ) )
         {
            mp_col = i;

            break;
         }
      }

      field_sqrs[ mp_col + num_cols * mp_row].edges.push_back( &line );
   }
}

void Field_Grid::clear_balls()
{
   for( int i = 0; i < num_rows*num_cols; i++ )
   {
      field_sqrs.at(i).balls.clear();
   }

   return;
}

void Field_Grid::return_objects_to_collide( 
      std::unordered_map< Ball*, std::set< Ball* > >& balls_to_collide,
      std::unordered_map< Ball*, std::set< Line_Object* > >& lines_to_collide,
      std::vector< Ball >& ball_vec //Owner of Balls
      )
{
   // Add objects in each square to ordered map if they don't already exist
   for( auto sqr : field_sqrs )
   {
      for( int i = 0; i < sqr.balls.size(); i++ )
      {
         for( int j = i + 1; j < sqr.balls.size(); j++ )
         {
            balls_to_collide.at( sqr.balls.at(i) ).insert( sqr.balls.at(j) );
         }

         for( int j = 0; j < sqr.edges.size(); j++ )
         {
            lines_to_collide.at( sqr.balls.at(i) ).insert( sqr.edges.at(j) );
         }
      }
   }

   // Delete duplicate pairs from map
   for( Ball& ref_ball : ball_vec )
   {
      for( auto ball_p : balls_to_collide.at( &ref_ball ) )
      {
         balls_to_collide.at( ball_p ).erase( &ref_ball );
      }
   }

   return;
}

Field::Field( const std::vector<Line_start>& boun_init_list,
      const std::vector<BallArgs>& ball_init_list, int x_d, int y_d,
      int rows, int columns):
    boundary {boun_init_list}, x_dim {x_d}, y_dim {y_d}
{
   if( x_dim <= 0 || y_dim <= 0 )
   {
      throw InvalidDimensions{};
   }

   for( auto arg : ball_init_list )
   {
      ball_vec.emplace_back( Ball( arg.radius, arg.init_x, arg.init_y, arg.speed) );
   }

   field_grid = { ball_vec, boundary, x_dim, y_dim, rows, columns };

   balls_to_collide = {};

   lines_to_collide = {};

   points_to_collide = {};

   for( Ball& b : ball_vec )
   {
      balls_to_collide.insert( { &b, {} } );

      lines_to_collide.insert( { &b, {} } );

      points_to_collide.insert( { &b, {} } );
   }
}

Ball& Field::get_ball( int index )
{
   return ball_vec.at( index );
}

int Field::ball_vec_size()
{
   return ball_vec.size();
}

int Field::get_x_dim() const
{
   return x_dim;
}

int Field::get_y_dim() const
{
   return y_dim;
}

//Below needs to be modified to accept paddle methods
void Field::advance_field()
{
   field_grid.return_objects_to_collide( balls_to_collide, lines_to_collide,
         ball_vec);

   for( Ball& b : ball_vec )
   {
      for( auto ball_p : balls_to_collide.at( &b ) )
      {
         Physics::collide_balls( b, *ball_p );
      }

      for( auto edge_p : lines_to_collide.at( &b ) )
      {
         Physics::collide_ball_line( b, *edge_p, points_to_collide );
      }

      for( auto point : points_to_collide.at( &b ) )
      {
         Physics::collide_ball_point( b, point );
      }
   }

   field_grid.clear_balls();

   for( Ball& b : ball_vec )
   {
      b.move();

      if( b.get_position().x < 0 || b.get_position().x > x_dim ||
            b.get_position().y < 0 || b.get_position().y > y_dim )
      {
         b.reset();

         std::cout << "Ball went out of bounds!!!\n";
      }

      field_grid.assign_ball_to_squares( b );

      balls_to_collide.at( &b ).clear();

      lines_to_collide.at( &b ).clear();

      points_to_collide.at( &b ).clear();
   }
}

