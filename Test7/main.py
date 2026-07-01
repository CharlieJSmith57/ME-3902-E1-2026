from machine import ADC, Pin, PWM
import time

# Setting up ADC on Pico GP26
fsr = ADC(Pin(26))

VCC = 3.3  # Pico Voltage

Resistance = 10000.0  # 10k resistor

# print("Calibration step...")
# time.sleep(1)

# Setting up Servo
servo = PWM(Pin(15))
servo.freq(50)

while True:

    adc_val = fsr.read_u16() >> 4

    if adc_val > 2000:   # <-- tuned for YOUR sensor; lecture used 30

        v_out = (adc_val * VCC) / 4095.0  # convert to 12-bit scale, compute voltage

        if v_out <= 0:
            v_out = 0.001

        resistance_fsr = Resistance * ((VCC / v_out) - 1.0)

        if resistance_fsr <= 0:
            resistance_fsr = 0.001

        # calculating conductance in Micro-Siemens
        conductance = 1000000.0 / resistance_fsr

        if conductance < 1000:
            # rotate to 45 deg
            angle = 45
            duty = int(1638 + (angle / 180.0) * (8192 - 1638))
            servo.duty_u16(duty)

        elif conductance < 5000:
            angle = 90
            duty = int(1638 + (angle / 180.0) * (8192 - 1638))
            servo.duty_u16(duty)

        print(f"ADC Value:{adc_val} | Conductance:{conductance:.2f} uS")

    else:

        # print("ADC Value: 0 | Conductance: 0.00 uS")  # No weight
        print("No finger press, hence servo is not actuated")

    time.sleep(1)