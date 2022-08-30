
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdlib.h>




// modes
bool debugMode = true;

// binary conversion for 0-255 number for speed binary conversion
uchar bins[256][8] = { {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,1},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,1},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,1},{0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,1},{0,0,0,0,1,0,1,0},{0,0,0,0,1,0,1,1},{0,0,0,0,1,1,0,0},{0,0,0,0,1,1,0,1},{0,0,0,0,1,1,1,0},{0,0,0,0,1,1,1,1},{0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,1},{0,0,0,1,0,0,1,0},{0,0,0,1,0,0,1,1},{0,0,0,1,0,1,0,0},{0,0,0,1,0,1,0,1},{0,0,0,1,0,1,1,0},{0,0,0,1,0,1,1,1},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,1},{0,0,0,1,1,0,1,0},{0,0,0,1,1,0,1,1},{0,0,0,1,1,1,0,0},{0,0,0,1,1,1,0,1},{0,0,0,1,1,1,1,0},{0,0,0,1,1,1,1,1},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,1},{0,0,1,0,0,0,1,0},{0,0,1,0,0,0,1,1},{0,0,1,0,0,1,0,0},{0,0,1,0,0,1,0,1},{0,0,1,0,0,1,1,0},{0,0,1,0,0,1,1,1},{0,0,1,0,1,0,0,0},{0,0,1,0,1,0,0,1},{0,0,1,0,1,0,1,0},{0,0,1,0,1,0,1,1},{0,0,1,0,1,1,0,0},{0,0,1,0,1,1,0,1},{0,0,1,0,1,1,1,0},{0,0,1,0,1,1,1,1},{0,0,1,1,0,0,0,0},{0,0,1,1,0,0,0,1},{0,0,1,1,0,0,1,0},{0,0,1,1,0,0,1,1},{0,0,1,1,0,1,0,0},{0,0,1,1,0,1,0,1},{0,0,1,1,0,1,1,0},{0,0,1,1,0,1,1,1},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,1},{0,0,1,1,1,0,1,0},{0,0,1,1,1,0,1,1},{0,0,1,1,1,1,0,0},{0,0,1,1,1,1,0,1},{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,1},{0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,1},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,1},{0,1,0,0,0,1,0,0},{0,1,0,0,0,1,0,1},{0,1,0,0,0,1,1,0},{0,1,0,0,0,1,1,1},{0,1,0,0,1,0,0,0},{0,1,0,0,1,0,0,1},{0,1,0,0,1,0,1,0},{0,1,0,0,1,0,1,1},{0,1,0,0,1,1,0,0},{0,1,0,0,1,1,0,1},{0,1,0,0,1,1,1,0},{0,1,0,0,1,1,1,1},{0,1,0,1,0,0,0,0},{0,1,0,1,0,0,0,1},{0,1,0,1,0,0,1,0},{0,1,0,1,0,0,1,1},{0,1,0,1,0,1,0,0},{0,1,0,1,0,1,0,1},{0,1,0,1,0,1,1,0},{0,1,0,1,0,1,1,1},{0,1,0,1,1,0,0,0},{0,1,0,1,1,0,0,1},{0,1,0,1,1,0,1,0},{0,1,0,1,1,0,1,1},{0,1,0,1,1,1,0,0},{0,1,0,1,1,1,0,1},
		{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,1},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,1},{0,1,1,0,0,0,1,0},{0,1,1,0,0,0,1,1},{0,1,1,0,0,1,0,0},{0,1,1,0,0,1,0,1},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,1},{0,1,1,0,1,0,0,0},{0,1,1,0,1,0,0,1},{0,1,1,0,1,0,1,0},{0,1,1,0,1,0,1,1},{0,1,1,0,1,1,0,0},{0,1,1,0,1,1,0,1},{0,1,1,0,1,1,1,0},{0,1,1,0,1,1,1,1},{0,1,1,1,0,0,0,0},{0,1,1,1,0,0,0,1},{0,1,1,1,0,0,1,0},{0,1,1,1,0,0,1,1},{0,1,1,1,0,1,0,0},{0,1,1,1,0,1,0,1},{0,1,1,1,0,1,1,0},{0,1,1,1,0,1,1,1},{0,1,1,1,1,0,0,0},{0,1,1,1,1,0,0,1},{0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,1},{0,1,1,1,1,1,0,0},{0,1,1,1,1,1,0,1},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},{1,0,0,0,0,0,1,1},{1,0,0,0,0,1,0,0},{1,0,0,0,0,1,0,1},{1,0,0,0,0,1,1,0},{1,0,0,0,0,1,1,1},{1,0,0,0,1,0,0,0},{1,0,0,0,1,0,0,1},{1,0,0,0,1,0,1,0},{1,0,0,0,1,0,1,1},{1,0,0,0,1,1,0,0},{1,0,0,0,1,1,0,1},{1,0,0,0,1,1,1,0},{1,0,0,0,1,1,1,1},{1,0,0,1,0,0,0,0},{1,0,0,1,0,0,0,1},{1,0,0,1,0,0,1,0},{1,0,0,1,0,0,1,1},{1,0,0,1,0,1,0,0},{1,0,0,1,0,1,0,1},{1,0,0,1,0,1,1,0},{1,0,0,1,0,1,1,1},{1,0,0,1,1,0,0,0},{1,0,0,1,1,0,0,1},{1,0,0,1,1,0,1,0},{1,0,0,1,1,0,1,1},{1,0,0,1,1,1,0,0},{1,0,0,1,1,1,0,1},{1,0,0,1,1,1,1,0},{1,0,0,1,1,1,1,1},{1,0,1,0,0,0,0,0},{1,0,1,0,0,0,0,1},{1,0,1,0,0,0,1,0},{1,0,1,0,0,0,1,1},{1,0,1,0,0,1,0,0},{1,0,1,0,0,1,0,1},{1,0,1,0,0,1,1,0},{1,0,1,0,0,1,1,1},{1,0,1,0,1,0,0,0},{1,0,1,0,1,0,0,1},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,1},{1,0,1,0,1,1,0,0},{1,0,1,0,1,1,0,1},{1,0,1,0,1,1,1,0},{1,0,1,0,1,1,1,1},{1,0,1,1,0,0,0,0},{1,0,1,1,0,0,0,1},{1,0,1,1,0,0,1,0},{1,0,1,1,0,0,1,1},{1,0,1,1,0,1,0,0},{1,0,1,1,0,1,0,1},{1,0,1,1,0,1,1,0},{1,0,1,1,0,1,1,1},{1,0,1,1,1,0,0,0},{1,0,1,1,1,0,0,1},{1,0,1,1,1,0,1,0},{1,0,1,1,1,0,1,1},{1,0,1,1,1,1,0,0},
		{1,0,1,1,1,1,0,1},{1,0,1,1,1,1,1,0},{1,0,1,1,1,1,1,1},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,1},{1,1,0,0,0,0,1,0},{1,1,0,0,0,0,1,1},{1,1,0,0,0,1,0,0},{1,1,0,0,0,1,0,1},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,1},{1,1,0,0,1,0,0,0},{1,1,0,0,1,0,0,1},{1,1,0,0,1,0,1,0},{1,1,0,0,1,0,1,1},{1,1,0,0,1,1,0,0},{1,1,0,0,1,1,0,1},{1,1,0,0,1,1,1,0},{1,1,0,0,1,1,1,1},{1,1,0,1,0,0,0,0},{1,1,0,1,0,0,0,1},{1,1,0,1,0,0,1,0},{1,1,0,1,0,0,1,1},{1,1,0,1,0,1,0,0},{1,1,0,1,0,1,0,1},{1,1,0,1,0,1,1,0},{1,1,0,1,0,1,1,1},{1,1,0,1,1,0,0,0},{1,1,0,1,1,0,0,1},{1,1,0,1,1,0,1,0},{1,1,0,1,1,0,1,1},{1,1,0,1,1,1,0,0},{1,1,0,1,1,1,0,1},{1,1,0,1,1,1,1,0},{1,1,0,1,1,1,1,1},{1,1,1,0,0,0,0,0},{1,1,1,0,0,0,0,1},{1,1,1,0,0,0,1,0},{1,1,1,0,0,0,1,1},{1,1,1,0,0,1,0,0},{1,1,1,0,0,1,0,1},{1,1,1,0,0,1,1,0},{1,1,1,0,0,1,1,1},{1,1,1,0,1,0,0,0},{1,1,1,0,1,0,0,1},{1,1,1,0,1,0,1,0},{1,1,1,0,1,0,1,1},{1,1,1,0,1,1,0,0},{1,1,1,0,1,1,0,1},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,1},{1,1,1,1,0,0,1,0},{1,1,1,1,0,0,1,1},{1,1,1,1,0,1,0,0},{1,1,1,1,0,1,0,1},{1,1,1,1,0,1,1,0},{1,1,1,1,0,1,1,1},{1,1,1,1,1,0,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,1,0,1,0},{1,1,1,1,1,0,1,1},{1,1,1,1,1,1,0,0},{1,1,1,1,1,1,0,1},{1,1,1,1,1,1,1,0},{1,1,1,1,1,1,1,1} };

