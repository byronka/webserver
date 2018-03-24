/*
   This enum represents the sizes we support.  UNKNOWN means we
   have been given a waist size that doesn't fit into our
   set of possible sizes 
*/
typedef enum { SMALL, MEDIUM, LARGE, XLARGE, UNKNOWN } pant_size;

/*
   calculate size is where the rubber meets the road.  Provide it a
   waist size as an int, and it will give you a pants-size
*/
pant_size calculate_size (int waist_size);
