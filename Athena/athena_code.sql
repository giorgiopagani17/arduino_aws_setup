CREATE EXTERNAL TABLE IF NOT EXISTS iot_dati.misure (
  misurazione DOUBLE,
  timestamp STRING,
  user STRING,
)
ROW FORMAT SERDE 'org.openx.data.jsonserde.JsonSerDe'
WITH SERDEPROPERTIES (
  'ignore.malformed.json' = 'true'
) 
LOCATION 's3://nomebucket/'
TBLPROPERTIES ('has_encrypted_data'='false');