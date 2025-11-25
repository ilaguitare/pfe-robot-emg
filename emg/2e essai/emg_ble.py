import bluetooth
import time
from machine import ADC, Pin

esp32_ble = bluetooth.BLE()
esp32_ble.active(True)

ROBOT_SERVICE_UUID = bluetooth.UUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E")
ROBOT_CHAR_UUID = bluetooth.UUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E")
ROBOT_ADDR = b'\x24\xEC\x4A\xCE\x3F\xD6'  # format b'\xXX'

adc = ADC(Pin(36))  # exemple: EMG sur GPIO36

threshold = 150   # À ajuster selon ton traitement
window = []
prevVal = 0

def connect_and_send(cmd):
    # Connecte en BLE au robot et envoie 'cmd'
    conn = esp32_ble.gap_connect(0, ROBOT_ADDR)
    time.sleep(1)
    esp32_ble.gattc_write(conn, ROBOT_CHAR_UUID, cmd.encode())
    # Optionnel: déconnexion
    esp32_ble.gap_disconnect(conn)

while True:
    val = adc.read()
    filtered = val - prevVal
    prevVal = val
    absval = abs(filtered)
    window.append(absval)
    if len(window) > 10:
        window.pop(0)
    smooth = sum(window) // len(window)
    if smooth > threshold:  # contraction détectée
        connect_and_send('F')
        print('Contraction! Avance!')
        time.sleep(1) # Pour éviter répétition
    time.sleep_ms(30)