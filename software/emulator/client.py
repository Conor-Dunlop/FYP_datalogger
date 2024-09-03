# https://www.digitalocean.com/community/tutorials/python-http-client-request-get-post

import env
import http.client
import time


MAX_AMOUNT_SEND = 1

def test_logans():
    data = env.LoganDataFormat.test_startup()
    connection.request("POST", "/logData", env.classToJson(data), headers=env.HEADERS)
    response = connection.getresponse()
    print("Status: {} and reason: {}".format(response.status, response.reason))
    print(response.read())

    for i in range(0, MAX_AMOUNT_SEND):
        data.random_data()
        connection.request("POST", "/logData", env.classToJson(data), headers=env.HEADERS)
        response = connection.getresponse()
        print("Status: {} and reason: {}".format(response.status, response.reason))
        print(response.read())
        time.sleep(1)

def test_chloes(type : str):
    data = env.chloeDataFormat.test_normal_send()
    if type == "float":
        data.data = "0.3"
        data.dataType = "%f"
    if type == "str":
        data.data = "string dawg"
        data.dataType = "%s"
    
    connection.request("POST", "/logData", env.classToJson(data), headers=env.HEADERS)
    response = connection.getresponse()
    print("Status: {} and reason: {}".format(response.status, response.reason))
    print(response.read())

    for i in range(0, MAX_AMOUNT_SEND):
        if type == "int":
            data.random_data_int()
        if type == "float":
            data.random_data_float()
        if type == "str":
            data.random_data_str()
            
        connection.request("POST", "/logData", env.classToJson(data), headers=env.HEADERS)
        response = connection.getresponse()
        print("Status: {} and reason: {}".format(response.status, response.reason))
        print(response.read())
        time.sleep(1)

def test_receive():
    connection.request("GET", "/getAllData", headers=env.HEADERS)
    response = connection.getresponse()
    print("Status: {} and reason: {}".format(response.status, response.reason))
    print(response.read())

def test_logger_receive(logger: str = "testclient"):
    connection.request("GET", f"/getLoggerData?ChosenLogger={logger}", headers=env.HEADERS)
    response = connection.getresponse()
    print("Status: {} and reason: {}".format(response.status, response.reason))
    print(response.read())


if __name__ == "__main__":
    # change the port here, or just set it to null
    connection = http.client.HTTPSConnection(env.IP, env.PORT)
    print(connection)
    #test_logans()
    test_receive()
    #test_chloes("int")
    test_chloes("float")
    #test_chloes("str")
    test_logger_receive()
    connection.close()