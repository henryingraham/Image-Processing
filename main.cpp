#include <iostream>
#include "Header.h"
#include "Pixel.h"
#include <vector>
#include <fstream>
using namespace std;

Header ReadFromFile(string inFilePath, vector<Pixel>& imageDataRef);
void WriteToFile(string outFilePath, vector<Pixel>& imageDataRef, Header headerObject);


void Multiply(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData);
void Subtract(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData);
void Screen(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData);
void Overlay(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData);
void AddToGreenChannel(vector<Pixel>& imageData1);
void ScaleRedAndBlueChannel(vector<Pixel>& imageData1);
void StrippedRedChannel(vector<Pixel>& imageData1, vector<Pixel>& redChannel);
void StrippedGreenChannel(vector<Pixel>& imageData1, vector<Pixel>& greenChannel);
void StrippedBlueChannel(vector<Pixel>& imageData1, vector<Pixel>& blueChannel);
void ConsolidateChannels(vector<Pixel>& redChannel, vector<Pixel>& greenChannel, vector<Pixel>& blueChannel, vector<Pixel>& outputImageData);
void FlipUpsideDown(vector<Pixel>& imageData1, vector<Pixel>& outputImageData);
void Quadrants(Header headerObject, vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& imageData3, vector<Pixel>& imageData4, vector<Pixel>& outputImageData);

int main() {
    string inFilePath;
    string outFilePath;
    string image1 = "input/layer1.tga";
    string image2 = "input/pattern1.tga";
    string image3 = "input/layer2.tga";
    string image4 = "input/car.tga";
    string image5 = "input/pattern2.tga";
    string image6 = "input/text.tga";
    string image7 = "input/circles.tga";
    string image8 = "input/layer_red.tga";
    string image9 = "input/layer_green.tga";
    string image10 = "input/layer_blue.tga";
    string image11 = "input/text2.tga";

    vector<Pixel> layer1pixels;
    vector<Pixel> pattern1pixels;
    vector<Pixel> layer2pixels;
    vector<Pixel> carPixels;
    vector<Pixel> pattern2pixels;
    vector<Pixel> textPixels;
    vector<Pixel> circlesPixels;
    vector<Pixel> layerRedPixels;
    vector<Pixel> layerGreenPixels;
    vector<Pixel> layerBluePixels;
    vector<Pixel> text2pixels;

    vector<Pixel> outputImageData;
    vector<Pixel> tempImageData;
    vector<Pixel> redChannel;
    vector<Pixel> greenChannel;
    vector<Pixel> blueChannel;




        Header layer1head = ReadFromFile(image1, layer1pixels);
        Header pattern1head = ReadFromFile(image2, pattern1pixels);
        Header layer2head = ReadFromFile(image3, layer2pixels);
        Header carhead = ReadFromFile(image4, carPixels);
        Header pattern2head = ReadFromFile(image5, pattern2pixels);
        Header texthead = ReadFromFile(image6, textPixels);
        Header circleshead = ReadFromFile(image7, circlesPixels);
        Header layerredhead = ReadFromFile(image8, layerRedPixels);
        Header layergreenhead = ReadFromFile(image9, layerGreenPixels);
        Header layerbluehead = ReadFromFile(image10, layerBluePixels);
        Header text2head = ReadFromFile(image11, text2pixels);



        //1
            outFilePath = "output/part1.tga";
            Multiply(layer1pixels, pattern1pixels, outputImageData);
            WriteToFile(outFilePath, outputImageData, layer1head);



        //2
            outFilePath = "output/part2.tga";
            Subtract(layer2pixels, carPixels, outputImageData);
            WriteToFile(outFilePath, outputImageData, layer2head);



        //3
            outFilePath = "output/part3.tga";
            Multiply(layer1pixels, pattern2pixels, tempImageData);
            Screen(textPixels, tempImageData, outputImageData);
            WriteToFile(outFilePath, outputImageData, layer1head);



        //4
            outFilePath = "output/part4.tga";
            Multiply(layer2pixels, circlesPixels, tempImageData);
            Subtract(pattern2pixels, tempImageData, outputImageData);
            WriteToFile(outFilePath, outputImageData, layer2head);



        //5
            outFilePath = "output/part5.tga";
            Overlay(layer1pixels, pattern1pixels, outputImageData);
            WriteToFile(outFilePath, outputImageData, layer1head);



        //6
            outFilePath = "output/part6.tga";
            AddToGreenChannel(carPixels);
            WriteToFile(outFilePath, carPixels, carhead);



       //7
            outFilePath = "output/part7.tga";
            ScaleRedAndBlueChannel(carPixels);
            WriteToFile(outFilePath, carPixels, carhead);



        //8
            outFilePath = "output/part8_r.tga";
            StrippedRedChannel(carPixels, redChannel);
            WriteToFile(outFilePath, redChannel, carhead);


            outFilePath = "output/part8_g.tga";
            StrippedGreenChannel(carPixels, greenChannel);
            WriteToFile(outFilePath, greenChannel, carhead);


            outFilePath = "output/part8_b.tga";
            StrippedBlueChannel(carPixels, blueChannel);
            WriteToFile(outFilePath, blueChannel, carhead);



        //9
            outFilePath = "output/part9.tga";
            StrippedRedChannel(layerRedPixels, redChannel);
            StrippedGreenChannel(layerGreenPixels, greenChannel);
            StrippedBlueChannel(layerBluePixels, blueChannel);
            ConsolidateChannels(redChannel, greenChannel, blueChannel, outputImageData);
            WriteToFile(outFilePath, outputImageData, layerredhead);



       //10
            outFilePath = "output/part10.tga";
            FlipUpsideDown(text2pixels, outputImageData);
            WriteToFile(outFilePath, outputImageData, text2head);



        //11
            outFilePath = "output/extracredit.tga";
            Quadrants(carhead, carPixels, circlesPixels, textPixels, pattern1pixels, outputImageData);
            carhead.width *= 2;
            carhead.height *= 2;
            WriteToFile(outFilePath, outputImageData, carhead);



}

