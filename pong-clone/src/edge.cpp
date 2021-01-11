/******************************************************************************
 * Edge - a class defining the basic edges used in game
 *
 * All units an integer number of pixels. Edge angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up
 *****************************************************************************/

class Edge
{
public:
   Edge(int x1_, int y1_, int x2_, int y2_);

private:
   int x1;

   int y1;

   int x2;

   int y2;

   float edge_angle;
}

Edge::Edge(int x1_, int y1_, int x2_, int y2_):
   x1{x1_}, y1{y1_}, x2{x2_}, y2{y2_}
{
   edge_angle = atan2f( ( (float) (y2 - y1) ), ( (float) (x2 - x1) ) );
}

