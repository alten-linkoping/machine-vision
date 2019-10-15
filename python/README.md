# Machine Vision

## Functional specification:

This is a web application that visualizes object detections of moving objects. 

###  features

* Create an application that can visualize/play sequences from the dataset and overlays

* Modify application to use network to identify moving objects in the sequences and display the object as an overlay on the sequence

* Add more functionality, either by adding more features in the current network or by adding a trained neural network.



## Technological specification:

To provide the JavaScript implementation Node.js uses a C++ library called v8 . Node.js Addons are dynamically-linked shared objects that can be loaded into Node.js using the require() function. Since both v8 and Node.js Addons are written in c++ we can write Addons that interacts with v8 in its own language and treat them as ordinary Node.js modules.

We want to visualize the c++-calculations in a web browser but can't require it directly from the client-side. We can neither require "ordinary" modules from the client-side since the require method is not defined there. Instead we use Browserify to write code that uses require in the same way as Node. We require "socket.io-client" to be able to receive the coordinates from the c++-calculations accessed in the server-side(Node.js).

* Client-side: JavaScript, HTML, CSS 

* Server-side: [Node.js](https://nodejs.org/en/) 

* Algorithmic core: [C++](http://www.cplusplus.org/)

* Libray for image processing algorithms: [OpenCV](https://opencv.org/) Version 4.1.0_3

* Dataset: [Multiple Object Tracking Benchmark](https://motchallenge.net/data/MOT17/)

* Task management: [Jira](https://support.alten.se/projects/MAC/summary)

* Code Review for Git [Gerrit](https://gerrit-review.googlesource.com/Documentation/)


