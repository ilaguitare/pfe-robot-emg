import asyncio
import tkinter as tk
from bleak import BleakClient

ROBOT_ADDRESS = "24:EC:4A:CE:3F:D6"
CHARACTERISTIC_UUID = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

# Fonction pour envoyer une commande
async def send_command(cmd):
    async with BleakClient(ROBOT_ADDRESS) as client:
        if client.is_connected:
            await client.write_gatt_char(CHARACTERISTIC_UUID, cmd.encode())
            print(f"Commande envoyée: {cmd}")

# Wrapper pour Tkinter (asyncio + Tkinter)
def send(cmd):
    asyncio.run(send_command(cmd))

# Interface graphique Tkinter
root = tk.Tk()
root.title("MiciRobot BLE Controller")

frame = tk.Frame(root)
frame.pack(padx=10, pady=10)

# Boutons directionnels
btn_forward = tk.Button(frame, text="↑", width=5, command=lambda: send("F"))
btn_backward = tk.Button(frame, text="↓", width=5, command=lambda: send("B"))
btn_left = tk.Button(frame, text="←", width=5, command=lambda: send("L"))
btn_right = tk.Button(frame, text="→", width=5, command=lambda: send("R"))
btn_stop = tk.Button(frame, text="STOP", width=5, command=lambda: send("S"))

# Placement simple
btn_forward.grid(row=0, column=1)
btn_left.grid(row=1, column=0)
btn_stop.grid(row=1, column=1)
btn_right.grid(row=1, column=2)
btn_backward.grid(row=2, column=1)

root.mainloop()
