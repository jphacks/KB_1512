var mqtt = require('mqtt');
var SensorTag = require('sensortag');

var client = mqtt.connect('mqtt://tree:tree@m11.cloudmqtt.com:19539');

client.on('connect', function () {
	client.publish('sensor', "foo");
	SensorTag.discoverAll(function (sensorTag) {
		console.log('Sensor found: ' + sensorTag);
		sensorTag.connectAndSetUp(function (error) {
			if (error)
				console.log("setup:" + error);
			setTimeout(function() {
				sensorTag.enableIrTemperature(function (error) {
					if (error)
						console.log("enableIrTemp" + error);	
					setInterval(function() {
						console.log('polling');
						sensorTag.readIrTemperature(function (error, objectTemperature, ambientTemperature) {
							console.log(ambientTemperature);
						});
					}, 1000);
				});
			}, 3000);
		});
	});
});

