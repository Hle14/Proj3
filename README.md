Proj3
=====

Edge Detection

INSTRUCTIONS FOR COMPILING:

-(instructions best done using MS Visual Studio)

-Set Additional Include Directories:
  $(opencv_root)\build\include

-Set Additional Link Library Dependencies:
  $(opencv_root)\build\x64\vc11\lib
  
  -Add inputs(includes everything in the \lib directory:
  opencv_calib3d246.lib
  opencv_contrib246.lib
  opencv_core246.lib
  opencv_features2d246.lib
  opencv_flann246.lib
  opencv_gpu246.lib
  opencv_haartraining_engine.lib
  opencv_highgui246.lib
  opencv_imgproc246.lib
  opencv_legacy246.lib
  opencv_ml246.lib
  opencv_nonfree246.lib
  opencv_objdetect246.lib
  opencv_ocl246.lib
  opencv_photo246.lib
  opencv_stitching246.lib
  opencv_superres246.lib
  opencv_ts246.lib
  opencv_video246.lib
  opencv_videostab246.lib
  
-Comment-out/exclude from project entirety of Hough.cpp and HoughP.cpp --> Build project --> rename .exe to Canny.exe

-Repeat above for Hough.cpp and HoughP.cpp to create a Hough.exe and HoughP.exe
