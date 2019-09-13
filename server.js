const addon = require('./build/Release/opticalFlow_addon.node');

var express = require('express');
var app = express();
app.use(express.static('public'));
//const addon = require('./build/Release/hello_addon');


var imageNames = [];

const imageFolder = './public/images/';


const fs = require('fs');

fs.readdirSync(imageFolder).forEach(file => {
  imageNames.push(file)
});

app.get('/', function (req, res) {
  res.sendFile(__dirname + "/index1.html");
});

server = app.listen(3000, function () {
  console.log("Example app listening to port 3000");
  console.log(JSON.parse(addon.hello()))
  

})

var socket = require('socket.io');

var io = socket(server);
//console.log(addon.hello());


io.sockets.on('connection', newConnection);

function newConnection(socket) {

  var data = JSON.parse(addon.hello());


  //console.log(data)

  //data['names'] = imageNames;

  io.sockets.emit("data", data);

  io.sockets.emit("imageNames", imageNames);
}

