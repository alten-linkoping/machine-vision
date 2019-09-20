const addon = require('./build/Release/opticalFlow_addon.node');

var express = require('express');
var app = express();
app.use(express.static('public'));
var data;
//const addon = require('./build/Release/hello_addon');

var dataSet;


app.get('/', function (req, res) {
  res.sendFile(__dirname + "/index1.html");
});

server = app.listen(3000, function () {
  console.log("Example app listening to port 3000");

  //console.log(JSON.parse(addon.hello()))


})

var socket = require('socket.io');

var io = socket(server);


io.on('connection', function(socket) {
  socket.on('event', function(data) {
      console.log('A client sent us this message:', data.message);
      dataSet = data.message;
      //console.log(addon.add(dataSet,10));

      chosenDataSet = addon.add(dataSet,10);
      console.log(chosenDataSet);

      io.sockets.emit("data", JSON.parse(chosenDataSet));
      
/*
      io.of("/client").on("connection", socket => {
        //console.log("test");
        data = JSON.parse(chosenDataSet);
        socket.emit("data", data);
      
      });
      */

      

  });
  
});


