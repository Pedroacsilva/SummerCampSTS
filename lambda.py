import boto3
import json
from datetime import datetime

def put_item(table, ts, val: bool):
    table.put_item(
       Item={
            'led': val,
            'sample_time': ts
        }
    )

def lambda_handler(event, context):
    dynamodb = boto3.resource('dynamodb')
    
    table = dynamodb.Table('group_three')
    
    
    led_state = bool(event["state"]["desired"]["led"])
    
    dt = datetime.now()
    ts = int(datetime.timestamp(dt))

    
    print(led_state, ts)
    put_item(table, ts, led_state)

    return {
        'statusCode': 200,
        'body': json.dumps(str(event))
    }

