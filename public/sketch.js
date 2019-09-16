console.log("sketch");
let img; // Declare variable 'img'.

var socket2;

var data1;
var startRect = false;

//var myImage2 = document.getElementById('mainImage2');
var imageArray2;
var currentImage;
var imageArray3;

var imageIndex2 = 1;
var t;
var angle = 0;


function changeImage2() {
  img = loadImage("MOT17-09-FRCNN/img1/" + Object.keys(imageArray2)[imageIndex2]);
  currentImage = Object.keys(imageArray2)[imageIndex2];
  imageIndex2++;
  console.log(Object.keys(imageArray2).length)
  if (imageIndex2 > Object.keys(imageArray2).length-1) {
    imageIndex2 = 0;
  }
}




function startVideo2() {
  t2 = setInterval(
    () => changeImage2(),
    500
  );

}

function stopVideo2() {
  clearTimeout(t2);
}





function setup() {

  frameRate(2);
  //1920x1080
  var can = createCanvas(480, 270);
  can.parent("myContainer");
  img = loadImage('MOT17-09-FRCNN/img1/000001.jpg'); // Load the image
  currentImage = '000002.jpg';

  socket2 = io.connect('http://127.0.0.1:3000/sketch');

  socket2.on("data", (data) =>{
    console.log("received from sketch: ", data);
    imageArray2 = data;
    socket2.disconnect();
  
  });


  const playButtonAfter = document.getElementById('playButton2');
  playButtonAfter.addEventListener('click', function (e) {
    console.log('button was clicked');
    startVideo2();
    startRect = true;
  });

  const stopButtonAfter = document.getElementById('stopButtonAfter');
  stopButtonAfter.addEventListener('click', function (e) {
    console.log('button was clicked');
    stopVideo2();
    startRect = false;
  });

}

function draw() {
  if (imageArray2 != null) {
  img.resize(480, 270);
  // Displays the image at its actual size at point (0,0)
  image(img, 0, 0);


   

    
    

  for (var i in imageArray2[currentImage]) {
    //console.log(imageArray2[currentImage][i]);
    var res = imageArray2[currentImage][i].split(",");


    var first = parseInt(res[0])/4;
    var second = parseInt(res[1])/4;
    var third = parseInt(res[2])/4;
    var fourth = parseInt(res[3])/4;

    noFill();
    rect(first, second, fourth, third);
    //console.log("MÅLA!!!!" + first +", "+ second +", "+  third +", "+  fourth);


    //x,y, height,width
    stroke(255, 204, 0);
    strokeWeight(2);


  }
  



   }
   else{
    background(51)
    translate(width/2, height/2);
    rotate(angle);
    strokeWeight(4)
    stroke(255)
    line(0,0,100,0)
    angle +=0.1

   }

  
  

}


