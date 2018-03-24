/*
   This enum represents the sizes we support.  UNKNOWN means we
   have been given a waist size that doesn't fit into our
   set of possible sizes 
*/
typedef enum { PANT_SMALL, PANT_MEDIUM, PANT_LARGE, PANT_XLARGE, PANT_UNKNOWN } pant_size;

/*
   This enum represents the sizes we support.  UNKNOWN means we
   have been given a waist size that doesn't fit into our
   set of possible sizes 
*/
typedef enum { SHIRT_SMALL, SHIRT_MEDIUM, SHIRT_LARGE, SHIRT_XLARGE, SHIRT_UNKNOWN } shirt_size;

/*
   calculate size is where the rubber meets the road.  Provide it a
   waist size as an int, and it will give you a pants-size
*/
pant_size calculate_pant_size (int waist_size);

/*
   calculate size is where the rubber meets the road.  Provide it a
   body size as an int, and it will give you a shirt-size
*/
shirt_size calculate_shirt_size (int body_size);
