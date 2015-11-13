### Connecting to the Honda ECU ###

![http://home.comcast.net/~keebler65/honda/images/socketsinstalled2.jpg](http://home.comcast.net/~keebler65/honda/images/socketsinstalled2.jpg)

The module is connected to the Honda ecu via its TTL serial port. (CN2 connector label on the PCB, bottom left on the picture above)

Every time it needs a value, a function sends a specific command (or several in a row) to the ECU, one or several bytes are then received and stored in the serial buffer until the function gets it.

Then the value is processed to become human readable.

What the ECU does is read in its memory (ram) to get the value, and send it to the module.

### Connecting to the AEM EMS ###

![https://www.jayracing.com/images/AEM-30-1XXXi.jpg](https://www.jayracing.com/images/AEM-30-1XXXi.jpg)

The AEM works on a "data stream" model. It is connected via a RS232 plug rather than an internal TTL serial.

The module doesn't send anything to the EMS, instead of that, it receives a continuous stream of bytes.
The cool thing with the EMS is that you can specify which data/sensors you want to send through the serial connection.

The EMS sends a header byte, the bytes stream, then the checksum.

The goal is to catch that header byte so you know that the data stream comes next.
I then bufferise the whole stream in an array, and process it to convert the bytes into the actual data.
Prior converting it, each sensor is stored in one byte, that means a 0 to 255 scale. Obviously this is no gonna work for the rpm scale, which is from 0 to 26000.