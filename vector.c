/* vector.c: vector/point operations. */

#include "usefull.h"
#include "vector.h"
#include "message.h"
#include "epsilon-equal.h"
#include <math.h>
#include <errno.h>

static const real acos_d (real);

#ifndef M_PI
#define M_PI 3.14159265
#endif

/* Given the point COORD, return the corresponding vector.  */

vector_type
make_vector (const real_coordinate_type c)
{
  vector_type v;

  v.dx = c.x;
  v.dy = c.y;

  return v;
}


/* And the converse: given a vector, return the corresponding point.  */

real_coordinate_type
vector_to_point (const vector_type v)
{
  real_coordinate_type coord;

  coord.x = v.dx;
  coord.y = v.dy;

  return coord;
}


const real
magnitude (const vector_type v)
{
  return hypot (v.dx, v.dy);
}


vector_type
normalize (const vector_type v)
{
  vector_type new_v;
  real m = magnitude (v);

  MYASSERT (m > 0.0);

  new_v.dx = v.dx / m;
  new_v.dy = v.dy / m;

  return new_v;
}


vector_type
Vadd (const vector_type v1, const vector_type v2)
{
  vector_type new_v;

  new_v.dx = v1.dx + v2.dx;
  new_v.dy = v1.dy + v2.dy;

  return new_v;
}


const real
Vdot (const vector_type v1, const vector_type v2)
{
  return v1.dx * v2.dx + v1.dy * v2.dy;
}


vector_type
Vmult_scalar (const vector_type v, const real r)
{
  vector_type new_v;

  new_v.dx = v.dx * r;
  new_v.dy = v.dy * r;

  return new_v;
}


/* Given the IN_VECTOR and OUT_VECTOR, return the angle between them in
   degrees, in the range zero to 180.  */

const real
Vangle (const vector_type in_vector, const vector_type out_vector)
{
  vector_type v1 = normalize (in_vector);
  vector_type v2 = normalize (out_vector);

  return acos_d (Vdot (v2, v1));
}


real_coordinate_type
Vadd_point (const real_coordinate_type c, const vector_type v)
{
  real_coordinate_type new_c;

  new_c.x = c.x + v.dx;
  new_c.y = c.y + v.dy;
  return new_c;
}


real_coordinate_type
Vsubtract_point (const real_coordinate_type c, const vector_type v)
{
  real_coordinate_type new_c;

  new_c.x = c.x - v.dx;
  new_c.y = c.y - v.dy;
  return new_c;
}


coordinate_type
Vadd_int_point (const coordinate_type c, const vector_type v)
{
  coordinate_type a;

  a.x = ROUND ((real) c.x + v.dx);
  a.y = ROUND ((real) c.y + v.dy);
  return a;
}


vector_type
Vabs (const vector_type v)
{
  vector_type new_v;

  new_v.dx = fabs (v.dx);
  new_v.dy = fabs (v.dy);
  return new_v;
}


/* Operations on points.  */

real_coordinate_type
Padd (const real_coordinate_type coord1, const real_coordinate_type coord2)
{
  real_coordinate_type sum;

  sum.x = coord1.x + coord2.x;
  sum.y = coord1.y + coord2.y;

  return sum;
}


real_coordinate_type
Pmult_scalar (const real_coordinate_type coord, const real r)
{
  real_coordinate_type answer;

  answer.x = coord.x * r;
  answer.y = coord.y * r;

  return answer;
}


vector_type
Psubtract (const real_coordinate_type c1, const real_coordinate_type c2)
{
  vector_type v;

  v.dx = c1.x - c2.x;
  v.dy = c1.y - c2.y;

  return v;
}



/* Operations on integer points.  */

vector_type
IPsubtract (const coordinate_type coord1, const coordinate_type coord2)
{
  vector_type v;

  v.dx = (real) (coord1.x - coord2.x);
  v.dy = (real) (coord1.y - coord2.y);

  return v;
}


coordinate_type
IPsubtractP (const coordinate_type c1, const coordinate_type c2)
{
  coordinate_type c;

  c.x = c1.x - c2.x;
  c.y = c1.y - c2.y;

  return c;
}


coordinate_type
IPadd (const coordinate_type c1, const coordinate_type c2)
{
  coordinate_type c;

  c.x = c1.x + c2.x;
  c.y = c1.y + c2.y;

  return c;
}


coordinate_type
IPmult_scalar (const coordinate_type c, const int i)
{
  coordinate_type a;

  a.x = c.x * i;
  a.y = c.y * i;

  return a;
}


real_coordinate_type
IPmult_real (const coordinate_type c, const real r)
{
  real_coordinate_type a;

  a.x = c.x * r;
  a.y = c.y * r;

  return a;
}


const boolean
IPequal (const coordinate_type c1, const coordinate_type c2)
{
  return ((c1.x == c2.x) && (c1.y == c2.y));
}

static const real
acos_d (real v)
{
  real a;

  if (epsilon_equal (v, 1.0))
    v = 1.0;
  else if (epsilon_equal (v, -1.0))
    v = -1.0;

  errno = 0;
  a = acos (v);
  if (errno == ERANGE || errno == EDOM)
    FATAL_PERROR ("acosd");

  return a * 180.0 / M_PI;
}

/* version 0.24 */
