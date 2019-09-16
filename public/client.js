console.log('Client-side code running');
const io = require('socket.io-client');

var socket;
var imageNames



socket = io.connect('http://127.0.0.1:3000/client')
socket.on("names", (names) =>{
  console.log("received: ", names);
  imageNames = names;
  socket.disconnect();

});






var myImage = document.getElementById('mainImage');

var imageIndex = 1;
var t;




function changeImage() {
  console.log(imageNames[imageIndex]);
  myImage.setAttribute("src", "MOT17-09-FRCNN/img1/"+imageNames[imageIndex])
  imageIndex++;
  if (imageIndex > imageNames.length-1) {
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
  console.log('Play button before', imageNames);

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