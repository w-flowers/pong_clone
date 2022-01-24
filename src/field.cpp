
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

   min_x.x -= static_cast<double>( ball.get_radius() );

   positiond max_x = ball.get_position();

   max_x.x += static_cast<double>( ball.get_radius() );

   positiond min_y = ball.get_position();

   min_y.y -= static_cast<double>( ball.get_radius() );

   positiond max_y = ball.get_position();

   max_y.y += static_cast<double>( ball.get_radius() );

   std::vector<int> ball_squares {};

   ball_squares.reserve(32);

   int current_row {0};

   find_squares_of_point( min_y, ball_squares );

   // Find first row of grid vertices under min_y

   for( int i : ball_squares )
   {
      int curr_y = i / num_cols;

      current_row = ( current_row < curr_y ) ? curr_y : current_row;
   }

   current_row++;

   int end_row = num_cols;

   int end_of_min_y_squares = ball_squares.size();

   find_squares_of_point( max_y, ball_squares );

   for( int i = end_of_min_y_squares; i < ball_squares.size(); i++ )
   {
      int curr_y = ball_squares.at(i) / num_cols;

      end_row = ( end_row > curr_y ) ? curr_y : end_row;
   }

   // Find all the indexes of squares contacting the circle
   //
   // Dump them all into ball_squares
   //
   // That's what this for loop does

   for( int i = current_row; i <= end_row; i++ )
   {
      double curr_y_pos = 
         static_cast<double>( field_sqrs.at( num_cols * i ).pos.y );
/*
      // The following index is the index of the rightmost left-side column in
      // ball_squares
      int curr_min_col = 0;

      // The same but on the right
      int curr_max_col = num_cols;
*/
      double curr_min_x = ball.get_position().x
         - sqrt( square_d( static_cast<double>( ball.get_radius() ) )
               - square_d( curr_y_pos - ball.get_position().y ) );

      double curr_max_x = ball.get_position().x
         + sqrt( square_d( static_cast<double>( ball.get_radius() ) )
               - square_d( curr_y_pos - ball.get_position().y ) );

      //int size_before = ball_squares.size();

      find_squares_of_point( { curr_min_x, curr_y_pos }, ball_squares );

      //int size_after = ball_squares.size();
/*
      if( size_after - size_before == 1 )
      {
         curr_min_col = ball_squares.at( size_after - 1 ) % num_cols;
      }

      else
      {
         for( int j = size_after - 1; j >= size_before; j-- )
         {
            int curr_col = ball_squares.at(j) % num_cols;

            curr_min_col = ( curr_min_col < curr_col ) ? curr_col : curr_min_col;
         }

      }
*/
      //size_before = size_after;

      find_squares_of_point( { curr_max_x, curr_y_pos }, ball_squares );

      //size_after = ball_squares.size();
/*
      if( size_after - size_before == 1 )
      {
         curr_max_col = ball_squares.at( size_after - 1 ) % num_cols;
      }

      else
      {
         for( int j = size_after - 1; j >= size_before; j-- )
         {
            int curr_col = ball_squares.at(j) % num_cols;

            curr_max_col = ( curr_max_col > curr_col ) ? curr_col : curr_max_col;
         }
      }

      for( int j = curr_min_col + 1; j < curr_max_col; j++ )
      {
         ball_squares.push_back( i * num_cols + j );

         if( i == current_row )
         {
            ball_squares.push_back( ( i - 1 ) * num_cols + j );
         }
      }
      */
   }

   find_squares_of_point( max_x, ball_squares );

   find_squares_of_point( min_x, ball_squares );

   // Add the balls to the squares with the given indices

   for( int i : ball_squares )
   {
      if( field_sqrs[i].balls.empty() )
      {
         field_sqrs[i].balls.push_back( &ball );
      }

      else if( field_sqrs[i].balls.back() != &ball )
      {
         field_sqrs[i].balls.push_back( &ball );
      }
   }

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

void Field_Grid::assign_ball_to_squares_lazy( Ball& ball, int index )
{
   double r = static_cast<double>( ball.get_radius() );

   positiond p = ball.get_position();

   double min_x = p.x - r;

   double max_x = p.x + r;

   double min_y = p.y - r;

   double max_y = p.y + r;

   int min_row = num_rows - 1;

   int max_row = num_rows - 1;

   int min_col = num_cols - 1;

   int max_col = num_cols - 1;

   while( min_x < static_cast<double>( field_sqrs[min_col].pos.x ) )
   {
      min_col--;
   }

   if( min_x = field_sqrs[min_col].pos.x && min_col > 0 )
   {
      min_col--;
   }

   while( max_x < static_cast<double>( field_sqrs[max_col].pos.x ) )
   {
      max_col--;
   }

   while( min_y < static_cast<double>( field_sqrs[num_cols * min_row].pos.y ) )
   {
      min_row--;
   }

   if( min_y = field_sqrs[min_row * num_cols].pos.y && min_row > 0 )
   {
      min_row--;
   }

   while( max_y < static_cast<double>( field_sqrs[num_cols * max_row].pos.y ) )
   {
      max_row--;
   }

   for( int row = min_row; row <= max_row; row++ )
   {
      for( int col = min_col; col <= max_col; col++ )
      {
         field_sqrs[row * num_cols + col].balls.push_back( &ball );
      }
   }
}

