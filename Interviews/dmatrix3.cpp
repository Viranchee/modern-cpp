/* A hill range is represented with an MxN matrix. To the north and to the west
 * of it lies lake Huron, to the south and to the east -- lake Erie. Each cell
 * in the matrix contains a positive number representing elevation at a
 * particular coordinate. Each cell can receive rain water. From one cell, rain
 * water can only flow in four directions, and it can only flow downwards or on
 * the same level. Return a list of coordinates from which rain water can reach
 * both of the lakes.
 *
 * Input:
 * {  // Huron
 *  H {1, 1, 2, 2, 5}, // E
 *  U {2, 1, 3, 4, 4}, // R
 *  R {1, 4, 5, 2, 2}, // I
 *  O {7, 8, 2, 3, 4}, // E
 *  N {5, 2, 1, 3, 3}  // !
 *    // Erie
 * }
 *
 * Output:
 * {{4, 0}, {3, 0}, {3, 1}, {2, 2}, {1, 3}, {1, 4}, {0, 4}}
 */

#include <iostream>
using namespace std;

// Trapping Rainwater 2D

vector<vector<int>> bothLakes(vector<vector<int>> &elevationAt) {
  // canGoHuron = set()
  // canGoErie = set()

  // canGo = [:]
  // magic algo

  // return canGoHuron Intersection canGoErie
}

int main() { return 0; }
