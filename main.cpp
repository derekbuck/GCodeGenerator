#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "Generator.h"

using namespace std;

int main(){


    cout << "GCode Generator" << endl;
    cout << "Created by Derek Boekelheide" << endl;
    cout << "Derek Boekelheide is not responsible for any damages that may occur printing files generated with this program." << endl;
    cout << "Current Functionality: " << endl;
    cout << "Can print up to 100 objects." << endl;
    cout << "No overlap detection currently included, so please double check that no two objects are created within the same space." << endl;
    cout << "The only way to change size of printable area is to edit the header file in source code (Generator.h)." << endl;
    cout << "Printable area preset for ENDER 3 PRO: 235, 235, 250." << endl;
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    int filament;
    cout << "Select '0' to print with PLA" << endl;
    cout << "Select '1' to print with ABS" << endl;
    cout << "Select '2' to enter custom print temperatures" << endl;
    cin >> filament;

    int headTemp;
    int bedTemp;
    string nameString;
    if (filament == 0) {
        cout << "File to be generated for PLA." << endl << endl;
        headTemp = 200;
        bedTemp = 60;
        nameString = "E3PRO_PLA_";
    }
    else if (filament == 1) {
        cout << "File to be generated for ABS." << endl << endl;
        headTemp = 230;
        bedTemp = 85;
        nameString = "E3PRO_ABS_";
    }
    else if (filament == 2){
        cout << "Please enter desired extruder temperature, in Celcius." << endl;
        cin >> headTemp;
        cout << "Please enter desired bed temperature, in Celcius." << endl;
        cin >> bedTemp;
        nameString = "E3PRO_CUSTOM_";
    }
    cout << endl;

    string fileName;
    cout << "Please enter file name. " << endl;
    cout << "Use normal characters/numbers. DO not use spaces. If you reuse a file name, it will override the old file." << endl;
    cin >> fileName;

    gen::printer(ENDER_3_PRO, headTemp, bedTemp, nameString + fileName);

    while(1){
        int userInput;
        cout << "Select corresponding number to modify preset settings." << endl;
        cout << "If you are ready to create printable objects, enter '0'." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "1: Layer Height = " << gen::layerHeight << " mm" << endl;
        cout << "2: Line Width = " << gen::lineWidth << " mm" << endl;
        cout << "3: Infill = " << gen::infillPercent * 100 << "%" << endl;
        cout << "4: Retraction Distance = " << gen::retraction << " mm" << endl;
        cout << "5: Wall Line Count = " << gen::wallLineCount << endl;
        cout << "6: Bottom Layers = " << gen::bottomLayers << endl;
        cout << "7: Top Layers = " << gen::topLayers << endl;
        cout << "8: Infill Print Speed = " << gen::infillSpeed << " mm/s" << endl;
        cout << "9: Inner Wall Print Speed = " << gen::innerWallSpeed << " mm/s" << endl;
        cout << "10 Outer Wall Print Speed = " << gen::outerWallSpeed << " mm/s" << endl;
        cout << "11: Solid Fill Print Speed = " << gen::solidFillSpeed << " mm/s" << endl;
        cout << "12: Top Layer Print Speed = " << gen::topSpeed << " mm/s" << endl;

        cin >> userInput;
        cout << endl;

        double newValue;

        if (userInput == 0) break;
        else if (userInput == 1) {
            cout << "Please enter new Layer Height in mm." << endl;
            cin >> newValue;
            gen::layerHeight = newValue;
            cout << endl << "The new Layer Height is: " << gen::layerHeight << " mm" << endl << endl;
        }
        else if (userInput == 2) {
            cout << "Please enter new Line Width in mm." << endl;
            cin >> newValue;
            gen::lineWidth = newValue;
            cout << endl << "The new Line Width is: " << gen::lineWidth << " mm" << endl << endl;
        }
        else if (userInput == 3) {
            cout << "Please enter new Infill Percentage as a decimal." << endl;
            cin >> newValue;
            gen::infillPercent = newValue;
            cout << endl << "The new Infill Percentage is: " << gen::infillPercent * 100 << "%" << endl << endl;
        }
        else if (userInput == 4) {
            cout << "Please enter new Retraction Distance in mm." << endl;
            cin >> newValue;
            gen::retraction = newValue;
            cout << endl << "The new Retraction Distance is: " << gen::retraction << " mm" << endl << endl;
        }
        else if (userInput == 5) {
            cout << "Please enter new Wall Line Count" << endl;
            cin >> newValue;
            gen::wallLineCount = newValue;
            cout << endl << "The new Wall Line Count is: " << gen::wallLineCount << " lines" << endl << endl;
        }
        else if (userInput == 6) {
            cout << "Please enter new Bottom Layer Count." << endl;
            cin >> newValue;
            gen::bottomLayers = newValue;
            cout << endl << "The new Bottom Layer Count is: " << gen::bottomLayers << " layers" << endl << endl;
        }
        else if (userInput == 7) {
            cout << "Please enter new Top Layer Count." << endl;
            cin >> newValue;
            gen::topLayers = newValue;
            cout << endl << "The new Top Layer Count is: " << gen::topLayers << " layers" << endl << endl;
        }
        else if (userInput == 8) {
            cout << "Please enter new Infill Print Speed in mm/s." << endl;
            cin >> newValue;
            gen::infillSpeed = newValue;
            cout << endl << "The new Infill Print Speed is: " << gen::infillSpeed << " mm/s" << endl << endl;
        }
        else if (userInput == 9) {
            cout << "Please enter new Inner Wall Print Speed in mm/s." << endl;
            cin >> newValue;
            gen::innerWallSpeed = newValue;
            cout << endl << "The new Inner Wall Print Speed is: " << gen::innerWallSpeed << " mm/s" << endl << endl;
        }
        else if (userInput == 10) {
            cout << "Please enter new Outer Wall Print Speed in mm/s." << endl;
            cin >> newValue;
            gen::outerWallSpeed = newValue;
            cout << endl << "The new Outer Wall Print Speed is: " << gen::outerWallSpeed << " mm/s" << endl << endl;
        }
        else if (userInput == 11) {
            cout << "Please enter new Solid Fill Print Speed in mm/s." << endl;
            cin >> newValue;
            gen::solidFillSpeed = newValue;
            cout << endl << "The new Solid Fill Print Speed is: " << gen::solidFillSpeed << " mm/s" << endl << endl;
        }
        else if (userInput == 12) {
            cout << "Please enter new Top Layer Print Speed in mm/s." << endl;
            cin >> newValue;
            gen::topSpeed = newValue;
            cout << endl << "The new Top Layer Print Speed is: " << gen::topSpeed << " mm/s" << endl << endl;
        }
    }

    for (int i = 0; i < 100; i++){

        int userInput;
        double objectDims[6];

        cout << "If you are ready to generate GCode, enter '0'." << endl;
        cout << "To delete an existing object, enter '1'." << endl;
        cout << "To create another printable object, enter '2'." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cin >> userInput;

        if (userInput == 0)
            break;
        else if (userInput == 1){
            int objectToDelete;
            cout << "Please enter the Object Number of the object you wish to delete." << endl;
            cin >> objectToDelete;
            gen::deleteObject(objectToDelete);
            gen::coutObjects();
        }
        else if (userInput == 2){

            cout << "Select corresponding number to your desired shape." << endl;
            cout << "0: Box" << endl;
            cout << "1: Pyramid" << endl;
            cout << "2: Shifted Box" << endl;
            cout << "3: Cylinder" << endl;
            cout << "4: Cone" << endl;
            cout << "5: Shifted Cylinder" << endl;
            cin >> objectDims[0];
            if (objectDims[0] == gen::box) cout << "Box" << endl;
            if (objectDims[0] == gen::pyramid) cout << "Pyramid" << endl;
            if (objectDims[0] == gen::shiftedBox) cout << "Shifted Box" << endl;
            if (objectDims[0] == gen::cylinder) cout << "Cylinder" << endl;
            if (objectDims[0] == gen::cone) cout << "Cone" << endl;
            if (objectDims[0] == gen::shiftedCylinder) cout << "Shifted Cylinder" << endl;

            if (objectDims[0] == gen::box || objectDims[0] == gen::pyramid || objectDims[0] == gen::shiftedBox){
                cout << "Please enter width of shape in mm." << endl;
                cin >> objectDims[1];

                cout << "Please enter length of shape in mm." << endl;
                cin >> objectDims[2];

                cout << "Please enter height of shape in mm." << endl;
                cin >> objectDims[3];

                cout << "Please enter X location of center of shape." << endl;
                cin >> objectDims[4];

                cout << "Please enter Y location of center of shape." << endl;
                cin >> objectDims[5];

            }

            else if (objectDims[0] == gen::cylinder || objectDims[0] == gen::cone || objectDims[0] == gen::shiftedCylinder){

                cout << "Please enter diameter of shape in mm." << endl;
                cin >> objectDims[1];

                objectDims[2] = 0;

                cout << "Please enter height of shape in mm." << endl;
                cin >> objectDims[3];

                cout << "Please enter X location of center of shape." << endl;
                cin >> objectDims[4];

                cout << "Please enter Y location of center of shape." << endl;
                cin >> objectDims[5];

            }

            gen::shape(objectDims[0], objectDims[1], objectDims[2], objectDims[3], objectDims[4], objectDims[5]);

            if (objectDims[0] == gen::shiftedBox || objectDims[0] == gen::shiftedCylinder) {
                    double xShiftDegree;
                    double yShiftDegree;
                    cout << "Please enter desired X overhang as degrees (0-90)" << endl;
                    cin >> xShiftDegree;
                    cout << "Please enter desired Y overhang as degrees (0-90)" << endl;
                    cin >> yShiftDegree;

                    gen::shapeObject[i].shiftedBoxDims(xShiftDegree, yShiftDegree);

            }

            gen::coutObjects();

        }

    }
    gen::generateCode();

    cout << "Your code has been generated, and the file is located in the same folder as this program." << endl;
    cout << "Please restart program to generate new file." << endl;
    return 0;
}
