# Machine Vision

## Functional specification:

This is a Qt application that visualizes object/people detections.


###  Feature specification (original)

* Create an application that can visualize/play sequences from the dataset and overlays

* Modify application to use network to identify moving objects in the sequences and display the object as an overlay on the sequence

* Add more functionality, either by adding more features in the current network or by adding a trained neural network.



## Technological specification:

* Client-side: [Qt](https://www.qt.io/) Version 5.13.1 

* Editor: [Qt Creator](https://www.qt.io/development-tools) Versoin 4.10.0

* Algorithmic core: [C++](http://www.cplusplus.org/)

* Libray for image processing algorithms: [OpenCV](https://opencv.org/) Version 4.1.1_2

* Dataset: [Multiple Object Tracking Benchmark](https://motchallenge.net/data/MOT17/)

* Task management: [Jira](https://support.alten.se/projects/MAC/summary)

### Setup:

* The application was developed on a Macbook Pro with macOS Mojave Version 10.14.6

* The PRO-file and project setting will need to be checked so that the OpenCV paths matches the local settings.

* * Set PKG_CONFIG_PATH to /usr/local/Cellar/opencv/4.1.1_2/lib/pkgconfig/

* * Add usr/local/bin/ to PATH 
