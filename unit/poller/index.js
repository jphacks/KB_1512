var mqtt = require('mqtt');
var SensorTag = require('sensortag');
var uuid = require('node-uuid');
var fs = require('fs');
var http = require('http');

var unit_id;

fs.exists('/opt/mori/uuid',  function(exists) {
	if (!exists) {
		console.log('First time startup, generating uuid');
		var gen_id = uuid.v4();
		fs.writeFile('/opt/mori/uuid', gen_id, 'utf8', function(error) {
			if (error)
				console.log('FATAL ERROR!');
			console.log('uuid saved');
			var post_data = require('querystring').stringify({
				'uuid': unit_id
			});
			var options = {
				hostname: 'example.com',
				port: 80,
				path: '/device/registration',
				headers: {
					'Content-Type': 'application/x-www-form-urlencoded',
					'Content-Length': post_data.length
				}
			};
			var req = http.request(options, function(res) {
				res.setEncoding('utf8');
				res.on('data', function(chunk) {
					console.log('BODY: ' + chunk);
				});
			});
			req.on('error', function(e) {
				console.log(e);
			});
			req.write(post_data);
			req.end();
		});
		unit_id = gen_id;
	} else {
		fs.readFile('/opt/mori/uuid', 'utf8', function (err, data) {
			unit_id = data;
			console.log(unit_id);
		});
	}
});

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
							'uuid': unit_id,
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
						http.get({
							hostname: 'example.com',
							port: 80,
							path: '/command/' + unit_id,
							agent: false
						}, function(res) {
							if (res.) {
								
							}
						});
					}, 6000);
				});
			}, 3000);
		});
	});
});

