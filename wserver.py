from flask import Flask, jsonify
import sqlite3
from sqlite3 import Error


app = Flask(__name__)
conn = None;



def select_latest_data():
    database = "/Users/Banknote/Desktop/(code)IoT_LoRaWAN_sp-master/IoT_LoRaWAN_sp-master/database/loradata.db" 
    

    with sqlite3.connect(database) as conn:
        cur = conn.cursor()
        cur.execute("SELECT rssi,temp FROM ttndata ORDER BY id DESC LIMIT 1")
        rows = cur.fetchall()

        for row in rows:
            print(row)

        return rows[0]

@app.route('/data')
def hello():
    dbData = select_latest_data()
    d = {}
    d["rssi"] = dbData[0]
    d["temperature"] = dbData[1]
    return jsonify(d)

if __name__ == '__main__':
    app.run()
