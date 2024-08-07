using Microsoft.Data.SqlClient;
using System.Diagnostics.CodeAnalysis;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// For production scenarios, consider keeping Swagger configurations behind the environment check
//if (app.Environment.IsDevelopment())
//{
app.UseSwagger();
app.UseSwaggerUI();
//}

app.UseHttpsRedirection();

string connectionString = app.Configuration.GetConnectionString("AZURE_SQL_CONNECTIONSTRING")!;

app.MapGet("/getAllData", () => {
    var rows = new List<string>();

    using var conn = new SqlConnection(connectionString);
    conn.Open();

    var command = new SqlCommand("SELECT * FROM DataStorage", conn);
    using SqlDataReader reader = command.ExecuteReader();

    if (reader.HasRows)
    {
        while (reader.Read())
        {
            rows.Add($"{reader.GetValue(0)}, {reader.GetString(1)}, {reader.GetString(2)}, {reader.GetDateTime(3)}, {reader.GetString(4)}, {reader.GetString(5)}"); //id, loggerid, sensorid, receivetime, receiveddata, datatype
        }
    }

    return rows;
})
.WithName("GetAllData")
.WithOpenApi();

app.MapGet("/getLoggerData", (string ChosenLogger) => {
    var rows = new List<string>();

    using var conn = new SqlConnection(connectionString);
    conn.Open();

    var command = new SqlCommand("SELECT * FROM DataStorage WHERE LoggerId = @chosenLogger", conn);
    command.Parameters.Clear();
    command.Parameters.AddWithValue("@chosenLogger", ChosenLogger);
    using SqlDataReader reader = command.ExecuteReader();

    if (reader.HasRows)
    {
        while (reader.Read())
        {
            rows.Add($"{reader.GetValue(0)}, {reader.GetString(1)}, {reader.GetString(2)}, {reader.GetDateTime(3)}, {reader.GetString(4)}, {reader.GetString(5)}"); //id, loggerid, sensorid, receivetime, receiveddata, datatype
        }
    }

    return rows;
})
.WithName("GetLoggerData")
.WithOpenApi();

app.MapPost("/logData", (Datalog datalog) => {
    using var conn = new SqlConnection(connectionString);
    conn.Open();

    var command = new SqlCommand(
        "INSERT INTO DataStorage (LoggerId, SensorId, ReceiveTime, ReceivedData, DataType) VALUES (@loggerID, @sensorID, @timestamp, @data, @datatype)",
        conn);

    command.Parameters.Clear();
    command.Parameters.AddWithValue("@loggerID", datalog.LoggerID);
    command.Parameters.AddWithValue("@sensorID", datalog.SensorID);
    command.Parameters.AddWithValue("@timestamp", datalog.Timestamp);
    command.Parameters.AddWithValue("@data", datalog.Data);
    command.Parameters.AddWithValue("@datatype", datalog.DataType);

    using SqlDataReader reader = command.ExecuteReader();
})
.WithName("LogData")
.WithOpenApi();

app.Run();

public class Datalog
{
    public required string LoggerID { get; set; }
    public required string SensorID { get; set; }
    public DateTime Timestamp { get; set; } = DateTime.Now;
    public required string Data { get; set; }
    public string DataType { get; set; } = "unknown";
}