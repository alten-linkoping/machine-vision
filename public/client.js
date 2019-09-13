console.log('Client-side code running');
const io = require('socket.io-client');

var socket;
var imageArray


socket = io.connect('http://127.0.0.1:3000')
socket.on("imageNames", getNames);

function getNames(imageNames){
 imageArray = imageNames;
 console.log("test")
 console.log(imageArray);
}



var myImage = document.getElementById('mainImage');

var imageIndex = 1;
var t;




function changeImage() {
  myImage.setAttribute("src", "images/"+imageArray[imageIndex])
  imageIndex++;
  if (imageIndex > imageArray.length-1) {
      imageIndex = 0;
  }
}

function startVideo() {
  t = setInterval(
      () => changeImage(),
      500
  );

}

function stopVideo() {
  clearTimeout(t);
}

const playButtonBefore = document.getElementById('playButton1');
playButtonBefore.addEventListener('click', function(e) {
  console.log('button was clicked');
  startVideo();
});

const stopButtonBefore = document.getElementById('stopButtonBefore');
stopButtonBefore.addEventListener('click', function(e) {
  console.log('button was clicked');
  stopVideo();
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