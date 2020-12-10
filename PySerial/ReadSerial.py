import serial
import random
import time
import eel

data = {'id': ""}
check_slots = [None] * 4

ser = serial.Serial()


@ eel.expose
def callPort(pt, baud, timeout=1):
    try:
        if(ser.is_open):
            ser.close()
        ser.port = pt
        ser.baudrate = baud
        ser.timeout = timeout
        ser.open()
        while ser.is_open:
            try:
                dataPort = ser.readline().decode("UTF-8")
                data['id'] = dataPort.strip()
                eel.valid()
            except ValueError:
                eel.invalid("<b>Data Invalid</b>: Wrong Port or Poor Signal")
            eel.sleep(0.025)
    except (serial.SerialException, ValueError):
        eel.invalid("Port is Invalid or already Opened <b>Port: </b>" + pt + "<b>   Baudrate: </b>" + str(baud))


@ eel.expose
def get_id():
    return data


@eel.expose
def get_check_slots():
    return check_slots


@ eel.expose
def park_in_slot(slot, id):
    check_slots[slot] = id
    print("Slot id: ", slot)
    ser.write(str(slot).encode())


@eel.expose
def get_car_out():
    try:
        index = check_slots.index(data['id'])
        check_slots[index] = None
        ser.write(str(index + 4).encode())
        return index
    except ValueError:
        return -1


my_options = {
    'mode': "chrome",  # or "chrome-app",
    'host': 'localhost',
    'port': 8020,
    'chromeFlags': ["--browser-startup-dialog"]
}
eel.init("web")
try:
    eel.start("main.html", block=True)
except (SystemExit, MemoryError, KeyboardInterrupt):
    pass
