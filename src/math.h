/**
 * @file math.h
 * @brief Useful math functions.
 *
 */

#ifndef MATH_H
#define MATH_H

#include <stdint.h>

/** approximate value of pi */
#define M_PI 3.14159265359f

/** approximate value of pi / 180 */
#define DEG_TO_RAD 0.01745329251f

/** approximate value of 180 / pi */
#define RAD_TO_DEG 57.2957795131f

/** returns 1 or -1 depending on the sign of x */
#define SIGN(x) (((x) >= 0) - ((x) < 0))

/** @cond */
extern float (*sin)(float x);
extern float (*cos)(float x);
extern float (*tan)(float x);
extern float (*fabs)(float x);

#if 0
/// @endcond

/**
 * @brief Returns the sine @p x radians.
 *
 * @param x - An angle expressed in radians.
 *
 * @return Sine of @p x radians.
 */
float sin(float x);

/**
 * @brief Returns the cosine @p x radians.
 *
 * @param x - An angle expressed in radians.
 *
 * @return Cosine of @p x radians.
 */
float cos(float x);

/**
 * @brief Returns the tangent @p x radians.
 *
 * @param x - An angle expressed in radians.
 *
 * @return Tangent of @p x radians.
 */
float tan(float x);

/**
 * @brief Returns the absolute value of @p x.
 *
 * @param x - A floating point number.
 *
 * @return The absolute value of @p x.
 */
float fabs(float x);

/** @cond */
#endif
/** @endcond */

/**
 * @brief Returns maximum value of array.
 *
 * @param ra[] - an array of 32-bit @c signed @c ints
 * 
 * @return The maximum value of @p ra[]
 */
int32_t imax_array(int32_t ra[]);

/**
 * @brief Returns minimum value of array.
 *
 * @param ra[] - an array of 32-bit @c signed @c ints
 * 
 * @return The minimum value of @p ra[]
 */
int32_t imin_array(int32_t ra[]);

/**
 * @brief Returns the maximum of two numbers.
 *
 * @param a - 32-bit @c signed @c int
 * @param b - 32-bit @c signed @c int
 * 
 * @return The larger value of @p a and @p b.
 */
int32_t imax(int32_t a, int32_t b);

/**
 * @brief Returns the minimum of two numbers.
 *
 * @param a - 32-bit @c signed @c int
 * @param b - 32-bit @c signed @c int
 * 
 * @return The smaller value of @p a and @p b.
 */
int32_t imin(int32_t a, int32_t b);

/**
 * @brief Returns maximum value of array.
 *
 * @param ra[] - an array of @c floats
 * 
 * @return The maximum value of @p ra[]
 */
float fmax_array(float ra[]);

/**
 * @brief Returns minimum value of array.
 *
 * @param ra[] - an array of @c floats
 * 
 * @return The minimum value of @p ra[]
 */
float fmin_array(float ra[]);

/**
 * @brief Returns the maximum of two numbers.
 *
 * @param a - a floating point number
 * @param b - a floating point number
 * 
 * @return The larger value of @p a and @p b.
 */
float fmax(float a, float b);

/**
 * @brief Returns the minimum of two numbers.
 *
 * @param a - a floating point number
 * @param b - a floating point number
 * 
 * @return The smaller value of @p a and @p b.
 */
float fmin(float a, float b);

/**
 * @brief Returns @p base raised to the power of @p exp
 *
 * @param base - a 16-bit @c signed @c int
 * @param exp - an 8-bit @c signed @c int
 * 
 * @return @p base raised to the power of @p exp
 */
int32_t ipow(int16_t base, uint8_t exp);

/**
 * @brief Returns @p base raised to the power of @p exp
 *
 * @param base - a floating point number
 * @param exp - an 8-bit @c signed @c int
 * 
 * @return @p base raised to the power of @p exp
 */
float fpow(float base, uint8_t exp);

/**
 * @brief Returns the square root of @p x
 *
 * @param x - a floating poin number
 * 
 * @return the square root of @p x
 */
float sqrt(float x);

/**
 * @brief Struct containing the coordinates of a point 
 */
typedef struct point
{
    float x; /**< X-coordinate of point */
    float y; /**< Y-coordinate of point */

} Point;

/**
 * @brief Compute arc tangent with two parameters 
 * 
 * Returns the arc tangent of @p y / @p x, expressed in radians. To 
 * compute the value, the function takes into accout the sign of
 * both arguments in order to determine the quadrant. 
 *
 * @param y - Y-coordinate relative to (0,0)
 * @param x - X-coordinate relative to (0,0)
 *
 * @return arc tangent of @p y / @p x, in interval [-pi, +pi] radians
 *
 * @see http://www.cplusplus.com/reference/cmath/atan2/
 */
float atan2(float y, float x);

/**
 * @brief Returns the magnitude of @p pt (i.e. distance from (0,0)
 *
 * @param pt - A Point struct
 *
 * @return The distance of @p pt from (0,0)
 *
 * @note error is within 0.26 degrees or 0.0045 radians
 */
float magnitude(Point pt);

/**
 * @brief Returns the distance between two points.
 *
 * @param a - A Point struct
 * @param b - A Point struct
 *
 * @return The distance between @p a and @p b
 */
float distance(Point a, Point b);

/**
 * @brief Returns the angle between two points.
 *
 * @param a - A Point struct
 * @param b - A Point struct
 *
 * @return The angle between @p a and @p b
 */
float angle(Point a, Point b);

#endif