// window Size
int windowSize = 5;



// util function
uchar* get5bitBinary(int val) {
    uchar* output = new uchar[5];
    for (int i = 3; i < 8; i++) {
        output[i - 3] = bins[val][i];
    }
    return output;
}

// this funtion is use to get 
uchar getTop(int x, int y,uchar** seeArray) {
    if ((x - 1) < 0) return 0;
    return seeArray[x - 1][y];
}
uchar getLeft(int x, int y, uchar** seeArray) {
    if ((y - 1) < 0) return 0;
    return seeArray[x][y - 1];
}
uchar getRight(int x, int y, uchar** seeArray,int boundaryWidth) {
    if ((y + 1) > (boundaryWidth-1)) return 0;
    return seeArray[x][y + 1];
}
uchar getBottom(int x, int y,uchar** seeArray,int boundaryHeight) {
    if ((x + 1) > (boundaryHeight-1)) return 0;
    return seeArray[x + 1][y];
}


uchar getPower(uchar val, int power) {
    uchar out = 1;
    for (int i = 0; i < power; i++) out *= val;
    return out;
}
void showImage(std::string windowName, cv::Mat image) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, image);
}

void debugPrintImage(cv::Mat image) {
    if (debugMode == false) return;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            for (int c = 0; c < 3; c++) {
                std::cout << (int)color[c] << " ";
            }
            std::cout << std::endl;
        }
    }
}
void print2DArrayImage(uchar** imag, int height, int width) {
    if (debugMode == false) return;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << (int)imag[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "______________________" << std::endl;
}
int** getRuleMatrix5x5() {
    // nt == 120
    // nc == 89
    
    // memory allocation 100 byte
    int** output = new int* [5];
    for (int i = 0; i < 5; i++) output[i] = new int[5];

    output[0][0] = 16;
    output[0][1] = 17;
    output[0][2] = 21;
    output[0][3] = 5;
    output[0][4] = 20;

    output[1][0] = 24;
    output[1][1] = 25;
    output[1][2] = 29;
    output[1][3] = 5;
    output[1][4] = 20;

    output[2][0] = 24;
    output[2][1] = 25;
    output[2][2] = 29;
    output[2][3] = 13;
    output[2][4] = 20;

    output[3][0] = 24;
    output[3][1] = 25;
    output[3][2] = 29;
    output[3][3] = 5;
    output[3][4] = 28;

    output[4][0] = 16;
    output[4][1] = 25;
    output[4][2] = 29;
    output[4][3] = 5;
    output[4][4] = 28;

    return output;
}

int** getRuleMatrix6x6() {
    int** output = new int* [6];
    for (int i = 0; i < 6; i++) output[i] = new int[6];

    output[0][0] = 17;
    output[0][1] = 5;
    output[0][2] = 17;
    output[0][3] = 21;
    output[0][4] = 5;
    output[0][5] = 20;


    output[1][0] = 25;
    output[1][1] = 13;
    output[1][2] = 25;
    output[1][3] = 29;
    output[1][4] = 5;
    output[1][5] = 28;

    output[2][0] = 25;
    output[2][1] = 13;
    output[2][2] = 25;
    output[2][3] = 29;
    output[2][4] = 5;
    output[2][5] = 28;

    output[3][0] = 25;
    output[3][1] = 5;
    output[3][2] = 25;
    output[3][3] = 21;
    output[3][4] = 13;
    output[3][5] = 28;

    output[4][0] = 25;
    output[4][1] = 5;
    output[4][2] = 17;
    output[4][3] = 29;
    output[4][4] = 13;
    output[4][5] = 28;

    output[4][0] = 25;
    output[4][1] = 13;
    output[4][2] = 25;
    output[4][3] = 29;
    output[4][4] = 13;
    output[4][5] = 28;
    return output;
}



// modules

uchar** getBinaryImage(cv::Mat image) {
    // memory alocation
    uchar** out = new uchar* [image.rows];
    for (int i = 0; i < image.rows; i++) out[i] = new uchar[image.cols * 8 * 3];
   
    // converting image into binary
    for (int i = 0; i < image.rows; i++) {
        int column = 0;
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b Color = image.at<cv::Vec3b>(i, j);
            for (int c = 0; c < 3; c++) {
                uchar* binColor = bins[Color[c]];
                for (int b = 0; b < 8; b++) {
                    out[i][column] = binColor[b];
                    column++;
                }
            }
        }
    }
    return out;
}



