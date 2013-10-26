  -Proj3
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

-All 3 executables are run through command line while in the same directory
  -running any executable w/out any parameters will list the proper format for running it
    -Canny [low threshold] [high threshold] [sobel operator size] [l2 gradient] [target file]
      -running Canny edge detection will output file with same name as original and c_ prefixed to it
    -Hough [rho] [theta divisor] [threshold] [srn] [stn] [target file]
      -running Hough Lines Transform will output file with same name as input file and h_ prefixed to it
      -as well as a file titled ints_h_ prefixed to input file name
    -HoughP [rho] [theta divisor] [threshold] [target file]
      -running Probabilistic Hough Lines Transform will output file with same name as input file and hP_ prefixed to it
      -as well as a file titled ints_hP_ prefixed to input file name
      
-depending on the results of canny, hough line transforms may take a long time to compute...
-intersection detection will take even longer
-vanishing point calculation will take even longer than the above
...if thresholds are set too high when executing Hough.exe or HoughP.exe program will crash trying to find vanishing point as a result of <still trying to figure that out, was sure empty vectors wouldn't crash my code>
