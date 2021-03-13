# Imports
import serial
import time
import os.path
import json

# Read config
with open(os.path.dirname(__file__) + "/config.json") as f:
    cfg = json.load(f)

# Assign variables from the config file
port = cfg["port"]
time_out = str(cfg["timeOut"])
interval = cfg["interval"]

# Start serial
ser = serial.Serial(port, 9600)

# Wait for serial to initiate
time.sleep(3)

# Set timeout value and start watchdog
ser.write(time_out.encode())

# Start infinite loop
try:
    while True:
        ser.write(b"R")
        time.sleep(interval)
except:
    pass
finally:
    ser.close()
