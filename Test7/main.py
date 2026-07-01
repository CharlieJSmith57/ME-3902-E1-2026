import machine
import time

#LED onboard is in GPIO Pin 25

led = machine.Pin(25,machine.Pin.OUT)

print("On board LED Blinking...")

while True:
    led.toggle()
    time.sleep(0.5)
