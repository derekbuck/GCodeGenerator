#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#define ENDER_3_PRO 235, 235, 250

using namespace std;

namespace gen{


    void printer(double printAreaX, double printAreaY, double printAreaZ, int setHeadTemp, int setBedTemp, string fileName);

    double maxHeight();
    int shapeCount();
    void coutObjects();

    void shape(int shape, double width, double length, double height, int xLocation, int yLocation);
    void deleteObject(int objectToDelete);

    void generateCode();

    extern int counter;
    extern int layer;
    extern int speed;
    extern bool fillDirection;

    extern double xMax;
    extern double yMax;
    extern double zMax;
    extern double headTemp;
    extern double bedTemp;
    extern string fileName;

    extern double lineWidth;
    extern double layerHeight;
    extern double infillPercent;
    extern double retraction;
    extern int wallLineCount;
    extern int bottomLayers;
    extern int topLayers;
    extern int infillSpeed;
    extern int innerWallSpeed;
    extern int outerWallSpeed;
    extern int solidFillSpeed;
    extern int topSpeed;

    extern double e;
    extern double f;
    extern double x;
    extern double y;
    extern double z;
    extern double oldF;
    extern double oldX;
    extern double oldY;
    extern double oldZ;

    void setup();
    void finish();
    void G0();
    void G1();
    void G0withRetraction();
    void G1circle(double radius, double xLocation, double yLocation);

    enum ShapeName : int8_t{
        emptyShape = -1, box, pyramid, shiftedBox, cylinder, cone, shiftedCylinder
    };

    class Shape{
        public:

            int objectNumber = 0;
            int shape = emptyShape;
            double width = 0;
            double length = 0;
            double height = 0;
            double xLocation = 0;
            double yLocation = 0;
            double xShiftDegrees = 0;
            double yShiftDegrees = 0;
            int totalLayers = 0;

            void shapeDims(int setObjectNumber, int setShape, double setWidth, double setLength, double setHeight, double setxLocation, double setyLocation);
            void shiftedBoxDims(double setxShiftDegrees, double yShiftDegrees);
            void drawLayer();

            void boxLayer();
            void pyramidLayer();
            void shiftedBoxLayer();
            void cylinderLayer();
            void coneLayer();
            void shiftedCylinderLayer();

            void wall();
            void solidFill();
            void cubicInfill();
            void shiftedInfill();

            void circleWall();
            void circleSolidFill();
            void circleInfill();

        private:
            double xCorner;
            double yCorner;
            double widthLayer;
            double lengthLayer;
            double xLocationLayer;
            double yLocationLayer;
            double xCornerLayer;
            double yCornerLayer;
            double _xShift;
            double _yShift;
    };

    extern Shape shapeObject[100];
};

#endif // GENERATOR_H

