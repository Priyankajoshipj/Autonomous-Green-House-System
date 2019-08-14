// app2.use(bodyParser.urlencoded({extended : true}));
app2.use('/', express.static('public'));

var xbeeRx = require('xbee-rx');
app2.get('/', function (req, res) {
	
	var xbee = xbeeRx({
    	serialport: '/dev/ttyUSB0',
    	serialPortOptions: {
        	baudrate: 9600
         },
    	module: "ZigBee"
	});



	xbee.remoteTransmit({
    	destinationId: "Temp Router",
    	data: "010000"
	}).subscribe();
      
});


//app2.listen(7014);