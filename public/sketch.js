let img; // Declare variable 'img'.

var socket;

var data1;
let x, y;
var startRect = false;

var myImage2 = document.getElementById('mainImage2');
var imageArray2;
var currentImage;
var imageArray3;

var imageIndex2 = 1;
var t;
var angle = 0;

var exampleData = {
  "000001.jpg": { "rect1": [20, 20, 30, 60], "rect2": [80, 20, 30, 60], "rect3": [120, 20, 30, 60] },
  "000002.jpg": { "rect1": [30, 20, 30, 60], "rect2": [90, 20, 30, 60], "rect3": [130, 20, 30, 60] }
}

var exampleData2 = {
  '000002.jpg': {
    Box1: '271,559,52,55',
    Box2: '850,534,54,58',
    Box3: '1240,458,234,141',
    Box4: '237,449,80,89',
    Box5: '1689,380,353,198',
    Box6: '1,311,568,131'
  },
  '000003.jpg': {
    Box1: '271,574,133,90',
    Box2: '1243,458,232,141',
    Box3: '245,452,120,84',
    Box4: '1685,379,360,234',
    Box5: '1,286,594,141'
  },
  '000004.jpg': {
    Box1: '307,634,72,55',
    Box2: '853,534,58,57',
    Box3: '1246,458,236,139',
    Box4: '243,450,171,96',
    Box5: '1684,378,362,235',
    Box6: '1,252,624,147',
    Box7: '247,167,76,70',
    Box8: '275,77,59,103'
  },
  '000005.jpg': {
    Box1: '1247,458,233,140',
    Box2: '242,449,262,121',
    Box3: '1686,381,365,167',
    Box4: '1,237,618,152'
  },
  '000006.jpg': {
    Box1: '1723,564,183,126',
    Box2: '1,560,298,94',
    Box3: '1244,456,215,145',
    Box4: '240,448,265,122',
    Box5: '1684,381,227,191',
    Box6: '1,228,348,168'
  },
  '000007.jpg': {
    Box1: '849,532,64,64',
    Box2: '1011,532,54,65',
    Box3: '1249,451,242,142',
    Box4: '238,446,268,126',
    Box5: '1694,383,371,172',
    Box6: '1866,355,228,53',
    Box7: '1,225,631,173'
  },
  '000008.jpg': {
    Box1: '1713,638,115,121',
    Box2: '277,614,96,81',
    Box3: '1,564,280,104',
    Box4: '1256,458,213,135',
    Box5: '282,450,164,69',
    Box6: '1699,404,175,163',
    Box7: '1,224,356,177'
  },
  '000009.jpg': {
    Box1: '1,564,259,105',
    Box2: '857,550,86,53',
    Box3: '770,544,88,60',
    Box4: '278,536,177,80',
    Box5: '1261,458,233,130',
    Box6: '283,452,79,62',
    Box7: '1691,415,338,169',
    Box8: '1866,405,189,53',
    Box9: '1,219,361,181'
  }
}

function changeImage2() {
  img = loadImage("images/" + Object.keys(imageArray2)[imageIndex2]);
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
  img = loadImage('images/000001.jpg'); // Load the image
  currentImage = '000002.jpg';

  socket = io.connect('http://127.0.0.1:3000')
  socket.on("data", getCoordinates);

  function getCoordinates(data) {
    //imageArray2 = data.names;
    imageArray2 = data;
    //console.log(imageArray2)
    console.log(data);


  }
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

  x = 230;
  y = 120;
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


