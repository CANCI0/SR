from flask import Flask, jsonify, request
from flask_cors import CORS
import random

app = Flask(__name__)
CORS(app)

SENSORS = [
    {"id": 1, "ip": "192.168.1.101", "location": [43.36079454669606, -5.843575937900081], "name": "Sensor Joker"},
    {"id": 2, "ip": "192.168.1.102", "location": [43.36164505168543, -5.850684022721297], "name": "Sensor San Francisco"}
]

def generate_sensor_data():
    data = []
    for sensor in SENSORS:
        data.append({
            "id": sensor["id"],
            "ip": sensor["ip"],
            "name": sensor["name"],
            "location": sensor["location"],
            "temperature": round(random.uniform(15, 35), 1),  # Temp entre 15 y 35°C
            "humidity": round(random.uniform(40, 90), 1),     # Humedad entre 40% y 90%
        })
    return data

@app.route('/sensors', methods=['GET'])
def get_sensors():
    # Retorna datos de sensores simulados
    return jsonify(generate_sensor_data())

@app.route('/control', methods=['POST'])
def control_sensor():
    data = request.json
    sensor_ip = data.get("ip")
    command = data.get("command")
    # Simula el control del LED
    if sensor_ip and command in ["ON", "OFF"]:
        return jsonify({"status": "success", "message": f"LED en sensor {sensor_ip} está {command}"})
    return jsonify({"status": "error", "message": "Parámetros inválidos"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