cv::Mat getImage(uchar** binaryImage,int height,int width){
    // inti output image
    cv::Mat output = cv::Mat::zeros(cv::Size(width / 24, height), CV_8UC3);
    
    // coverting binary image back to normal image
    for (int i = 0; i < height; i++) {
        int count = 0;
        for (int j = 0; j < width; j+=24) {
            
            uchar blue = 0, green = 0, red = 0;

            // loop for blue
            int powerCount = 7;
            for (int bc = j; bc < j + 8; bc++) { 
                blue += getPower(2, powerCount) * binaryImage[i][bc];
                powerCount -= 1;
            }
            // loop for green
            powerCount = 7;
            for (int gc = j+8; gc < j + 16; gc++) {
                green += getPower(2, powerCount) * binaryImage[i][gc];
                powerCount -= 1;
            }
            // loop for red
            powerCount = 7;
            for (int rc = j+16; rc < j + 24; rc++) {
                red += getPower(2, powerCount) * binaryImage[i][rc];
                powerCount -= 1;
            }

            // putting value in output image
            cv::Vec3b& Color = output.at<cv::Vec3b>(i, count);
            Color[0] = blue;
            Color[1] = green;
            Color[2] = red;
            count++;
        }
    }
    return output;
}

void rowLeftShift(uchar** binaryImage, int height, int width){
    for (int i = 0; i < height; i++) {
        uchar* rowBuffer = new uchar[width];
        for (int j = 1; j < width; j++) {
            rowBuffer[j - 1] = binaryImage[i][j];
        }
        rowBuffer[width - 1] = binaryImage[i][0];
        for (int cj = 0; cj < width; cj++) {
            binaryImage[i][cj] = rowBuffer[cj];
        }
        free(rowBuffer);
    }
}
void colLeftShift(uchar** binaryImage, int height, int width) {
    for (int i = 0; i < width; i++) {
        uchar* colBuffer = new uchar[height];
        for (int j = 1; j < height; j++) {
            colBuffer[j - 1] = binaryImage[j][i];
        }
        colBuffer[height - 1] = binaryImage[i][0];
        for (int cj = 0; cj < height; cj++) {
            binaryImage[cj][i] = colBuffer[cj];
        }
        free(colBuffer);
    }
}

