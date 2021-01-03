#include "Generator.h"

//#define EMPTY -1
//#define BOX 0
//#define PYRAMID 1
//#define SHIFTEDBOX 2
//#define CYLINDER 3
//#define CONE 4
//#define SHIFTEDCYLINDER 5

using namespace std;

ofstream fout;

gen::Shape gen::shapeObject[100];

int gen::counter = 0;
int gen::layer = 1;
int gen::speed;
bool gen::fillDirection = 0;

double gen::xMax;
double gen::yMax;
double gen::zMax;
double gen::headTemp;
double gen::bedTemp;
string gen::fileName;

double gen::lineWidth = .4;
double gen::layerHeight = .2;
double gen::infillPercent = .2;
double gen::retraction = 6;
int gen::wallLineCount = 3;
int gen::bottomLayers = 4;
int gen::topLayers = 4;
int gen::infillSpeed = 40;
int gen::innerWallSpeed = 40;
int gen::outerWallSpeed = 25;
int gen::solidFillSpeed = 40;
int gen::topSpeed = 25;

double gen::e = 0;
double gen::f = 0;
double gen::x = 0;
double gen::y = 0;
double gen::z = 0;
double gen::oldF = 0;
double gen::oldX = 0;
double gen::oldY = 0;
double gen::oldZ = 0;

void gen::printer(double printAreaX, double printAreaY, double printAreaZ, int setHeadTemp, int setBedTemp, string setFileName){


    xMax = printAreaX;
    yMax = printAreaY;
    zMax = printAreaZ;
    headTemp = setHeadTemp;
    bedTemp = setBedTemp;
    fileName = setFileName;

    fout.open(fileName + ".gcode");

}

void gen::setup(){

    fout << "; " << fileName << " GCode" << endl;
    fout << "; Objects To Be Printed: " << counter << endl;
    fout << "; Print Bed Dimensions: " << xMax << " x " << yMax << " x " << zMax << endl;
    fout << "; Extruder Temp: " << headTemp << " Degrees Celcius" << endl;
    fout << "; Bed Temp: " << bedTemp << " Degrees Celcius" << endl;
    fout << "; Layer Height = " << layerHeight << " mm" << endl;
    fout << "; Line Width = " << lineWidth << " mm" << endl;
    fout << "; Infill = " << infillPercent * 100 << "%" << endl;
    fout << "; Retraction Distance = " << retraction << " mm" << endl;
    fout << "; Wall Line Count = " << wallLineCount << endl;
    fout << "; Bottom Layers = " << bottomLayers << endl;
    fout << "; Top Layers = " << topLayers << endl;
    fout << "; Infill Print Speed = " << infillSpeed << " mm/s" << endl;
    fout << "; Inner Wall Print Speed = " << innerWallSpeed << " mm/s" << endl;
    fout << "; Outer Wall Print Speed = " << outerWallSpeed << " mm/s" << endl;
    fout << "; Solid Fill Print Speed = " << solidFillSpeed << " mm/s" << endl;
    fout << "; Top Layer Print Speed = " << topSpeed << " mm/s" << endl;

    fout << "; --------------------------------------" << endl;

    fout << "; " << shapeCount() << " Total Objects" << endl << endl;
    for (int i = 0; i < 100; i++){
        if (shapeObject[i].shape != emptyShape){
            if (shapeObject[i].shape == box){
                fout << "; Object " << i + 1 << ": Box" << endl;
                fout << "; Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == pyramid){
                fout << "; Object " << i + 1 << ": Pyramid" << endl;
                fout << "; Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == shiftedBox){
                fout << "; Object " << i + 1 << ": Shifted Box" << endl;
                fout << "; Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                fout << "; X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].xShiftDegrees << " Degrees" << endl << endl;
            }
            if (shapeObject[i].shape == cylinder){
                fout << "; Object " << i + 1 << ": Cylinder" << endl;
                fout << "; Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == cone){
                fout << "; Object " << i + 1 << ": Cone" << endl;
                fout << "; Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == shiftedCylinder){
                fout << "; Object " << i + 1 << ": Shifted Cylinder" << endl;
                fout << "; Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                fout << "; X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].xShiftDegrees << " Degrees" << endl << endl;
            }
        }
    }

    fout << "; --------------------------------------" << endl;

    //GCODE setup commands
    fout << "; Setup Commands" << endl;
    fout << "M140 S" << bedTemp << endl;
    fout << "M105" << endl;
    fout << "M104 S" << headTemp << endl;
    fout << "M105" << endl;
    fout << "M109 S" << headTemp << endl;
    fout << "M82 ; absolute extrusion mode" << endl;
    fout << "G92 E0 ; Reset Extruder" << endl;
    fout << "G28 ; Home all axes" << endl;
    fout << "G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed" << endl;
    fout << "G1 X0.1 Y20 Z0.3 F5000.0 ; Move to start position" << endl;
    fout << "G1 X0.1 Y200.0 Z0.3 F1500.0 E15 ; Draw the first line" << endl;
    fout << "G1 X0.4 Y200.0 Z0.3 F5000.0 ; Move to side a little" << endl;
    fout << "G1 X0.4 Y20 Z0.3 F1500.0 E30 ; Draw the second line" << endl;
    fout << "G92 E0 ; Reset Extruder" << endl;
    fout << "G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed" << endl;
    fout << "G1 X5 Y20 Z0.3 F5000.0; Move over to prevent blob squish" << endl;
    fout << "G0 F9000 Z2" << endl;
    fout << "M300 S800 P500" << endl;

}

