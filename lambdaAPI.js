var AWS = require('aws-sdk');
var iotdata = new AWS.IotData({ endpoint: 'a1yj9lgdqxsds2-ats.iot.eu-west-2.amazonaws.com' });

exports.handler = async (event) => {
    console.log("Event => " + JSON.stringify(event));

    let led_state = JSON.parse(event["body"])["led"]
    
    led_state = led_state ? 1 : 0

    console.log(led_state)
    
    var params = {
        topic: "$aws/things/grupo3/shadow/update",
        payload: JSON.stringify({"state": {"desired": {"led": led_state}}}),
    };

    let res = await iotdata.publish(params, function(err, data) {
        if (err) {
            console.log("ERROR => " + JSON.stringify(err));
            return {
                "statusCode": 400,
                "error": JSON.stringify(err),
            }
        }
        else {
            console.log("Success");
            return {
                "statusCode": 200
            }
        }
    }).promise();
    
    return res;
    
};

