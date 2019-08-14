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
app1.listen(7015,'192.168.137.230');


var xbeeRx = require('xbee-rx')
var app = express();

/*
var xbee = xbeeRx({

    serialport: '/dev/ttyUSB0',
    serialPortOptions: {
        baudrate: 9600
    },
    module: "ZigBee"
});


app1.use(bodyParser.json());



app1.post('/',function(req,res)
{

var check = req.body["task"]
var check2string = check.toString()
console.log(check)
var add2 = "0013A200410809DD"
var data = [];

for(var i =0; i < add2.length ; i++)
{
	data.push(add2.charCodeAt(i));
}

console.log(data)
if(check == "101")
{
xbee.remoteTransmit({

    destinationId: "IR",

    data:"010110"

}).subscribe();
}

if(check == "100")
{
xbee.remoteTransmit({

    destinationId: "IR",

    data:"010010"

}).subscribe();
}

if(check == "201")
{
xbee.remoteTransmit({

    destinationId: "IR",

    data:"020110"

}).subscribe();
}

if(check == "200")
{
xbee.remoteTransmit({

    destinationId: "IR",

    data:"020010"

}).subscribe();
}

if(check == "301")
{
xbee.remoteTransmit({

    destinationId: "IR",

    data:"030110"

}).subscribe();
}

if(check == "111")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"010110"

}).subscribe();
}

if(check == "110")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"010010"

}).subscribe();
}

if(check == "211")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"020110"

}).subscribe();
}

if(check == "210")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"020010"

}).subscribe();
}

if(check == "311")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"030110"

}).subscribe();
}

if(check == "310")
{
xbee.remoteTransmit({

    destinationId: "LT",

    data:"030010"

}).subscribe();
}

})


//app.listen(7015,'192.168.137.122');


*/

