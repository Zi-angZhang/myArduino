#arduino-cli lib install u8g2
arduino-cli compile -b arduino:avr:uno
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno
