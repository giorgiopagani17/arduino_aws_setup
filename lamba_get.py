import boto3
import time

athena = boto3.client('athena')

DATABASE = 'iot_dati'
TABLE = 'misure'
S3_OUTPUT = 's3://giorgioscemo/'

def lambda_handler(event, context):
    query = f"SELECT * FROM {TABLE} ORDER BY timestamp DESC LIMIT 100;"

    response = athena.start_query_execution(
        QueryString=query,
        QueryExecutionContext={'Database': DATABASE},
        ResultConfiguration={'OutputLocation': S3_OUTPUT}
    )

    query_execution_id = response['QueryExecutionId']

    while True:
        result = athena.get_query_execution(QueryExecutionId=query_execution_id)
        status = result['QueryExecution']['Status']['State']

        if status in ['SUCCEEDED', 'FAILED', 'CANCELLED']:
            break
        time.sleep(1)

    if status != 'SUCCEEDED':
        raise Exception(f"Query fallita: {status}")

    result_response = athena.get_query_results(QueryExecutionId=query_execution_id)
    rows = result_response['ResultSet']['Rows']
    headers = [col['VarCharValue'] for col in rows[0]['Data']]
    results = []

    for row in rows[1:]:
        data = row['Data']
        item = {headers[i]: data[i].get('VarCharValue', None) for i in range(len(headers))}
        
        if 'misurazione' in item and item['misurazione'] is not None:
            try:
                item['misurazione'] = float(item['misurazione'])
            except ValueError:
                item['misurazione'] = None
        
        results.append(item)

    return {"data": results}
