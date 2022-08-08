var AWS = require('aws-sdk');
var iotdata = new AWS.IotData({ endpoint: 'a1yj9lgdqxsds2-ats.iot.eu-west-2.amazonaws.com' });

exports.handler = async (event) => {
    console.log("Event => " + JSON.stringify(event));
    
    // await iotdata.getThingShadow({thingName: 'grupo3'}, function(err, data) {
    //   if (err) console.log(err, err.stack); // an error occurred
    //   else     console.log(data);           // successful response
    // });
    
    let led_state = + event["led"]
    
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

