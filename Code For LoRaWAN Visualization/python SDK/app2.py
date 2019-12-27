#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Sep  6 21:38:33 2018

@author: manlu
"""

import time
import ttn
import sqlite3
import time
import datetime
import random

temp = ''
rssi = 0



def uplink_callback(msg, client):
    print("Received a message from TTN: ", msg.dev_id)
    #print(msg)
    #print(msg.metadata.gateways)
    print(msg.metadata.gateways[0].rssi)
    print(msg.payload_fields.temperature)

    global temp, rssi

    temp = msg.payload_fields.temperature
    rssi = msg.metadata.gateways[0].rssi
    dynamic_data_entry()
    #print(msg.payload_fields)
    #print(msg.gateways[0].rssi)


def send_ttn_request(mqtt_client):
    mqtt_client.connect()
    print("Waiting for an answer...")
    time.sleep(50)
    mqtt_client.close()


def dynamic_data_entry():
    print("Inserting record into database ...")
    global temp, rssi
    temp1 = temp
    rssi1 = rssi

    conn = sqlite3.connect("/Users/Banknote/Desktop/(code)IoT_LoRaWAN_sp-master/IoT_LoRaWAN_sp-master/database/loradata.db" )
    c = conn.cursor()
    c.execute("INSERT INTO ttndata (rssi, temp) VALUES (?, ?)",
          (rssi1, temp1))
    conn.commit()
    c.close()
    conn.close()


def main():

    i = 0

    app_id = "radhemicrochip"
    access_key = "ttn-account-v2.anvcRy7edUgm8sQuhWfd4YXBCq6X6c2BFU54fgSm5E8"

    handler = ttn.HandlerClient(app_id, access_key)

    # using mqtt client
    mqtt_client = handler.data()
    mqtt_client.set_uplink_callback(uplink_callback)

    # using application manager client
    #app_client =  handler.application()
    #my_app = app_client.get()
    #print(my_app)
    #my_devices = app_client.devices()
    #print(my_devices)

    while(True):
        i = i + 1
        print("Sending request number (%d)" % i)
        send_ttn_request(mqtt_client)

    conn.close()

if __name__ == "__main__":
    # execute only if run as a script
    main()
