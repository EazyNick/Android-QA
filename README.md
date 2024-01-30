# Android QA Test Tool
This program is based on Android-only mobile phone testing.

@ Image Comparison

- Conduct a test to compare the current Android screen image with the stored test result image.
Comparison methods: pixel-by-pixel comparison, histogram comparison

@ OCR Text Recognition

~ It is often used to identify the current image by recognizing characters on the screen.

I applied for the OCR library based on the list below.

- tesseract/baseapi.h
Includes the C++ API for using the Tesseract Optical Character Recognition (OCR) engine, 
which implements the ability to extract text from images

- leptonica/allheaders.h
Contains all header files in the Leptonica library. 
Leptonica is an open source library for image processing and image analysis, 
mainly used for image preprocessing for text recognition (OCR)

@ ADB Command Control

- Apply a script that allows you to control ADB commands in the MFC window to help you customize the test.
