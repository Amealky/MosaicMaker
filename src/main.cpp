#include <iostream>
#include <filesystem>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Configuration.h"

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

Configuration config;


Size tileSize;
Size outputImageSize;
vector<Mat> bankImages;
vector<int> bankImagesLuminance;


int square(int x)
{
    return x * x;
}

void getBankImages(string path) {
    cout << "loading bank images, this can't take a moment please wait..." << endl;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".JPG" || entry.path().extension() == ".jpg")) {
            Mat bankImage = imread(entry.path().string());
            if (bankImage.empty()) {
                cout << "Unable to load image : " << entry.path().string() << endl;
            }
            else {
                resize(bankImage, bankImage, tileSize);
                bankImages.push_back(bankImage);
            }
        }
    }
}

int calculateLuminanceFor(Mat image) {
    Mat imageGrey;
    cvtColor(image, imageGrey, CV_RGB2GRAY);

    int luminance = 0;
    for (int j = 0; j < tileSize.height; j++)
    {
        for (int i = 0; i < tileSize.width; i++)
        {
            luminance += imageGrey.at<uchar>(j, i);
        }
    }
    luminance /= (tileSize.height * tileSize.width);
    return luminance;
}

int main(int argc, char* argv[])
{
    string absolutePath = fs::absolute(fs::path(argv[0])).parent_path().string();
    string configFilePath = absolutePath + "\\..\\config\\configuration.txt";
    string inputImagePath = absolutePath + "\\..\\config\\input_image.jpg";
    string bankImagesPath = absolutePath + "\\..\\config\\imagesBank";
    string outputImagePath = absolutePath + "\\resultImages\\";

    config = loadConfigurationFromTxt(configFilePath);
    tileSize.width = config.tileWidth;
    tileSize.height = config.tileHeight;

    outputImageSize.width = config.outputImageWidth;
    outputImageSize.height = config.outputImageHeight;

    
    getBankImages(bankImagesPath);
    if (bankImages.empty()) {
        cout << "Bank of images is empty, program can't continue" << endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < bankImages.size(); i++) {
        bankImagesLuminance.push_back(calculateLuminanceFor(bankImages[i]));
    }
  
    cout << "Loading input image" << endl;
    Mat inputImage = imread(inputImagePath);
    if (inputImage.empty()) {
        cout << "input image is empty, program can't continue" << endl;
        return EXIT_FAILURE;
    }

    resize(inputImage, inputImage, outputImageSize);

    Mat inputImageGrey;
    cvtColor(inputImage, inputImageGrey, CV_RGB2GRAY);

    // Allocation dynamique pour LuminanceMap
    int** tilesLuminanceMap = new int* [outputImageSize.height];
    for (int i = 0; i < outputImageSize.height; ++i)
        tilesLuminanceMap[i] = new int[outputImageSize.width];

    Mat outputImage = Mat(outputImageSize, CV_8UC3);
    cout << "Start calculate best matching tiles, this can't take a moment please wait..." << endl;

    //We cut the input image in square of tile ( regarding the tiles size )
    for (int i = 0; i < outputImageSize.height / tileSize.height; i++)
    {
        for (int j = 0; j < outputImageSize.width / tileSize.width; j++)
        {
            // For each tile we get the luminance
            Rect tileRect(j * tileSize.width, i * tileSize.height, tileSize.width, tileSize.height);
            Mat tileToReplace = inputImage(tileRect);

            tilesLuminanceMap[i][j] = calculateLuminanceFor(tileToReplace);


            //Next we search for the best matchin image in the bank of image
            int bestLuminanceDiff = numeric_limits<int>::max();
            int bestIndex = 0;
            for (int z = 0; z < bankImagesLuminance.size(); ++z) {
                int luminanceDiff = abs(tilesLuminanceMap[i][j] - bankImagesLuminance[z]);

                //if the luminance diff between this tile and this image is better than the actual best then we register the index of the bankImage to use
                if (luminanceDiff < bestLuminanceDiff) {
                    bestLuminanceDiff = luminanceDiff;
                    bestIndex = z;
                }
            }

            //Then we use the best image in the bank as tile to create the output mosaic image
            bankImages.at(bestIndex).copyTo(outputImage(cv::Rect(j * tileSize.width, i * tileSize.height, tileSize.width, tileSize.height)));
        }
    }

    bool saveSucceed = imwrite(outputImagePath + config.outputImageName, outputImage);
    if (saveSucceed) {
        cout << "Image saved : " << outputImagePath + config.outputImageName << endl;
    }
    else {
        cout << "Image saving failed" << endl;
    }

    imshow("MosaicMaker output", outputImage);
    waitKey(0);

    // Free memory
    for (int i = 0; i < outputImageSize.height; ++i)
        delete[] tilesLuminanceMap[i];
    delete[] tilesLuminanceMap;

    return EXIT_SUCCESS;
}