const addon = require('./build/Release/hello_addon');
const port = 5000;
const http = require('http');





const fs = require('fs');

const server = http.createServer(function(req, res){
    res.writeHead(200, {'Content-Type': "text/html"});
    fs.readFile('index.html', function(error,data){
        if(error){
            res.writeHead(404);
        }
        else{
            res.write(data)
        }
        res.end();
    })
})


server.listen(port, function(error){
    if(error){
        console.log("Something went wrong", error)
    }
    else{
        console.log("Server is listening on port: "+port);
    }


});





console.log(addon.hello());
console.log(addon.hello()["image2"]); // 'world'
console.log(addon.hello().toString());


/*
//create a server object:
http.createServer(function (req, res) {
  res.write(addon.hello()["hello"].toString()); //write a response to the client
  res.end(); //end the response
}).listen(5000); //the server object listens on port 8080

*/