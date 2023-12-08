import serial
from datetime import datetime

def read_serial_port(port, baud_rate=115200):
    try:
        ser = serial.Serial(port, baud_rate)
        print(f"Reading from serial port {port} at {baud_rate} baud rate...\n")
        
        timestamp = datetime.now().strftime("%Y-%M-%d_%H_%M_%S")
        with open(f"whisker_{timestamp}.csv",'a') as datafile:
            while True:
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")#[:-3]
                line = ser.readline().decode('utf-8').strip()

                if "X" in line:
                    line = line.split(' ')[-1]
                    datafile.write(f"{timestamp},{line}")
                if "Y" in line:
                    line = line.split(' ')[-1]
                    datafile.write(f",{line}\n")

    except serial.SerialException as e:
        print(f"Error: {e}")

    finally:
        if ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":

    serial_port = "/dev/serial/by-id/usb-Raspberry_Pi_Pico_E461184767093A21-if00"
    # serial_port = input("Enter the serial port name (e.g., COM3 or /dev/ttyUSB0): ") or find_serial_port()
    baud_rate = 115200
    # baud_rate = int(input("Enter the baud rate (default is 115200): ") or 115200)

    read_serial_port(serial_port, baud_rate)