void rowRightShift(uchar** binaryImage, int height, int width) {
    for (int i = 0; i < height; i++) {
        uchar* rowBuffer = new uchar[width];
        int rowCount = 1;
        rowBuffer[0] = binaryImage[i][width - 1];
        for (int j = 0; j < width - 1; j++) {
            rowBuffer[rowCount] = binaryImage[i][j];
            rowCount++;
        }
        for (int rj = 0; rj < width; rj++) {
            binaryImage[i][rj]= rowBuffer[rj];
        }
    }
}

void colRightShift(uchar** binaryImage, int height, int width){
    for (int i = 0; i < width; i++) {
        uchar* colBuffer = new uchar[height];
        int colCount = 1;
        colBuffer[0] = binaryImage[i][height - 1];
        for (int j = 0; j < height - 1; j++) {
            colBuffer[colCount] = binaryImage[i][j];
            colCount++;
        }
        for (int cj = 0; cj < height; cj++) {
            binaryImage[i][cj] = colBuffer[cj];
        }
    }
}

void maskingLeftShift(uchar** binaryImage, int height, int width) {
    // row Shift done
    rowLeftShift(binaryImage, height, width);
    // col Shift done
    colLeftShift(binaryImage, height, width);
}
void maskingRighttShift(uchar** binaryImage, int height, int width) {
    // row Shif
    rowRightShift(binaryImage, height, width);
}

