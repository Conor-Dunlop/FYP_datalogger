
# Current JSON Format

```json
{
    "loggerID" : "string",
    "sensorID" : "string",
    "timestamp" : "datetime",
    "data" : "data",
    "datatype" : "string"
}

```

# Future Format

Will reduce the amount of redundant data being sent and allow for multiple sensor's data to be sent at once.
Optionally, location data can be sent on startup.

### Sent during logger startup:
```json
{
    "loggerID" : "string",
    "location" : "locationdata",
    "sensors" : [
        {"sensorID" : "datatype"},
        {"sensorID" : "datatype"},
        ...
        {"sensorID" : "datatype"},
    ]
}
```

### Sent when logging data:
If timestamp is omitted will store the time that the server receives the data
```json
{
    "loggerID" : "string",
    "data" : [
        {"sensorID" : "data", "timestamp" : "datetime"},
        {"sensorID" : "data"},
        {"sensorID" : "data"},
        ...
        {"sensorID" : "data", "timestamp" : "datetime"}
    ]
}
```

<br><hr><br>

# Current Database Schema
`[NVARCHAR](n)` has a maximum size of `n` chars and uses `2n+2` bytes.

```sql
CREATE TABLE DataStorage
(
    id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWID(),
    LoggerID [NVARCHAR](50) NOT NULL,
    SensorID [NVARCHAR](50) NOT NULL,
    ReceiveTime DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    ReceivedData [NVARCHAR](50) NOT NULL,
    DataType [NVARCHAR](50) NOT NULL
)
```

# Future Database Schema
Tables will need to be added or updated to support the change in JSON format.

`[VARBINARY](n)` has a max length of `n` bytes and uses `n+2` bytes.

Using varbinary instead of nvarchar will be more storage efficient and allow for more data to be sent at a time.

```sql
CREATE TABLE LoggerInfo
(
    LoggerID [NVARCHAR](32) PRIMARY KEY,
    Location geostamp
)
```
```sql
CREATE TABLE SensorInfo
(
    LoggerID [NVARCHAR](32) PARTIAL KEY FOREIGN KEY REFERENCES(LoggerInfo),
    SensorID [NVARCHAR](32) PARTIAL KEY,
    DataType [NVARCHAR](32) NOT NULL
)
```
```sql
CREATE TABLE DataStorage
(
    UUID UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWID(),
    Sensor FOREIGN KEY REFERENCES(SensorInfo),
    LogTime datetime NOT NULL,
    Data [VARBINARY](128) NOT NULL
)
```