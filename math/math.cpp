#include <cmath>
#include <iostream>

using namespace std;

/* sum_to: returns the sum of numbers from 1-n
 * sum of numbers from 1-n is given by (n)(n+1)/2
 */
int sum_to(int n){
    return (n) * (1 + n) / 2;
}

/* sum_of_squares: returns the sum of squares from 1-n
 * sum of squares from 1-n is (n)(n+1)(2n+1)/6
 */
int sum_of_squares(int n){
    return n * (n + 1) * (2 * n + 1) / 6;
}

/* sum_of_cubes: returns the sum of cubes from 1-n
 * the sum of cubes from 1-n is the square of the sum from 1-n
 */
int sum_of_cubes(int n){
    int sum = n * (n + 1) / 2;
    return sum * sum;
}

/* fast_exp: returns base raised to the exponent power
 * recursive fast exponentiation algorithm:
 *     if exponent is 0 --> return 1
 *     if exponent is 1 --> return base
 *     if exponent is even --> return (base ^ (exponent / 2))^2
 *     if exponent is odd --> return base * (base ^ (exponent / 2))^2
 */
int fast_exp(int base, int exponent){
    if (exponent == 0) { return 1; }
    if (exponent == 1) { return base; }

    // note we can truncate the two cases since integral division takes care of
    // decimals
    int tmp = fast_exp(base, exponent / 2);
    return tmp * tmp * fast_exp(base, exponent % 2);
}

// TODO Mateix Stuff :3 I need to git gud at linear algebra first

/* gcd: finds the greatest common factor of a and b
 * repeated application of Euclidean's Algo: gcd(a, b) = gcd(a, b - n * a)
 */
int gcd(int a, int b){
    if (a > b) { return gcd(b, a); }
    if (a == 0) { return b; }
    return gcd(a, b % a);
}

/* lcm: finds the least common multiple of a and b
 * least common multiple of two numbers is the product of the two numbers
 * divided by their greatest common factor
 */
int lcm(int a, int b){
    return a / gcd(a, b) * b;
}

/* egcd: extended euclidean algorithm
 * returns the gcd of a and b, but also keeps the coefficient x, y such that ax
 * + by = gcd(a, b)
 */
int egcd(int a, int b, int &x, int &y) {

    if (a > b) { return egcd(b, a, y, x); }

    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    // let b = an + c, then we have
    // ax + (an + c)y = g
    // a(x + ny) + cy = g
    int x1, y1, g = egcd(b % a, a, x1, y1);
    y = x1;
    x = y1 - x1 * (b / a);
    return g;
}

/* mod_inv: returns the multiplicative inverse of a mod n, returns -1 if
 * non-existent
 * we use the extended euclidean algorithm on a and n, if ax + ny = 1, we know
 * ax is congruent to 1 mod n
 */
int mod_inv(int a, int n){
    int x, y, g = egcd(a, n, x, y);

    if (g != 1) { // a and n must be co-prime
        return -1;
    }
    else {
        return x;
    }
}

