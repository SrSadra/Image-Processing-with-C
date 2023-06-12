//#include <opencv2/opencv.hpp>
//
//int main() {
//    // Load the image
//    IplImage* image = cvLoadImage("input.jpg", CV_LOAD_IMAGE_COLOR);
//
//    // Check if the image loaded successfully
//    if (!image) {
//        printf("Failed to load the image.\n");
//        return -1;
//    }
//
//    // Convert the image to grayscale
//    IplImage* grayImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
//    cvCvtColor(image, grayImage, CV_BGR2GRAY);
//
//    // Perform eye detection based on contrast
//    CvHaarClassifierCascade* eyeCascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_eye.xml", 0, 0, 0);
//    CvMemStorage* storage = cvCreateMemStorage(0);
//    CvSeq* eyes = cvHaarDetectObjects(grayImage, eyeCascade, storage, 1.1, 3, 0, cvSize(30, 30));
//
//    // Apply red-eye correction
//    for (int i = 0; i < (eyes ? eyes->total : 0); i++) {
//        CvRect* eye = (CvRect*)cvGetSeqElem(eyes, i);
//
//        // Extract the eye region
//        CvRect eyeRegion = cvRect(eye->x, eye->y, eye->width, eye->height);
//        cvSetImageROI(image, eyeRegion);
//
//        // Apply red-eye correction by reducing the red channel
//        for (int y = 0; y < eye->height; y++) {
//            for (int x = 0; x < eye->width; x++) {
//                CvScalar pixel = cvGet2D(image, y, x);
//                pixel.val[2] = pixel.val[2] * 0.2;  // Reduce the red channel intensity
//                cvSet2D(image, y, x, pixel);
//            }
//        }
//
//        cvResetImageROI(image);
//    }
//
//    // Save the image with red-eye correction
//    cvSaveImage("output.jpg", image);
//
//    // Release resources
//    cvReleaseHaarClassifierCascade(&eyeCascade);
//    cvReleaseImage(&image);
//    cvReleaseImage(&grayImage);
//    cvReleaseMemStorage(&storage);
//
//    return 0;
//}
