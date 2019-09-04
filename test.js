var express = require('express');
var app = express();
app.use(express.static('public'));
const addon = require('./build/Release/hello_addon');




app.get('/', function(req,res){
  res.sendFile(__dirname+"/index1.html");
  //res.status(200).send('Hello world');
});




server = app.listen(3000, function(){
  console.log("Example app listening to port 3000");
  console.log(addon.hello()["image1"]);
console.log(addon.hello()["image2"]); 
})

var socket = require('socket.io');

var io = socket(server);

io.sockets.on('connection', newConnection);

function newConnection(socket){
  console.log(socket.id);
  console.log("TESTSHFDHFGHFGHGF");
}