void gen::finish(){

    fout << endl << ";-----------------------------------" << endl;
    fout << "; Finishing Commands" << endl;
    fout << "M300 S440 P200" << endl;
    fout << "M140 S0" << endl;
    fout << "M107" << endl;
    fout << "G91 ;Relative positioning" << endl;
    fout << "G1 E-2 F2700 ;Retract a bit" << endl;
    fout << "G1 E-2 Z0.2 F2400 ;Retract and raise Z" << endl;
    fout << "G1 X5 Y5 F3000 ;Wipe out" << endl;
    fout << "G1 Z50 ;Raise Z more" << endl;
    fout << "G90 ;Absolute positionning" << endl;
    fout << "G1 X0 Y220 ;Present print" << endl;
    fout << "M106 S0 ;Turn-off fan" << endl;
    fout << "M104 S0 ;Turn-off hotend" << endl;
    fout << "M140 S0 ;Turn-off bed" << endl;
    fout << "M84 X Y Z E ;Disable all steppers" << endl;
    fout << "M82 ;absolute extrusion mode" << endl;
    fout << "M104 S0" << endl;

}

void gen::generateCode(){

    setup();

    double maxH = maxHeight();

    while (1){

        fout << endl << ";-------------------------------------------------" << endl;
        fout << "; Layer:" << layer << endl;
        z = layer * layerHeight;
        //G0();

        for (int i = 0; i < 100; i++){

            shapeObject[i].drawLayer();

        }

        if (layer * layerHeight >= maxH) break;
        else if (layer * layerHeight >= zMax) break;
        else {
            layer += 1;
            fillDirection = !fillDirection;
        }
    }

    finish();

}

void gen::coutObjects(){

    cout << shapeCount() << " Total Objects" << endl << endl;

    for (int i = 0; i < 100; i++){
        if (shapeObject[i].shape != emptyShape){
            if (shapeObject[i].shape == box){
                cout << "Object " << i + 1 << ": Box" << endl;
                cout << "Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == pyramid){
                cout << "Object " << i + 1 << ": Pyramid" << endl;
                cout << "Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == shiftedBox){
                cout << "Object " << i + 1 << ": Shifted Box" << endl;
                cout << "Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                cout << "X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].xShiftDegrees << " Degrees" << endl << endl;
            }
            if (shapeObject[i].shape == cylinder){
                cout << "Object " << i + 1 << ": Cylinder" << endl;
                cout << "Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == cone){
                cout << "Object " << i + 1 << ": Cone" << endl;
                cout << "Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl << endl;
            }
            if (shapeObject[i].shape == shiftedCylinder){
                cout << "Object " << i + 1 << ": Shifted Cylinder" << endl;
                cout << "Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                cout << "X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].xShiftDegrees << " Degrees" << endl << endl;
            }
        }
    }

}

