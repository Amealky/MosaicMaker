<h1 align="center">🖼️ Mosaic Maker 🖼️</h1>
<p align="center">
   <a href="https://fr.wikipedia.org/wiki/C%2B%2B"> 
        <img src="https://img.shields.io/badge/C++17-%204--2--1?style=for-the-badge&label=language&color=blue">
    </a>
    <a href="https://opencv.org/"> 
        <img src="https://img.shields.io/badge/3--2--0-OpenCV%204--2--1?style=for-the-badge&logo=opencv&logoColor=white&label=OPENCV%20version&color=white">
    </a>
  
</p>

<p align="center">
        <img src="https://github.com/Amealky/MosaicMaker/blob/main/output/resultImages/girl1.JPG" width="200" height="200">
        <img src="https://github.com/Amealky/MosaicMaker/blob/main/output/resultImages/jamie_fox.JPG" width="200" height="200">
        <img src="https://github.com/Amealky/MosaicMaker/blob/main/output/resultImages/amanda.JPG" width="200" height="200">
        <img src="https://github.com/Amealky/MosaicMaker/blob/main/output/resultImages/girl2.JPG" width="200" height="200">
</p>


## Overview
This project is C++ and OpenCV program to transform a picture into a Mosaic using a bank of images, you can play with multiple variable into the ``config/`` folder to impact the final result like :
- Size of a tiles
- Size of output image
- Images to use ( by modifying the images into the ``imagesBank/`` folder )
- Input image by replacing the ``input_image.jpg``

## Run it
The github file already provide the ``.exe`` just double click on the file ( Only available for windows )

The result is stored under ``output/resultImages/`` folder

## Build the project
If you want to build the project you can follow the steps below :

- Download [OpenCV 3.2.0](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.2.0/opencv-3.2.0-vc14.exe/download)
- Install [Visual Studio](https://visualstudio.microsoft.com/fr/)
- Open the project
- Add OpenCV libs and includes [How to do](https://docs.opencv.org/4.x/dd/d6e/tutorial_windows_visual_studio_opencv.html)
- Build it 


Note : Build with G++11.4.0 using OpenCV-3.2.0

