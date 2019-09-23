console.log("sketch");
let img; // Declare variable 'img'.
var socket;

var data1;

var imageArray2;
var currentImage;

var imageIndex2 = 1;
var t;
var angle = 0;
var socket;

var dataSetNumber = 0;

var dataSetNames = ["MOT17-09-FRCNN", "MOT17-08-FRCNN", "MOT17-04-SDP"]

var highScore =0;


var dataSetHasBeenChosen = false;

let particle;




var possibleToChangeSet = true;

var dataSetName;


function changeImage2() {
  socket.disconnect();
  img = loadImage(dataSetNames[dataSetNumber] + "/img1/" + Object.keys(imageArray2)[imageIndex2]);
  currentImage = Object.keys(imageArray2)[imageIndex2];
  imageIndex2++;
  console.log(Object.keys(imageArray2).length)
  if (imageIndex2 > Object.keys(imageArray2).length - 1) {
    imageIndex2 = 0;
  }
}




function startVideo() {
  t = setInterval(
    () => changeImage2(),
    250
  );

}

function stopVideo() {
  clearTimeout(t);
}


function getDataBasedOnChoice() {

  socket = io.connect('http://127.0.0.1:3000')
  socket.on("data", getCoordinates);

}

function getCoordinates(data) {

  imageArray2 = data;

}


function setVariables() {

  imageArray2 = null;

  currentImage = '000002.jpg';
  dataSetHasBeenChosen = true;

  img = loadImage(dataSetNames[dataSetNumber] + '/img1/000001.jpg');

  stopVideo();

  //document.getElementById('playButton2').disabled = false;


}


function buttonSetUp() {

  const playButtonAfter = document.getElementById('playButton2');
  playButtonAfter.addEventListener('click', function (e) {
    console.log('button was clicked');
    startVideo();
  });

  const stopButtonAfter = document.getElementById('stopButtonAfter');
  stopButtonAfter.addEventListener('click', function (e) {
    console.log('button was clicked');
    stopVideo();
  });


  const dataset1 = document.getElementById('dataset1');
  dataset1.addEventListener('click', function (e) {
    console.log('dataset1');

    if (possibleToChangeSet) {

      dataSetNumber = 0;
      setVariables();


      socket = io.connect('/');
      socket.emit('event', { message: 1 });




      getDataBasedOnChoice();
    }



  });
  const dataset2 = document.getElementById('dataset2');
  dataset2.addEventListener('click', function (e) {
    console.log('dataset2');
    if (possibleToChangeSet) {

      dataSetNumber = 1;
      setVariables();
      socket = io.connect('/');
      socket.emit('event', { message: 2 });



      getDataBasedOnChoice();
    }
  });

  const dataset3 = document.getElementById('dataset3');
  dataset3.addEventListener('click', function (e) {
    if (possibleToChangeSet) {

      dataSetNumber = 2;
      setVariables();

      socket = io.connect('/');
      socket.emit('event', { message: 3 });

      getDataBasedOnChoice();


    }
  });


}


class Particle {

  constructor() {
    this.pos = createVector(width / 2, height / 2);
    this.vel = createVector(0, 0);
    this.acc = createVector(0, 0);
  }

  applyForce(force) {
    this.acc.add(force);
  }

  update() {
    this.vel.add(this.acc);
    this.pos.add(this.vel);

    this.acc.set(0, 0);
  }

  display() {
    stroke('rgb(0,0,0)');
    strokeWeight(2);
    fill('#0275d8');
    ellipse(this.pos.x, this.pos.y, 48, 48);
  }

  edges() {
    if (this.pos.y > (height - 24)) {
      this.vel.y *= -1;
      this.pos.y = (height - 24);
    }

    if (this.pos.x > (width - 24)) {
      this.vel.x *= -1;
      this.pos.x = (width - 24);
    }

    if (this.pos.x < 24) {
      this.vel.x /= -1;
      this.pos.x = 24;
    }
  }

}






function setup() {

  //1920x1080
  var can = createCanvas(480, 270);
  can.parent("myContainer");
  currentImage = '000002.jpg';

  buttonSetUp()

  particle = new Particle();

  document.getElementById("demo1").innerHTML = highScore;


  $(document).ready(() =>{
    $.ajax({
      url: 'test/',
      type: 'GET',
      dataType: 'json',
      success: (data) => {
        console.log("test: "+ data);
        highScore = parseInt(data);
        document.getElementById("demo2").innerHTML = highScore;

      }
    });

  });

}



function draw() {
  if (imageArray2 != null) {
    document.getElementById('playButton2').disabled = false;
    document.getElementById('stopButtonAfter').disabled = false;
    img.resize(480, 270);
    // Displays the image at its actual size at point (0,0)
    image(img, 0, 0);


    possibleToChangeSet = true;

    document.getElementById("demo").innerHTML = "Dataset " + (dataSetNumber + 1);



    for (var i in imageArray2[currentImage]) {
      //console.log(imageArray2[currentImage][i]);
      var res = imageArray2[currentImage][i].split(",");


      var first = parseInt(res[0]);
      var second = parseInt(res[1]);
      var third = parseInt(res[2]);
      var fourth = parseInt(res[3]);

      noFill();
      rect(first, second, fourth, third);



      //x,y, height,width
      stroke(255, 204, 0);
      strokeWeight(2);


    }

  }
  else {


    if (dataSetHasBeenChosen) {
      possibleToChangeSet = false;
      background(51)
      translate(width / 2, height / 2);
      rotate(angle);
      strokeWeight(4)
      stroke(255)
      line(0, 0, 100, 0)
      angle += 0.1
      document.getElementById('playButton2').disabled = true;
      document.getElementById('stopButtonAfter').disabled = true;


    }
    else {

      background(50);
      strokeWeight(2);


      if(Math.abs(particle.vel.x) > highScore){
        //document.getElementById("demo1").innerHTML = "JAAAAAAA";
        document.getElementById("demo1").innerHTML = Math.abs(particle.vel.x);
        document.getElementById("demo2").innerHTML = Math.abs(particle.vel.x) ;
        highScore = Math.abs(particle.vel.x);

        /*

        $(document).ready(() =>{
        $.ajax({
          type: "POST",
          url: "sendhighscore/",
          data: data,
          success: success,
          dataType: dataType
        });
      });

      */

      }
      else{
        document.getElementById("demo1").innerHTML = Math.abs(particle.vel.x);
        
        
      }

      

      if (particle.vel.x != 0) {
        //make the text flash between 0 and 258(black and white). The framecount scaling factor depends on how smooth the text should flash.
        fill(128 + sin(frameCount * 0.1) * 128);
      }

      if (mouseIsPressed && 0 < mouseX && mouseX < 480 && 0 < mouseY && mouseY < 270) {
        //set the boarder to blue when the mouse is pressed
        stroke('#0275d8');
        strokeWeight(4);
      }
      else {
        noStroke();
      }
      textSize(50);
      text("Choose dataset", 70, 80);

      var gravity = createVector(0, 0.2);
      var wind = createVector(0.09, 0);

      if (mouseIsPressed && 0 < mouseX && mouseX < 480 && 0 < mouseY && mouseY < 270) {
        particle.applyForce(wind);
      }

      particle.applyForce(gravity);

      particle.update();
      particle.edges();
      particle.display();




    }
  }
}