void gen::shape(int shape, double width, double length, double height, int xLocation, int yLocation){
    static int objectCounter = 0;
    shapeObject[objectCounter].shapeDims(++objectCounter, shape, width, length, height, xLocation, yLocation);
}


void gen::deleteObject(int objectToDelete){
    int objectNumber = objectToDelete - 1;
    shapeObject[objectNumber].shapeDims(0, emptyShape, 0, 0, 0, 0, 0);
}

//G commands
void gen::G0(){

    f = 9000;

    fout << "G0";
    if (f != oldF) fout << " F" << f;
    fout << " X" << x;
    fout << " Y" << y;
    if (z != oldZ) fout << " Z" << z;
    fout << endl;
    oldF = f;
    oldX = x;
    oldY = y;
    oldZ = z;

}

void gen::G1(){

    f = speed * 60;
    e += sqrt(((x - oldX) * (x - oldX)) + ((y - oldY) * (y - oldY))) * ((lineWidth * layerHeight) / 2.3);

    fout << "G1";
    if (f != oldF) fout << " F" << f;
    fout << " X" << x;
    fout << " Y" << y;
    if (z != oldZ) fout << " Z" << z;
    fout << " E" << e;
    fout << endl;
    oldF = f;
    oldX = x;
    oldY = y;
    oldZ = z;

}

void gen::G0withRetraction(){

    f = 9000;
    e -= retraction;
    fout << "G1";
    if (f != oldF) fout << " F" << f;
    fout << " E" << e << endl;

    G0();

    e += retraction;
    fout << "G1 E" << e << endl;

    oldF = f;
}

void gen::G1circle(double radius, double xLocation, double yLocation){


    for (double theta = 0; theta <= 2 * M_PI; theta += (2 * M_PI / 60)){

        x = xLocation + (radius * cos(theta));
        y = yLocation + (radius * sin(theta));

        G1();

    }


}


int gen::shapeCount(){
    int counter = 0;
    for (int i = 0; i < 100; i++){
        if (shapeObject[i].shape != emptyShape)
            counter += 1;
    }
    return counter;
}

double gen::maxHeight(){
    int counter = 0;
    for (int i = 0; i < 100; i ++){
        counter = (shapeObject[i].height > counter) ? shapeObject[i].height : counter;
    }
    return counter;
}

void gen::Shape::shapeDims(int setObjectNumber, int setShape, double setWidth, double setLength, double setHeight, double setxLocation, double setyLocation){
    objectNumber = setObjectNumber;
    shape = setShape;
    width = setWidth;
    length = setLength;
    height = setHeight;
    xLocation = setxLocation;
    yLocation = setyLocation;
    totalLayers = height / layerHeight;
    xCorner = xLocation - (width / 2);
    yCorner = yLocation - (length / 2);
}

void gen::Shape::shiftedBoxDims(double setxShiftDegrees, double setyShiftDegrees){
    xShiftDegrees = setxShiftDegrees;
    yShiftDegrees = setyShiftDegrees;
    _xShift = (((xShiftDegrees / 9) * 10) / 100) * lineWidth;
    _yShift = (((yShiftDegrees / 9) * 10) / 100) * lineWidth;
}

void gen::Shape::drawLayer(){

    if (shape != emptyShape && layer <= totalLayers){

        fout << endl << "; Object " << objectNumber << ": ";

        if (shape == box) {
            fout << "Box" << endl;
            boxLayer();
        }
        else if (shape == pyramid) {
            fout << "Pyramid" << endl;
            pyramidLayer();
        }
        else if (shape == shiftedBox) {
            fout << "Shifted Box" << endl;
            shiftedBoxLayer();
        }
        else if (shape == cylinder) {
            fout << "Cylinder" << endl;
            cylinderLayer();
        }
        else if (shape == cone) {
            fout << "Cone" << endl;
            coneLayer();
        }
        else if (shape == shiftedCylinder) {
            fout << "Shifted Cylinder" << endl;
            shiftedCylinderLayer();
        }
    }
}

