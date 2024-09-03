-- Create the table in the specified schema
CREATE TABLE DataStorage
(
    id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWID(), -- primary key column
    LoggerId [NVARCHAR](50) NOT NULL,
    SensorId [NVARCHAR](50) NOT NULL,
    ReceiveTime DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    ReceivedData [NVARCHAR](50) NOT NULL,
    DataType [NVARCHAR](50) NOT NULL
);
GO