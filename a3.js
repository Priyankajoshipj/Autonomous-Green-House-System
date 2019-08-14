
'use strict';
const fs = require('fs');

var express = require('express');
var path = require('path');
var bodyParser = require('body-parser');

var app = express();


var SerialPort = require('serialport');
var xbee_api = require('xbee-api');
var C = xbee_api.constants;

var xbeeAPI = new xbee_api.XBeeAPI({
  api_mode: 1
});

var serialport = new SerialPort("/dev/ttyUSB0", {
  baudrate: 9600,
});


var data = [];



function hex2a() {
    var hex = "0013A20041671DAC"//force conversion
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



var strasc = hex2a()

for(var i =0; i < strasc.length ; i++)
{
	data.push(strasc.charCodeAt(i));
}

data.push(hexon.charCodeAt(0))
data.push(priority.charCodeAt(0))
//data.push(hexon.charCodeAt(1))
 
serialport.pipe(xbeeAPI.parser);
xbeeAPI.builder.pipe(serialport);

serialport.on("open",function() {

    var frame_obj = {
    type: 0x10, // xbee_api.constants.FRAME_TYPE.ZIGBEE_TRANSMIT_REQUEST
    id: 0x01, // optional, nextFrameId() is called per default
    destination64: "0013A20041671DAC",
    destination16: "fffe", // optional, "fffe" is default
    broadcastRadius: 0x00, // optional, 0x00 is default
    options: 0x00, // optional, 0x00 is default
    data: data // Can either be string or byte array.
   };

     xbeeAPI.builder.write(frame_obj);

});



