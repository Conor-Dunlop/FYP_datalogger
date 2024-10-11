FYP Meeting Minutes 7/5/24
No Steve or Lui
Josh (black hair) chair, Chloe Minutes
Josh iterated on his design, based it on documentation, added test points, different form factors for better routing, wiggly lines so no reflections and stuff, playing around with different footprints, 2 designs on same board so can snap off.
Devkit from Nordic, has all the comms, and another devkit with sensors and stuff, can do what we want but very expensive and complicated. Don't have but would be nice.
Could put tiny temp/pressure/humidity sensor on main board.
End of week, finishing that design, making sure everyone understands decisions, component availability, etc.
Other Josh altered PCB so can daisy chain to devkit, easier programming, trying to compile but running into issues with embed OS, when done can start sending to server.
Online compiler no work, currently using windows, use linux instead.
Integration between teams.
Logan will give main boards to comms team and Conor
Conor needs to work with comms team for data layer, send info over SPI.
Need to discuss data format, Give names to ADC channels, etc.
Conor busy with other things, still planning to design code and get cmake and stuff to work. Look into linux.
Logan still needs parts, will check parts store/Lui, will upload simple blink script, going over board and noting down features he wants. Want to move i/o to seperate pcb + put screen and stuff, change out digital pins for power cutoff, for camera found IC which works with SPI and high-speed. Going to change round a couple pins on comms module to have interrupts. Some spare enable pins, directly connect comms modules to battery module, decoupling. 
Currently board could work just need to change labelling, etc.
Don't currently meet minimum requirements.
Timeline of board 2: hopefully send off by start of study week.
Chloe working on getting some test data on server and visualised.
Doesn't seem to be any weird formats for gps and stuff.
Progress report due in 3 weeks. Don't make too long. Use appendices. Can copy paste intro.
Josh 2 compilation problems - check git, mbed usually just works, might have wrong board set? talk with philip hoff, send git to rest of us so we can look it over (user the hivemind)