Header ReadFromFile(string inFilePath, vector<Pixel>& imageDataRef) {
    ifstream file(inFilePath, ios_base::binary);

    /*----- Read header data----*/

    Header headerObject = Header(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file.read((char*)&headerObject.width, sizeof(headerObject.width));
    file.read((char*)&headerObject.height, sizeof(headerObject.height));
    file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    /*----- Read image data----*/

    int numPixels = headerObject.width * headerObject.height;
    for (int i = 0; i < numPixels; ++i) {
        Pixel newPixel = Pixel(0, 0, 0);
        file.read((char*)&newPixel.blue, sizeof(newPixel.blue));
        file.read((char*)&newPixel.green, sizeof(newPixel.green));
        file.read((char*)&newPixel.red, sizeof(newPixel.red));

        imageDataRef.push_back(newPixel);
    }

    return headerObject;
}

void WriteToFile(string outFilePath, vector<Pixel>& imageDataRef, Header headerObject) {
    ofstream file(outFilePath, ios_base::binary);

    file.write(&headerObject.idLength, sizeof(headerObject.idLength));
    file.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file.write((char*)&headerObject.width, sizeof(headerObject.width));
    file.write((char*)&headerObject.height, sizeof(headerObject.height));
    file.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    for (int i = 0; i < imageDataRef.size(); ++i) {
        file.write((char*)&imageDataRef.at(i).blue, sizeof(imageDataRef.at(i).blue));
        file.write((char*)&imageDataRef.at(i).green, sizeof(imageDataRef.at(i).green));
        file.write((char*)&imageDataRef.at(i).red, sizeof(imageDataRef.at(i).red));
    }
}



void Multiply(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData) {
    for (int i = 0; i < imageData1.size(); ++i) {
        float redNum1 = (float)imageData1.at(i).red;
        float redNum2 = (float)imageData2.at(i).red;
        float greenNum1 = (float)imageData1.at(i).green;
        float greenNum2 = (float)imageData2.at(i).green;
        float blueNum1 = (float)imageData1.at(i).blue;
        float blueNum2 = (float)imageData2.at(i).blue;
        Pixel newPixel = Pixel(0, 0 , 0);

        newPixel.red = (unsigned char)(((redNum1 * redNum2) / 255) + 0.5);
        newPixel.green = (unsigned char)(((greenNum1 * greenNum2) / 255) + 0.5);
        newPixel.blue = (unsigned char)(((blueNum1 * blueNum2) / 255) + 0.5);

        outputImageData.push_back(newPixel);
    }
}

void Subtract(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData) {
    for (int i = 0; i < imageData1.size(); ++i) {
        float redNum1 = (float)imageData1.at(i).red;
        float redNum2 = (float)imageData2.at(i).red;
        float greenNum1 = (float)imageData1.at(i).green;
        float greenNum2 = (float)imageData2.at(i).green;
        float blueNum1 = (float)imageData1.at(i).blue;
        float blueNum2 = (float)imageData2.at(i).blue;
        Pixel newPixel = Pixel(0, 0 , 0);

        if ((redNum2 - redNum1) < 0) {
            newPixel.red = 0;
        }

        else {
            newPixel.red = (unsigned char)(redNum2 - redNum1);
        }

        if ((greenNum2 - greenNum1) < 0) {
            newPixel.green = 0;
        }

        else {
            newPixel.green = (unsigned char)(greenNum2 - greenNum1);
        }

        if ((blueNum2 - blueNum1) < 0) {
            newPixel.blue = 0;
        }

        else {
            newPixel.blue = (unsigned char)(blueNum2 - blueNum1);
        }

        outputImageData.push_back(newPixel);
    }
}

void Screen(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData) {
    for (int i = 0; i < imageData1.size(); ++i) {
        float redNum1 = (float)imageData1.at(i).red;
        float redNum2 = (float)imageData2.at(i).red;
        float greenNum1 = (float)imageData1.at(i).green;
        float greenNum2 = (float)imageData2.at(i).green;
        float blueNum1 = (float)imageData1.at(i).blue;
        float blueNum2 = (float)imageData2.at(i).blue;
        Pixel newPixel = Pixel(0, 0 , 0);

        newPixel.red = (unsigned char)(255 - (((255 - redNum1) * (255 - redNum2) / 255) - 0.5));
        newPixel.green = (unsigned char)(255 - (((255 - greenNum1) * (255 - greenNum2) / 255) - 0.5));
        newPixel.blue = (unsigned char)(255 - (((255 - blueNum1) * (255 - blueNum2) / 255) - 0.5));

        outputImageData.push_back(newPixel);
    }
}

void Overlay(vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& outputImageData) {
    for (int i = 0; i < imageData1.size(); ++i) {
        float redNum1 = (float)imageData1.at(i).red;
        float redNum2 = (float)imageData2.at(i).red;
        float greenNum1 = (float)imageData1.at(i).green;
        float greenNum2 = (float)imageData2.at(i).green;
        float blueNum1 = (float)imageData1.at(i).blue;
        float blueNum2 = (float)imageData2.at(i).blue;
        Pixel newPixel = Pixel(0, 0 , 0);

        if (redNum2 < 128) {
            newPixel.red = (unsigned char)(((2 * redNum1 * redNum2) / 255) + 0.5);
            newPixel.green = (unsigned char)(((2 * greenNum1 * greenNum2) / 255) + 0.5);
            newPixel.blue = (unsigned char)(((2 * blueNum1 * blueNum2) / 255) + 0.5);
        }

        else {
            newPixel.red = (unsigned char)(255 - ((2 * (255 - redNum1) * (255 - redNum2) / 255) - 0.5));
            newPixel.green = (unsigned char)(255 - ((2 * (255 - greenNum1) * (255 - greenNum2) / 255) - 0.5));
            newPixel.blue = (unsigned char)(255 - ((2 * (255 - blueNum1) * (255 - blueNum2) / 255) - 0.5));
        }

        outputImageData.push_back(newPixel);
    }
}

void AddToGreenChannel(vector<Pixel>& imageData1) {
    for (int i = 0; i < imageData1.size(); ++i) {
        if ((float)imageData1.at(i).green + 200 > 255) {
            imageData1.at(i).green = 255;
        }

        else {
            imageData1.at(i).green += 200;
        }
    }
}

void ScaleRedAndBlueChannel(vector<Pixel>& imageData1) {
    for (int i = 0; i < imageData1.size(); ++i) {
        if ((float)imageData1.at(i).red * 4 > 255) {
            imageData1.at(i).red = 255;
        }

        else {
            imageData1.at(i).red *= 4;
        }

        imageData1.at(i).blue *= 0;
    }
}

void StrippedRedChannel(vector<Pixel>& imageData1, vector<Pixel>& redChannel) {
    for (int i = 0; i < imageData1.size(); ++i) {
        Pixel newPixel = Pixel(imageData1.at(i).red, imageData1.at(i).red, imageData1.at(i).red);
        redChannel.push_back(newPixel);
    }
}

void StrippedGreenChannel(vector<Pixel>& imageData1, vector<Pixel>& greenChannel) {
    for (int i = 0; i < imageData1.size(); ++i) {
        Pixel newPixel = Pixel(imageData1.at(i).green, imageData1.at(i).green, imageData1.at(i).green);
        greenChannel.push_back(newPixel);
    }
}

void StrippedBlueChannel(vector<Pixel>& imageData1, vector<Pixel>& blueChannel) {
    for (int i = 0; i < imageData1.size(); ++i) {
        Pixel newPixel = Pixel(imageData1.at(i).blue, imageData1.at(i).blue, imageData1.at(i).blue);
        blueChannel.push_back(newPixel);
    }
}

void ConsolidateChannels(vector<Pixel>& redChannel, vector<Pixel>& greenChannel, vector<Pixel>& blueChannel, vector<Pixel>& outputImageData) {
    for (int i = 0; i < redChannel.size(); ++i) {
        Pixel newPixel = Pixel(redChannel.at(i).red, greenChannel.at(i).green, blueChannel.at(i).blue);
        outputImageData.push_back(newPixel);
    }
}

void FlipUpsideDown(vector<Pixel>& imageData1, vector<Pixel>& outputImageData) {
    for (int i = imageData1.size() - 1; i >= 0; --i) {
        Pixel newPixel = Pixel(imageData1.at(i).red, imageData1.at(i).green, imageData1.at(i).blue);
        outputImageData.push_back(newPixel);
    }
}

void Quadrants(Header headerObject, vector<Pixel>& imageData1, vector<Pixel>& imageData2, vector<Pixel>& imageData3, vector<Pixel>& imageData4, vector<Pixel>& outputImageData) {
    int width = headerObject.width;
    int height = headerObject.height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) { //get line of bottom left and write to array
            Pixel newPixel = Pixel(imageData3.at(i * width + j).red, imageData3.at(i * width + j).green, imageData3.at(i * width + j).blue);
            outputImageData.push_back(newPixel);
        }

        for (int j = 0; j < width; ++j) { //get line of bottom right and write to array
            Pixel newPixel = Pixel(imageData4.at(i * width + j).red, imageData4.at(i * width + j).green, imageData4.at(i * width + j).blue);
            outputImageData.push_back(newPixel);
        }
    }

    for (int i = 0; i < height; ++i) { //get line of top left and write to array
        for (int j = 0; j < width; ++j) { //get first line and write to array
            Pixel newPixel = Pixel(imageData1.at(i * width + j).red, imageData1.at(i * width + j).green, imageData1.at(i * width + j).blue);
            outputImageData.push_back(newPixel);
        }

        for (int j = 0; j < width; ++j) { //get line of top right and write to array
            Pixel newPixel = Pixel(imageData2.at(i * width + j).red, imageData2.at(i * width + j).green, imageData2.at(i * width + j).blue);
            outputImageData.push_back(newPixel);
        }
    }
}


