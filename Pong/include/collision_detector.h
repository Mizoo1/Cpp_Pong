// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation
/**========================================================================
 * @file      collision.h
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *@brief     Collision detection using separating axis test.
 *           This method is using bounding boxes to check collision between two objects
 *           based on the Separating Axis Theorem (SAT). Two polygons are in collision
 *           when they are not separated.
 *           This is verfied by testing their projections on x, y, and z axes (in 3D) to
 *           find an axis where the objects are separated. If there is no separating axis,
 *           then the objects are colliding.
 *
 *           Collision Detector class is definited here for a structure that is used for
 *           a fast collision detection. This implementation is for 2D only as the 3D
 *           version is not need for this game.
 *
 *@see http://programmerart.weebly.com/separating-axis-theorem.html#:~:text=%E2%80%8BThe%20Separating%20Axis%20Theorem,is%20calculated%20in%20two%20dimensions.
 *========================================================================**/

#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
#include <array>

namespace myPong
{
  class CollisionDetector
  {
  public:
    CollisionDetector();

    bool collides(const CollisionDetector& other) const;
   /*
    * This function is used to check if the collision detector collides
    * with another collision detector passed as a parameter.
    * It returns true if the collision detector collides with
    * the other collision detector, and false otherwise.
    */

    const std::array<int, 2>& getCenter() const { return mCenter; }
    const std::array<int, 2>& getExtent() const { return mExtent; }
    /*
     * These functions are used to get the center and extent of the collision detector,
     * respectively. They return a reference to the mCenter and mExtent arrays.
     */

    void setCenter(const std::array<int, 2>& center) { mCenter = center; }
    void setExtent(const std::array<int, 2>& extent) { mExtent = extent; }
    /*
     * These functions are used to set the center and extent of the collision detector,
     * respectively. They take in an array of integers and set the mCenter
     * and mExtent arrays with those values.
     */

    int getCenterX() const { return mCenter[0]; }
    int getCenterY() const { return mCenter[1]; }
    int getExtentX() const { return mExtent[0]; }
    int getExtentY() const { return mExtent[1]; }
    /*
     * These functions are used to get the x and y values of the center
     * and extent of the collision detector, respectively.
     * They return the first and second element of the mCenter and mExtent arrays.
     */

    void setCenterX(int x) { mCenter[0] = x; }
    void setCenterY(int y) { mCenter[1] = y; }
    void setExtentX(int x) { mExtent[0] = x; }
    void setExtentY(int y) { mExtent[1] = y; }

  private:
    std::array<int, 2> mCenter;
    std::array<int, 2> mExtent;

  };

} //namespace myPong
#endif // COLLISION_DETECTOR_H
