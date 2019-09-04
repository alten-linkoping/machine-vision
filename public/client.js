console.log('Client-side code running');
const io = require('socket.io-client');

var socket;

socket = io.connect('http://127.0.0.1:3000')


var myImage = document.getElementById('mainImage');
var imageArray = ["000001.jpg", "000002.jpg", "000003.jpg", "000004.jpg", "000005.jpg", "000006.jpg", "000007.jpg", "000008.jpg", "000009.jpg", "000010.jpg"]
var imageIndex = 1;
var t;
var t2;


function changeImage() {
  myImage.setAttribute("src", "images/"+imageArray[imageIndex])
  imageIndex++;
  if (imageIndex > imageArray.length-1) {
      imageIndex = 0;
  }
}




function startVideo() {
  changeImage();
  t = setInterval(
      () => changeImage(),
      500
  );

}

function stopVideo() {
  clearTimeout(t);
}




var myImage2 = document.getElementById('mainImage2');
var imageArray2 = ["000001.jpg", "000002.jpg", "000003.jpg", "000004.jpg", "000005.jpg", "000006.jpg", "000007.jpg", "000008.jpg", "000009.jpg", "000010.jpg"]
var imageIndex2 = 1;
var t;

function changeImage2() {
    myImage2.setAttribute("src", "images/"+imageArray2[imageIndex2])
    imageIndex2++;
    if (imageIndex2 > imageArray2.length-1) {
        imageIndex2 = 0;
    }
}




function startVideo2() {
    changeImage2();
    t2 = setInterval(
        () => changeImage2(),
        500
    );

}

function stopVideo2() {
  clearTimeout(t2);
}





const playButtonBefore = document.getElementById('playButton1');
playButtonBefore.addEventListener('click', function(e) {
  console.log('button was clicked');
  startVideo();
});

const playButtonAfter = document.getElementById('playButton2');
playButtonAfter.addEventListener('click', function(e) {
  console.log('button was clicked');
  startVideo2();
});

const stopButtonBefore = document.getElementById('stopButtonBefore');
stopButtonBefore.addEventListener('click', function(e) {
  console.log('button was clicked');
  stopVideo();
});

const stopButtonAfter = document.getElementById('stopButtonAfter');
stopButtonAfter.addEventListener('click', function(e) {
  console.log('button was clicked');
  stopVideo2();
});

const playButtonBoth = document.getElementById('playButtonBoth');
playButtonBoth.addEventListener('click', function(e) {
  console.log('button was clicked');
  startVideo();
  startVideo2();
});



const stopButtonBoth = document.getElementById('stopButtonBoth');
stopButtonBoth.addEventListener('click', function(e) {
  console.log('button was clicked');
  stopVideo();
  stopVideo2();
});