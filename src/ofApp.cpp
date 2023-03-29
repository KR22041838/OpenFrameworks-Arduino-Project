#include "ofApp.h"
bool isBackgroundGreen = false; // Variable to keep track of the background color
int sendData = 0; // Variable to send data to Arduino
//ofTrueTypeFont font; // Declare a font object


void ofApp::setup() {
    serialMessage = false;

    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

    //font.load("Helvetica", 18);


    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    //serial.setup("COM10", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example

}

void ofApp::update() {
    if (serialMessage) {
        serialMessage = false;
        serial.writeByte(sendData); // sending the data to arduino

        serial.readBytes(receivedData, 5); // Getting the data from Arduino
        printf("receivedData is %d \n", receivedData);    // Printing in ASCII format
    }
}

void ofApp::draw() {

    ofSetColor(0);	// Text color is white

    if (isBackgroundGreen) {
        ofColor colorOne(255, 0, 0);
        ofColor colorTwo(30, 0, 0);

        ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
        // Sets the background to a circular gradient
    }
    else {
        ofColor colorOne(0, 255, 0);
        ofColor colorTwo(200,255,200);

        ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
        // Sets the background to a circular gradient
    }

    string msg;
    msg += "Click to change background color\n";
    msg += receivedData;
   
    
    ofDrawBitmapString(msg, 200, 300); // Write the data on the output window
   // font.drawString(msg, 400, 600);
}

void ofApp::mousePressed(int x, int y, int button) {
    isBackgroundGreen = !isBackgroundGreen; // Toggle the background color
    serialMessage = true; // Send data to Arduino
   // sendData = isBackgroundBlue ? 1 : 0; // Set the data to be sent to Arduino
}
