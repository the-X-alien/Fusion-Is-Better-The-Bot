import socket
from pynput import keyboard
import threading
import time

# === Configuration ===
ESP32_IP = "192.168.4.1"
UDP_PORT = 4210

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Currently pressed keys
pressed_keys = set()

# Map keys to robot commands
key_map = {
    'w': 'w',  # forward
    's': 's',  # backward
    'a': 'd',  # turn left
    'd': 'a',  # turn right
    'r': 'r',  # servo leftwdasdawwsws
    'f': 'f',  # servo centerwlda
    'l': 'l',  # servo rightww
}

# Function to continuously send commands while key is pressed
def command_sender():
    while True:
        if pressed_keys:
            # Take first pressed key from the set (or decide priority)
            key = next(iter(pressed_keys))
            cmd = key_map.get(key)
            if cmd:
                sock.sendto(cmd.encode(), (ESP32_IP, UDP_PORT))
        else:
            # Stop motors if no movement key is pressed
            sock.sendto('x'.encode(), (ESP32_IP, UDP_PORT))
        time.sleep(0.05)  # send commands every 50ms

# Start the sender in a background thread
threading.Thread(target=command_sender, daemon=True).start()

# Keyboard event handlers
def on_press(key):
    try:
        k = key.char.lower()
        if k in key_map:
            pressed_keys.add(k)
    except AttributeError:
        # Special keys
        if key == keyboard.Key.esc:
            print("Exiting...")
            return False

def on_release(key):
    try:
        k = key.char.lower()
        if k in pressed_keys:
            pressed_keys.remove(k)
    except AttributeError:
        pass

# Start listener
with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
