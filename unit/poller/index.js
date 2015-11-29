var mqtt = require('mqtt');
var SensorTag = require('sensortag');

var client = mqtt.connect('mqtt://tree:tree@m11.cloudmqtt.com:19539');

client.on('connect', function () {
	SensorTag.discoverAll(function (sensorTag) {
		console.log('Sensor found: ' + sensorTag);
		sensorTag.connectAndSetUp(function (error) {
			if (error)
				console.log("setup:" + error);
			setTimeout(function() {
				sensorTag.enableHumidity(function (error) {
					if (error)
						console.log("enableIrTemp" + error);	
					setInterval(function() {
						var data = {
							'uuid': 0,
							'temperature': 0,
							'humidity': 0
						};
						console.log('polling');
						sensorTag.readHumidity(function (error, temperature, humidity) {
							console.log("temp: " + temperature);
							data['temperature'] = temperature;
							console.log("humidity :" + humidity);
							data['humidity'] = humidity;
							client.publish('sensor', JSON.stringify(data));
							console.log(JSON.stringify(data));
						});
					}, 6000);
				});
			}, 3000);
		});
	});
});

