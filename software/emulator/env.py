from typing import Optional, Any
from datetime import datetime
import random

# i define the port here for testing on a local machine
# but server will use an srv record and it wont be needed
# if you are connecting to the server, set PORT = none
#PORT = 8008
#IP = "127.0.0.1"
PORT = None
IP = "dataloggerapi.azurewebsites.net"
HEADERS = {"Host": IP, "Content-Type": "application/json", "accept": "*/*"}
    
class chloeDataFormat:
    def __init__(self, loggerID, sensorID, timestamp, data, dataType) -> None:
        self.loggerID   : str      = loggerID 
        self.sensorID   : str      = sensorID
        self.timestamp  : datetime = timestamp # yes this is a string, but datetime makes more sense here
        self.data       : str      = data
        self.dataType   : str      = dataType

    @classmethod
    def test_normal_send(self):
        return chloeDataFormat(
            "testclient",
            "sensor1",
            getTime(),
            "42",
            "%d",
        )

    def random_data_int(self):
        self.data = str(random.randint(0, 255))
        self.timestamp = getTime()

    def random_data_float(self):
        self.data = str(random.random()*200)
        self.timestamp = getTime()
    
    def random_data_str(self):
        self.data = ["OK", "Working", "Broken", "OverTemp"][random.randint(0, 3)]
        self.timestamp = getTime()

class LoganDataFormat:
    def __init__(self, loggerID, timestamp, location, sensors) -> None:
        self.loggerID   : str            = loggerID
        self.timestamp  : datetime       = timestamp # yes this is a string, but datetime makes more sense here
        self.location   : Optional[str]  = location
        self.sensors    : dict[str, str] = sensors 

    @classmethod
    def test_startup(self):
        return LoganDataFormat(
            "testclient",
            getTime(),
            "0,0",
            {
                # dont know how to implemnet this yet but its used for
                # determining wether its start up data, if say the datalogger
                # was reloacted, and sensors were changed but it still had the same id
                "state"   : "true", #this line is optional
                # normal sensors
                "sensor1" : "%d",    
                "sensor2" : "%f",   
                "sensor3" : "%s",
                #...
            }
        )
    
    @classmethod
    def test_normal_send(self):
        return LoganDataFormat(
            "testclient",
            getTime(),
            "0,0",
            {
                "sensor1" : 10,
                "sensor2" : 22.45,
                "sensor3" : "working",
            }
        )
    
    def random_data(self):
        self.sensors = {
                "sensor1" : random.randint(0, 255),
                "sensor2" : random.random()*200,
                "sensor3" : ["OK", "Working", "Broken", "OverTemp"][random.randint(0, 3)],
        }        
        self.timestamp = getTime()

def classToJson(cls : Any) -> str:
    return str(cls.__dict__).replace("'", '"') 

def getTime() -> str:
    return str(datetime.now()).replace(" ", "T")

if __name__ == "__main__":
    Cdata = chloeDataFormat.test_normal_send()
    LSdata = LoganDataFormat.test_startup()
    Ldata = LoganDataFormat.test_normal_send()
    print(classToJson(Cdata))
    print(classToJson(LSdata))
    print(classToJson(Ldata))
