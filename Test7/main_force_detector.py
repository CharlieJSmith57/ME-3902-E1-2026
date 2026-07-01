from machine import ADC, Pin
import time

# Setting up ADC on Pico GP26
fsr = ADC(Pin(26))

VCC = 3.3  # Pico Voltage

Resistance = 10000.0  # 10k resistor

print("Calibration step...")
time.sleep(1)

while True:

    adc_val = fsr.read_u16() >> 4

    if adc_val > 300:

        v_out = (adc_val * VCC) / 4095.0  # converting to 12-bit scale and computing voltage

        resistance_fsr = Resistance * ((VCC / v_out) - 1.0)

        # calculating conductance in Micro-Siemens

        conductance = 1000000.0 / resistance_fsr

        print(f"ADC Value:{adc_val} | Conductance:{conductance:.2f} uS")

    else:

        print("ADC Value: 0 | Conductance: 0.00 uS")  # No weight

    time.sleep(1)