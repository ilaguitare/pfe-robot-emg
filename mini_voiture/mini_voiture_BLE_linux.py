import asyncio
import threading
import tkinter as tk
from bleak import BleakClient

ROBOT_ADDRESS = "24:EC:4A:CE:3F:D6"
CHARACTERISTIC_UUID = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

client = BleakClient(ROBOT_ADDRESS)

# --- Fonctions BLE ---
async def ble_connect():
    await client.connect()
    if client.is_connected:
        print("✅ Connecté au robot")

async def ble_send(cmd):
    if client.is_connected:
        await client.write_gatt_char(CHARACTERISTIC_UUID, cmd.encode())
        print(f"Commande envoyée: {cmd}")
    else:
        print("❌ Robot non connecté")

def send(cmd):
    asyncio.run_coroutine_threadsafe(ble_send(cmd), loop)

# --- Tkinter GUI ---
root = tk.Tk()
root.title("MiniRobot BLE Controller")

frame = tk.Frame(root)
frame.pack(padx=10, pady=10)

btn_forward = tk.Button(frame, text="↑", width=5, command=lambda: send("F"))
btn_backward = tk.Button(frame, text="↓", width=5, command=lambda: send("B"))
btn_left = tk.Button(frame, text="←", width=5, command=lambda: send("L"))
btn_right = tk.Button(frame, text="→", width=5, command=lambda: send("R"))
btn_stop = tk.Button(frame, text="STOP", width=5, command=lambda: send("S"))

btn_forward.grid(row=0, column=1)
btn_left.grid(row=1, column=0)
btn_stop.grid(row=1, column=1)
btn_right.grid(row=1, column=2)
btn_backward.grid(row=2, column=1)

# --- Boucle asyncio dans un thread ---
loop = asyncio.new_event_loop()

def start_loop(loop):
    asyncio.set_event_loop(loop)
    loop.run_forever()

threading.Thread(target=start_loop, args=(loop,), daemon=True).start()
asyncio.run_coroutine_threadsafe(ble_connect(), loop)

root.mainloop()