// gpu env
void transpose(uchar** binaryImage,int thRow,int thCol){
    // winsize^2 bytes buffer
    uchar** buffer = new uchar * [windowSize];
    for (int i = 0; i < windowSize; i++) buffer[i] = new uchar[windowSize];


    // iter over the Window

    // this loop transpose the matrix and stored in buffer
    for (int winRow = thRow,i=0; winRow < thRow + windowSize && i < windowSize; winRow++,i++) {
        for (int winCol = thCol,j=0; winCol < thCol + windowSize && j < windowSize; winCol++,j++) {
            buffer[j][i] = binaryImage[winRow][winCol];
        }
    }
    //this loop get transpose matrix from the buffer and stored again into in the binary Image
    for (int winRow = thRow, i = 0; winRow < thRow + windowSize && i < windowSize; winRow++, i++) {
        for (int winCol = thCol, j = 0; winCol < thCol + windowSize && j < windowSize; winCol++, j++) {
            binaryImage[winRow][winCol] = buffer[i][j];
        }
    }
    free(buffer);
}

void celluarAutomata(uchar** binaryImage,int thRow,int thCol,int** ruleMatrix,int nc,int height,int width){
    for (int evo = 0; evo < nc; evo++) {
        //std::cout << "Evolution: " << evo << std::endl;
        uchar nextVal = 0;
        for (int winRow = thRow, i = 0; winRow < thRow + windowSize && i < windowSize; winRow++, i++) {
            for (int winCol = thCol, j = 0; winCol < thCol + windowSize && j < windowSize; winCol++, j++) {
                uchar nonNeumann[5] = {binaryImage[winRow][winCol],getTop(winRow,winCol,binaryImage),getLeft(winRow,winCol,binaryImage),getBottom(winRow,winCol,binaryImage,height),getRight(winRow,winCol,binaryImage,width)};
                uchar* key = get5bitBinary(ruleMatrix[i][j]);
                for (int ru = 0; ru < 5; ru++) if(key[ru]==1)nextVal = nonNeumann[ru] ^ key[ru];
                free(key);
            }
        }
    }
}