void gen::Shape::boxLayer(){

    widthLayer = width;
    lengthLayer = length;
    xCornerLayer = xCorner;
    yCornerLayer = yCorner;

    wall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        solidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        shiftedInfill();

}

void gen::Shape::pyramidLayer(){

    widthLayer = width - (layer * (width / (height / layerHeight)));
    lengthLayer = length - (layer * (length / (height / layerHeight)));
    xCornerLayer = xLocation - (widthLayer / 2);
    yCornerLayer = yLocation - (lengthLayer / 2);

    wall();

    if (layer <= bottomLayers)
        solidFill();
    if (layer > bottomLayers)
        cubicInfill();

}

void gen::Shape::shiftedBoxLayer(){

    widthLayer = width;
    lengthLayer = length;
    xCornerLayer = xLocation - (widthLayer / 2) + ((_xShift * layer) - _xShift);
    yCornerLayer = yLocation - (lengthLayer / 2) + ((_yShift * layer) - _yShift);

    wall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        solidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        cubicInfill();

}

void gen::Shape::cylinderLayer(){

    widthLayer = width;
    xLocationLayer = xLocation;
    yLocationLayer = yLocation;

    circleWall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        circleSolidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        circleInfill();

}

void gen::Shape::coneLayer(){

    widthLayer = width - (layer * (width / (height / layerHeight)));
    xLocationLayer = xLocation;
    yLocationLayer = yLocation;

    circleWall();

    if (layer <= bottomLayers)
        circleSolidFill();
    if (layer > bottomLayers)
        circleInfill();

}

void gen::Shape::shiftedCylinderLayer(){

    widthLayer = width;
    xLocationLayer = xLocation + ((_xShift * layer) - _xShift);
    yLocationLayer = yLocation + ((_yShift * layer) - _yShift);

    circleWall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        circleSolidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        circleInfill();

}


void gen::Shape::wall(){

    fout << endl << "; Wall" << endl;

    x = xCornerLayer;
    y = yCornerLayer;
    G0withRetraction();

    for (int i = 0; i < wallLineCount; i++){

        double wallShift = lineWidth * i;
        if (widthLayer < ((i+1) * lineWidth) || lengthLayer < ((i+1) * lineWidth)) break;

        x = xCornerLayer + wallShift;
        y = yCornerLayer + wallShift;
        G0();

        if (layer == totalLayers) speed = topSpeed;
        else if (!i) speed = outerWallSpeed;
        else if (i) speed = innerWallSpeed;

        x += (widthLayer - (wallShift * 2));
        G1();
        y += (lengthLayer - (wallShift * 2));
        G1();
        x -= (widthLayer - (wallShift * 2));
        G1();
        y -= (lengthLayer - (wallShift * 2));
        G1();

    }
}

void gen::Shape::solidFill(){

    x = xCornerLayer + (lineWidth * wallLineCount);
    y = yCornerLayer + (lineWidth * wallLineCount);
    G0withRetraction();

    if (layer == totalLayers) speed = topSpeed;
    else speed = solidFillSpeed;

    fout << endl << "; Solid Fill" << endl;
    if (!fillDirection){
        while(1){

            y += (lengthLayer - (lineWidth * wallLineCount * 2));
            G1();
            if ((x + lineWidth) > (xCornerLayer + widthLayer - (lineWidth * wallLineCount))) break;
            x += lineWidth;
            G0();
            y -= lengthLayer - (lineWidth * wallLineCount * 2);
            G1();
            if ((x + lineWidth) > (xCornerLayer + widthLayer - (lineWidth * wallLineCount))) break;
            x += lineWidth;
            G0();
        }
    }
    if (fillDirection){
        while(1){

            x += (widthLayer - (lineWidth * wallLineCount * 2));
            G1();
            if ((y + lineWidth) > (yCornerLayer + lengthLayer - (lineWidth * wallLineCount))) break;
            y += lineWidth;
            G0();
            x -= widthLayer - (lineWidth * wallLineCount * 2);
            G1();
            if ((y + lineWidth) > (yCornerLayer + lengthLayer - (lineWidth * wallLineCount))) break;
            y += lineWidth;
            G0();
        }
    }
}

