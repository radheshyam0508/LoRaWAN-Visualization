from network import LTE
import time
import socket

start = time.ticks_ms()
lte = LTE()
print("\nModem is activated, time needed (s): ", time.ticks_diff(time.ticks_ms(), start)/10000)

start = time.ticks_ms()
lte.attach(band=20, apn="company.iot.dk1.tdc")

while not lte.isattached():
    time.sleep(0.5)
    print(".", end="")
print("\nAttached to the Network!, time needed (s): ", time.ticks_diff(time.ticks_ms(), start)/10000)

start = time.ticks_ms()
lte.connect()       # starting a data section and obtaining an ip address
while not lte.isconnected():
    time.sleep(0.5)
    print("-", end="")
print("Connected to the Network Operator!, time needed (s): ", time.ticks_diff(time.ticks_ms(), start)/1000)


lte.disconnect()     # Dissconnect the module and send at commands
while lte.disconnect():
#time.sleep(0.5)
       print("Disconnected!")
lte.send_at_cmd("AT+CSQ") # Check the Signal Strength
print("-", end="")
