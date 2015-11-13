# Introduction #

RzDash is based on Qt4 plus a couple external libraries:
- Qserialdevice (serial, you guessed it)
- QWT (graphs)

It can run on multiple hardware, Pc, as well as embedded devices like a tablet.

## Why ? ##

I searched on the web for such systems, I did not find anything that had the features I wanted.
It's pretty easy to datalog a Honda ECU, all you need is a custom rom with datalog enabled, a TTL (serial) to USB cable, a laptop with the right software and that's it.

The problem is, I wanted to keep an eye on my engine's constants while driving, without the hassle of having a laptop in my car.

The other reason is that I didn't want to turn my car into a "night club" with 10 gauges flashing on the dash. One screen to display all the info, and only the info I want is way better.