void gen::Shape::cubicInfill(){

    if (infillPercent == 0) return;

    double xCornerInterior = xCornerLayer + (lineWidth * wallLineCount);
    double yCornerInterior = yCornerLayer + (lineWidth * wallLineCount);
    double widthInterior = widthLayer - (wallLineCount * lineWidth * 2);
    double lengthInterior = lengthLayer - (wallLineCount * lineWidth * 2);
    double infillSpacing = (1 / infillPercent) * lineWidth;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    //convert to int for remainder operator
    int xCorner1000 = xCorner * 1000;
    int yCorner1000 = yCorner * 1000;
    int width1000 = width * 1000;
    int length1000 = length * 1000;
    int infillSpacing1000 = infillSpacing * 1000;

    double xShift1000 = ((xCorner1000 + (width1000 / 2)) % infillSpacing1000);
    double yShift1000 = ((yCorner1000 + (length1000 / 2)) % infillSpacing1000);
    double xFirstPass = xShift1000 / 1000;
    double yFirstPass = yShift1000 / 1000;

    while (1){
        if (xFirstPass < xCornerInterior) xFirstPass += infillSpacing;
        else break;
    }
    while (1){
        if (yFirstPass < yCornerInterior) yFirstPass += infillSpacing;
        else break;
    }

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    if (width > infillSpacing){

        x = xFirstPass;
        y = yCornerInterior;
        G0withRetraction();
        while(1){
            y += lengthInterior;
            G1();
            if (x + infillSpacing > xCornerInterior + widthInterior) break;
            x += infillSpacing;
            G0();
            y -= lengthInterior;
            G1();
            if (x + infillSpacing > xCornerInterior + widthInterior) break;
            x += infillSpacing;
            G0();
        }
    }

    if (lengthLayer > infillSpacing){

        x = xCornerInterior;
        y = yFirstPass;
        G0withRetraction();
        while(1){
            x += widthInterior;
            G1();
            if (y + infillSpacing > yCornerInterior + lengthInterior) break;
            y += infillSpacing;
            G0();
            x -= widthInterior;
            G1();
            if (y + infillSpacing > yCornerInterior + lengthInterior) break;
            y += infillSpacing;
            G0();
        }
    }
}

void gen::Shape::shiftedInfill(){

    if (infillPercent == 0) return;

    const double infillMultiplier = 1 / infillPercent;
    static double infillShift = 0;
    infillShift += (lineWidth / 4);
    if (infillShift >= lineWidth * infillMultiplier) infillShift = 0;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    x = xCorner + (lineWidth * wallLineCount) + infillShift;
    y = yCorner + (lineWidth * wallLineCount);
    G0withRetraction();

    while(1){
        y += length - (lineWidth * wallLineCount * 2);
        G1();
        if ((x + (lineWidth * infillMultiplier)) > (xCorner + width - (lineWidth * wallLineCount))) break;
        x += (lineWidth * infillMultiplier);
        G0();
        y -= (length - (lineWidth * wallLineCount * 2));
        G1();
        if ((x + (lineWidth * infillMultiplier)) > (xCorner + width - (lineWidth * wallLineCount))) break;
        x += (lineWidth * infillMultiplier);
        G0();
    }
    x = xCorner + (lineWidth * wallLineCount);
    y = yCorner + (lineWidth * wallLineCount) + infillShift;
    G0withRetraction();
    while(1){
        x += width - (lineWidth * wallLineCount * 2);
        G1();
        if ((y + (lineWidth * infillMultiplier)) > (yCorner + length - (lineWidth * wallLineCount))) break;
        y += (lineWidth * infillMultiplier);
        G0();
        x -= (width - (lineWidth * wallLineCount * 2));
        G1();
        if ((y + (lineWidth * infillMultiplier)) > (yCorner + length - (lineWidth * wallLineCount))) break;
        y += (lineWidth * infillMultiplier);
        G0();
    }

}

