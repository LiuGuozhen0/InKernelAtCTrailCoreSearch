//
//  myPositions.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef myPositions_hpp
#define myPositions_hpp

#include <iostream>

using namespace std;



/** Class containing the x, y, z coordinates of a bit. */
class myBitPosition {
public:
    /** The x-coordinate of the bit, 0 ≤ x < 5. */
    unsigned int x;
    /** The y-coordinate of the bit, 0 ≤ y < 5. */
    unsigned int y;
    /** The z-coordinate of the bit, 0 ≤ z < laneSize. */
    unsigned int z;
    /** The default constructor. */
    myBitPosition() : x(0), y(0), z(0) {}
    /** The constructor.
     * @param  ax  The x-coordinate.
     * @param  ay  The y-coordinate.
     * @param  az  The z-coordinate.
     */
    myBitPosition(unsigned int ax, unsigned int ay, unsigned int az);
    /** The copy constructor.
     * @param  aPoint  The bit position.
     */
    myBitPosition(const myBitPosition& aPoint);
    /** A display function, for use with the << operator.
     * @param  fout    The output stream to write to.
     * @param  point   The bit position to display.
     */
    friend ostream& operator<<(ostream& fout, const myBitPosition& point);
    /** The equality operator.
     * @param  otherPoint  The bit position at the right of the operator.
     * @return True iff this object equals @a otherPoint.
     */
    bool operator==(const myBitPosition& otherPoint) const;
    /** An ordering operator.
     * @param  otherPoint  The bit position at the right of the operator.
     * @return True iff this object comes before @a otherPoint.
     */
    bool operator<(const myBitPosition& otherPoint) const;
    /** This method increments the coordinates while maintaining the z coordinate.
     * It first attempts to increment y. If not possible, it resets y and increments x.
     * @return It returns false if (x, y)=(4, 4).
     */
    bool nextXY();
    /** This method sets the three coordinates.
     * @param  ax  The x-coordinate.
     * @param  ay  The y-coordinate.
     * @param  az  The z-coordinate.
     */
    void set(unsigned int ax=0, unsigned int ay=0, unsigned int az=0);
    /** This method translates the position along the x axis.
     * @param  dx  The amount of translation (can be positive or negative).
     */
    void xTranslate(int dx);
    /** This method translates the position along the y axis.
     * @param  dy  The amount of translation (can be positive or negative).
     */
    void yTranslate(int dy);
    /** This method translates the position along the z axis.
     * @param  dz  The amount of translation (can be positive or negative).
     * @param  laneSize    The lane size.
     */
    void zTranslate(int dz, unsigned int aLaneSize);

    void directXYPi();
    void inverseXYPi();
    void directRhoPi();
    void inverseRhoPi();


};

/** Class containing the x, z coordinates of a column. */
class myColumnPosition
{
public:
    /** The x-coordinate of the column, 0 ≤ x < 5. */
    unsigned int x;
    /** The z-coordinate of the column, 0 ≤ z < laneSize. */
    unsigned int z;
public:
    /** The default constructor. */
    myColumnPosition() : x(0), z(0) {}
    /** The constructor.
     * @param  ax  The x-coordinate.
     * @param  az  The z-coordinate.
     */
    myColumnPosition(unsigned int ax, unsigned int az) : x(ax), z(az) {}
    /** A constructor taking a bit position.
     * @param  ap  The bit position.
     */
    myColumnPosition(const myBitPosition& ap) : x(ap.x), z(ap.z) {}
    /** This function returns an integer between 0 and 5*laneSize.
     * @return x + 5*z
     */
    inline unsigned int getXplus5Z() const { return x+5*z; }
    /** An ordering operator, required when storing a ColumnPosition object
     * in a set or as the first member in maps.
     * @param  a   The column position at the left of the operator.
     * @param  az  The column position at the right of the operator.
     */
    friend bool operator<(const myColumnPosition& aCP, const myColumnPosition& bCP);
    /** A display function, for use with the << operator.
     * @param  fout    The output stream to write to.
     * @param  aCP The column position to display.
     */
    friend ostream& operator<<(ostream& fout, const myColumnPosition& aCP);
};

/** Class containing the y, z coordinates of a row. */
class myRowPosition
{
public:
    /** The y-coordinate of the column, 0 ≤ x < 5. */
    unsigned int y;
    /** The z-coordinate of the column, 0 ≤ z < laneSize. */
    unsigned int z;
public:
    /** The default constructor. */
    myRowPosition() : y(0), z(0) {}
    /** The constructor.
     * @param  ax  The y-coordinate.
     * @param  az  The z-coordinate.
     */
    myRowPosition(unsigned int ay, unsigned int az) : y(ay), z(az) {}
    /** A constructor taking a bit position.
     * @param  ap  The bit position.
     */
    myRowPosition(const myBitPosition& ap) : y(ap.y), z(ap.z) {}
    /** This function returns an integer between 0 and 5*laneSize.
     * @return y + 5*z
     */
    inline unsigned int getYplus5Z() const { return y+5*z; }
    /** An ordering operator, required when storing a RowPosition object
     * in a set or as the first member in maps.
     * @param  aRP  The row position at the left of the operator.
     * @param  bRP  The row position at the right of the operator.
     */
    friend bool operator<(const myRowPosition& aRP, const myRowPosition& bRP);
    /** A display function, for use with the << operator.
     * @param  fout    The output stream to write to.
     * @param  aRP The row position to display.
     */
    friend ostream& operator<<(ostream& fout, const myColumnPosition& aCP);
};

#endif /* myPositions_hpp */
