import socket

# === Configuration ===
ESP32_IP = "192.168.4.1"   # <-- Replace with your ESP32's IP address
UDP_PORT = 4210             # Must match the port in your Arduino code

# === Setup UDP socket ===w
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Control your ESP32 robot!")
print("Use W/A/S/D to move, J/L/K for servo, X to stop, Q to quit.\n")

while True:
    cmd = input("Command: ").lower()

    if cmd == 'q':
        print("Exiting...")
        break
    elif cmd in ['w', 'a', 's', 'd', 'x', 'j', 'k', 'l']:
        sock.sendto(cmd.encode(), (ESP32_IP, UDP_PORT))
        print(f"Sent '{cmd}' to ESP32")
    else:
        print("Invalid command. Use W/A/S/D/X/J/K/L or Q to quit.")