// enc and dec function
void GpuEnvr(uchar** binaryImage, int height, int width,int** ruleMatrix,int nc) {
    for (int subRow = 0; subRow < height; subRow += windowSize) {
        for (int subCol = 0; subCol < width; subCol += windowSize) {
            transpose(binaryImage,subRow,subCol);
            celluarAutomata(binaryImage, subRow, subCol, ruleMatrix, nc,height,width);
            // masking(binaryImage, subRow, subCol);
        }
    }
}
void GpuEnvrEnc(uchar** binaryImage, int height, int width, int** ruleMatrix, int nc) {
    for (int subRow = 0; subRow < height; subRow += windowSize) {
        for (int subCol = 0; subCol < width; subCol += windowSize) {
            transpose(binaryImage, subRow, subCol);
            celluarAutomata(binaryImage, subRow, subCol, ruleMatrix, nc, height, width);
            // masking(binaryImage, subRow, subCol);
        }
    }

    //  maskingLeftShif(binaryImage, height, width);
}
void GpuEnvrDec(uchar** binaryImage, int height, int width, int** ruleMatrix, int nc) {

    //  maskingRighttShif(binaryImage, height, width);
    
    for (int subRow = 0; subRow < height; subRow += windowSize) {
        for (int subCol = 0; subCol < width; subCol += windowSize) {
            celluarAutomata(binaryImage, subRow, subCol, ruleMatrix, nc, height, width);
            transpose(binaryImage, subRow, subCol);
            // masking(binaryImage, subRow, subCol);
        }
    }
}

// main function (Entry point)
int main()
{
    cv::Mat image = cv::imread("C:\\Users\\USER\\Pictures\\Saved Pictures\\lofoten-islands---norway-wallpaper (1).jpg", cv::IMREAD_COLOR);
    cv::Mat resizeImage;
    // Check for failure
    if (image.empty())
    {
        std::cout << "Image Not Found!!!" << std::endl;
        std::cin.get(); //wait for any key press
        return -1;
    }

    cv::resize(image, resizeImage, cv::Size(5, 10), cv::INTER_LINEAR);
    if(debugMode==false)cv::resize(image, resizeImage, cv::Size(100, 100), cv::INTER_LINEAR);
    
    //                                  get converted
    //uchar** binaryImage = getBinaryImage(resizeImage);
    //std::cout << "binary Image" << std::endl;
    //print2DArrayImage(binaryImage, resizeImage.rows, resizeImage.cols * 24);


    
    //             gpu env this method is basically use for processing data

     
    //                                  Encription
    //GpuEnvrEnc(binaryImage, resizeImage.rows, resizeImage.cols * 24,getRuleMatrix5x5(),89);
    //std::cout << "binary Image Transpose" << std::endl;
    //print2DArrayImage(binaryImage, resizeImage.rows, resizeImage.cols * 24);
    //showImage("enc", getImage(binaryImage, resizeImage.rows, resizeImage.cols * 24));
    
    //                                  decryption
    //GpuEnvrDec(binaryImage, resizeImage.rows, resizeImage.cols * 24, getRuleMatrix5x5(), 31);
    //std::cout << "binary Image Transpose" << std::endl;
    //print2DArrayImage(binaryImage, resizeImage.rows, resizeImage.cols * 24);
    //showImage("dec", getImage(binaryImage, resizeImage.rows, resizeImage.cols * 24));
    
    //                                  Original Image
    //  cv::Mat img = getImage(binaryImage, resizeImage.rows, resizeImage.cols * 24);
    //  showImage("real", resizeImage);
    
    // wait for oo
    //  cv::waitKey(0);

    // debug testing leftShif and right shif module
    uchar** testArray = new uchar * [3];
    for (int i = 0; i < 3; i++) testArray[i] = new uchar[3];

    testArray[0][0] = 1;
    testArray[0][1] = 2;
    testArray[0][2] = 3;

    testArray[1][0] = 4;
    testArray[1][1] = 5;
    testArray[1][2] = 6;

    testArray[2][0] = 7;
    testArray[2][1] = 8;
    testArray[2][2] = 9;



    print2DArrayImage(testArray, 3, 3);
    rowRightShift(testArray, 3, 3);
    print2DArrayImage(testArray, 3, 3);
    
}
