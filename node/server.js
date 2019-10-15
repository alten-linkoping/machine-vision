const addon = require('./build/Release/opticalFlow_addon.node');

const sqlite3 = require('sqlite3')

const db = new sqlite3.Database('score.db');

var express = require('express');
var app = express();
app.use(express.static('public'));
var data;

//app.use(express.bodyParser());
//const addon = require('./build/Release/hello_addon');
var bodyParser = require('body-parser')
app.use(bodyParser.json())

var highscore;


app.get('/test', (req, res) => {
var test1 = { "age":30 }


 db.get("select score from highscore where name = 'velocity'", (err, row)=>{
   console.log(row);
  res.send(row);
});


});


app.post('/todb', function(req, res){
	var obj = {};
  console.log('body: ' + JSON.stringify(req.body));
  console.log(req.body.score);
  db.run("UPDATE highscore SET score = ? WHERE name = 'velocity'", [req.body.score]);
	res.send(req.body);
});



app.get('/', function (req, res) {
  res.sendFile(__dirname + "/index1.html");
});

server = app.listen(3000, function () {
  console.log("Example app listening to port 3000");

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

      //db.run("UPDATE highscore SET score = 20 WHERE name = 'velocity'");

      io.sockets.emit("data", JSON.parse(chosenDataSet));
      

      

  });
  
});


