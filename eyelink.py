import serial
import pyautogui

ser = serial.Serial("COM27", 9600, timeout=0.25)  # Change your port name COM... and your baudrate

def retrieveData():
    return ser.readline().strip()  # Strip any leading/trailing whitespace

x = 0
y = 0

while True:
    try:
        data = retrieveData().decode()  # Convert bytes to string
        if not data:
            continue  # Skip empty lines

        if data == 'l':
            x -= 1
        elif data == 'r':
            x += 1
        elif data == 'u':
            y -= 1
        elif data == 'd':
            y += 1
        elif data == 'a':
            pyautogui.click(button='right')
        elif data == 'b':
            pyautogui.click(button='left')
        elif data == 'q':
            break

        pyautogui.moveTo(x, y)
    except serial.SerialException:
        # Handle serial port errors
        print("Serial port error occurred. Exiting.")
        break
    except pyautogui.FailSafeException:
        # Handle mouse cursor moving out of screen
        pass