void gen::Shape::circleWall(){

    fout << endl << "; Wall" << endl;

    x = xLocationLayer + (widthLayer / 2);
    y = yLocationLayer;
    G0withRetraction();

    for (int i = 0; i < wallLineCount; i++){

        if (widthLayer < ((i+1) * lineWidth)) break;

        double lineRadius = (widthLayer / 2) - (i * lineWidth);
        x = xLocationLayer + lineRadius;
        y = yLocationLayer;
        G0();

        if (layer == totalLayers) speed = topSpeed;
        else if (!i) speed = outerWallSpeed;
        else if (i) speed = innerWallSpeed;

        G1circle(lineRadius, xLocationLayer, yLocationLayer);

    }
}

void gen::Shape::circleSolidFill(){

    fout << endl << "; Solid Fill" << endl;


    double interiorRadiusLayer = (widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);


    if (layer == totalLayers) speed = topSpeed;
    else speed = solidFillSpeed;

    if (!fillDirection){

        x = xLocationLayer - interiorRadiusLayer;
        y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            y = yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G1();
            if (x + lineWidth > xLocationLayer + interiorRadiusLayer) break;
            x += lineWidth;
            y = yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G0();
            y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G1();
            if (x + lineWidth > xLocationLayer + interiorRadiusLayer) break;
            x += lineWidth;
            y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G0();
        }
    }
    if (fillDirection){

        y = yLocationLayer - interiorRadiusLayer;
        x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            x = xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G1();
            if (y + lineWidth > yLocationLayer + interiorRadiusLayer) break;
            y += lineWidth;
            x = xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G0();
            x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G1();
            if (y + lineWidth > yLocationLayer + interiorRadiusLayer) break;
            y += lineWidth;
            x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G0();
        }
    }

}

void gen::Shape::circleInfill(){

    if (infillPercent == 0) return;

    double interiorRadiusLayer = (widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    double interiorDiameterLayer = interiorRadiusLayer * 2;
    double xLimitInteriorLayer = xLocationLayer - interiorRadiusLayer;
    double yLimitInteriorLayer = yLocationLayer - interiorRadiusLayer;
    double infillSpacing = (1 / infillPercent) * lineWidth;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    double interiorRadiusBase = (width / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    double interiorDiameterBase = interiorRadiusBase * 2;
    double xLimitInteriorBase = xLocation - interiorRadiusBase;
    double yLimitInteriorBase = yLocation - interiorRadiusBase;

    //convert to int for remainder operator
    int xLimitInteriorBase1000 = xLimitInteriorBase * 1000;
    int yLimitInteriorBase1000 = yLimitInteriorBase * 1000;
    int interiorRadiusBase1000 = interiorRadiusBase * 1000;
    int infillSpacing1000 = infillSpacing * 1000;

    double xShift1000 = (xLimitInteriorBase1000 + interiorRadiusBase1000 % infillSpacing1000);
    double yShift1000 = (yLimitInteriorBase1000 + interiorRadiusBase1000 % infillSpacing1000);
    double xFirstPass = xShift1000 / 1000;
    double yFirstPass = yShift1000 / 1000;

    while (1){
        if (xFirstPass < xLimitInteriorLayer) xFirstPass += infillSpacing;
        else break;
    }
    while (1){
        if (yFirstPass < yLimitInteriorLayer) yFirstPass += infillSpacing;
        else break;
    }

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    if (interiorDiameterLayer > infillSpacing){

        x = xFirstPass;
        y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            y = yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G1();
            if (x + infillSpacing > xLocationLayer + interiorRadiusLayer) break;
            x += infillSpacing;
            y = yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G0();
            y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G1();
            if (x + infillSpacing > xLocationLayer + interiorRadiusLayer) break;
            x += infillSpacing;
            y = yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - xLocationLayer) * (x - xLocationLayer))) + .0000001);
            G0();
        }

        y = yFirstPass;
        x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
        x = xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G1();
            if (y + infillSpacing > yLocationLayer + interiorRadiusLayer) break;
            y += infillSpacing;
        x = xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G0();
        x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G1();
            if (y + infillSpacing > yLocationLayer + interiorRadiusLayer) break;
            y += infillSpacing;
        x = xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - yLocationLayer) * (y - yLocationLayer))) + .0000001);
            G0();
        }
    }
}
