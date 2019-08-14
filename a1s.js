'use strict';
const fs = require('fs');

let rawdata = fs.readFileSync('data.json');
let plantdata = JSON.parse(rawdata);


var express = require('express');
var path = require('path');
var bodyParser = require('body-parser');

var app1 = express();
var app2 = express();

app1.get('/',function(req,res)
{    
	res.send(plantdata);
})
app1.listen(7015,'192.168.43.41');


app1.use(bodyParser.json());



app1.post('/',function(req,res)
{

var check = req.body["task"]
const fs = require('fs');

fs.writeFile('priority.txt', check, function(err){
    if(err){console.log(err);}
});

console.log(check)
/*
var SerialPort = require('serialport');
var xbee_api = require('xbee-api');
var C = xbee_api.constants;

var xbeeAPI = new xbee_api.XBeeAPI({
  api_mode: 1
});


var serialport = new SerialPort("/dev/ttyUSB0", {
  baudrate: 9600,
});



var p1data = [];
var p2data = [];
var p3data = [];
var p1address = "0013A200410809DD"
var p2address = "0013A200410809E3"
var p3address = "0013A200410809D8"

function hex2aplant(paddress) {
    var hex = paddress //force conversion
    var str = '';
    for (var i = 0; i < hex.length ; i += 2)
        str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
    return str;
}

var on =  "1"
var off= "0"
var priority="1"
var hexon = String.fromCharCode(parseInt(on.substr(0,2),16));
var hexoff = String.fromCharCode(parseInt(off.substr(0,2),16)); 
var priority = String.fromCharCode(parseInt(priority.substr(0,2),16));



var p1hex = hex2aplant(p1address)
var p2hex = hex2aplant(p2address)
var p3hex = hex2aplant(p3address)


for(var i =0; i < p1hex.length ; i++)
{
	p1data.push(p1hex.charCodeAt(i));
	p2data.push(p2hex.charCodeAt(i));
	p3data.push(p3hex.charCodeAt(i));
	
}

//data.push(hexon.charCodeAt(0))
//data.push(priority.charCodeAt(0))
//data.push(hexon.charCodeAt(1))
 
serialport.pipe(xbeeAPI.parser);
xbeeAPI.builder.pipe(serialport);



if(check == "101")
{
var p1 = p1data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A20041671DAC",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});
}


if(check == "100")
{
var p1 = p1data
p1.push(hexoff.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A20041671DAC",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()
});
}


if(check == "201")
{
   var p1 = p2data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A20041671DAC",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00,  
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});	
}

if(check == "200")
{

var p1 = p2data
p1.push(hexoff.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A20041671DAC",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});

}





if(check == "301")
{
var p1 = p3data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A20041671DAC",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});

}

if(check == "111")
{

var p1 = p1data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});
}

if(check == "110")
{

var p1 = p1data
p1.push(hexoff.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});
}


if(check == "211")
{
var p1 = p2data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});

}

if(check == "210")
{
var p1 = p2data
p1.push(hexoff.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});

}

if(check == "311")
{

var p1 = p3data
p1.push(hexon.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00, 
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});
}

if(check == "310")
{
var p1 = p3data
p1.push(hexoff.charCodeAt(0))
p1.push(priority.charCodeAt(0))
   serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, 
    id: 0x01, 
    destination64: "0013A200415B8CBA",
    destination16: "fffe", 
    broadcastRadius: 0x00, 
    options: 0x00,
    data: p1 
   };

     xbeeAPI.builder.write(frame_obj);
	serialport.close()

});

}
*/
});