bool Field_Grid::point_in_square( struct positiond p, Field_Square& f )
{
   return ( static_cast<double>( f.pos.x ) <= p.x &&
            static_cast<double>( f.pos.y ) <= p.y &&
            p.x <= static_cast<double>( f.pos.x + f.w ) &&
            p.y <= static_cast<double>( f.pos.y + f.h ) );
}

bool Field_Grid::point_in_column( struct positiond p, int col )
{
   return ( static_cast<double>( field_sqrs[col].pos.x ) <= p.x &&
            p.x <= static_cast<double>( field_sqrs[col].pos.x +
               field_sqrs[col].w ) );
}

bool Field_Grid::point_in_row( struct positiond p, int row )
{
   return ( static_cast<double>( field_sqrs[row*num_cols].pos.y ) <= p.y &&
            p.y <= static_cast<double>( field_sqrs[row*num_cols].pos.y +
               field_sqrs[row*num_cols].h ) );
}

void Field_Grid::find_squares_of_point( struct positiond p,
      std::vector<int>& indexes )
{
   //Horizontal search

   //std::vector<int> x_inds {};

   //std::vector<int> y_inds {};

   int x_inds[2] = {-1, -1};

   int y_inds[2] = {-1, -1};

   int x_ind = 0;

   int y_ind = 0;

   //int ub = num_cols - 1;

   //int lb = 0;

   int mid_x = 1;

   while( field_sqrs[mid_x].pos.x < p.x && mid_x < num_cols )
   {
      mid_x++;
   }

   mid_x--;
/*
   int mid = ( ub + lb ) / 2 ;

   while( !point_in_column( p, mid ) )
   {
      if( ub - lb == 1 )
      {
         mid = ( ub == mid ) ? lb : ub;

         break;
      }

      if( static_cast<double>( field_sqrs[ mid ].pos.x ) > p.x )
      {
         ub = mid;
      }

      else
      {
         lb = mid;
      }

      mid = ( ub + lb ) / 2;
   }
*/
   x_inds[0] = mid_x ;
/*
   if( p.x == static_cast<double>( field_sqrs[ mid ].pos.x ) )
   {
      x_inds.push_back( mid - 1 );
   }

   else if ( p.x == static_cast<double>( field_sqrs[ mid ].pos.x + 
           field_sqrs[ mid ].w ) )
   {
      x_inds.push_back( mid + 1 );
   }
*/
   // Vertical Search

   //ub = num_rows - 1;

   //lb = 0;

   //mid = ( ub + lb ) / 2 ;

   int mid_y = 1;

   while( field_sqrs[mid_y*num_cols].pos.y < p.y && mid_y < num_rows )
   {
      mid_y++;
   }

   mid_y--;
/*
   while( !point_in_row( p, mid ) )
   {
      if( ub - lb == 1 )
      {
         mid = ( ub == mid ) ? lb : ub;

         break;
      }

      if( static_cast<double>( field_sqrs[ mid * num_cols ].pos.y ) > p.y )
      {
         ub = mid;
      }

      else
      {
         lb = mid;
      }

      mid = ( ub + lb ) / 2;
   }
*/
   y_inds[0] = mid_y;
/*
   if( p.y == static_cast<double>( field_sqrs[ num_cols * mid ].pos.y ) )
   {
      y_inds.push_back( mid - 1 );
   }

   else if ( p.y == static_cast<double>( field_sqrs[ num_cols * mid ].pos.y +
           field_sqrs[ num_cols * mid ].h ) )
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
   */

   if ( p.x == static_cast<double>( field_sqrs[ mid_x ].pos.x + 
            field_sqrs[ mid_x ].w ) )
   {
      x_inds[1] = mid_x + 1;
   }

   if ( p.y == static_cast<double>( field_sqrs[ num_cols * mid_y ].pos.y +
           field_sqrs[ num_cols * mid_y ].h ) )
   {
      y_inds[1] =  mid_y + 1;
   }


   for( int i = 0; i < 4; i++ )
   {
      if( x_inds[i%2] >= 0 && y_inds[i/2] >= 0 )
      {
         indexes.push_back( num_cols * y_inds[i/2] + x_inds[i%2] );
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
   for( auto& sqr : field_sqrs )
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
      const std::vector<Ball_Args>& ball_init_list, int x_d, int y_d,
      int rows, int columns):
    boundary {boun_init_list}, x_dim {x_d}, y_dim {y_d}
{
   if( x_dim <= 0 || y_dim <= 0 )
   {
      throw InvalidDimensions{};
   }

   for( auto arg : ball_init_list )
   {
      ball_vec.emplace_back( Ball( arg.r, arg.init_x, arg.init_y, arg.speed) );
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

      if( b.get_position().x <= 0 ||
            b.get_position().x >= x_dim ||
            b.get_position().y <= 0 ||
            b.get_position().y >= y_dim )
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

void Field::write_field_positions( struct field_position_data& fpd )
{
   fpd.ball_positions.clear();

   fpd.line_positions.clear();

   for( Ball& b : ball_vec )
   {
      fpd.ball_positions.push_back(
            { round( b.get_position().x ),
            round( b.get_position().y ),
            b.get_radius() } );
   }


   for( int i = 0; i < boundary.get_lines_size(); i++ )
   {
      fpd.line_positions.push_back(
            { boundary.get_line( i ).line.get_p1(),
            boundary.get_line( i ).line.get_p2(),
            boundary.get_line( i ).get_type() } );
   }
}

