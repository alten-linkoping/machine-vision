const addon = require('./build/Release/opticalFlow_addon.node');

var express = require('express');
var app = express();
app.use(express.static('public'));
var data;
//const addon = require('./build/Release/hello_addon');



var imageNames = [];

const imageFolder = 'public/MOT17-09-FRCNN/img1/';


const fs = require('fs');

fs.readdirSync(imageFolder).forEach(file => {
  imageNames.push(file)
});

app.get('/', function (req, res) {
  res.sendFile(__dirname + "/index1.html");
});

server = app.listen(3000, function () {
  console.log("Example app listening to port 3000");
   
  //console.log(JSON.parse(addon.hello()))
  

})

var socket = require('socket.io');

var io = socket(server);




io.of("/client").on("connection", socket => {
  //console.log("test");
  socket.emit("names", imageNames);

});

io.of("/sketch").on("connection", socket => {
  //console.log("test");
  data = JSON.parse(addon.hello());
  socket.emit("data", data);

});


/*
io.sockets.on('connection', newConnection);

function newConnection(socket) {
  io.sockets.emit("imageNames", imageNames);
  io.sockets.emit("data", data);

  
}
*/



