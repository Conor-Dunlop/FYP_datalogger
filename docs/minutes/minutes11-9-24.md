# FYP Minutes 11/9/24
### Joshs not here, Steve not here

Joshes and Conor worked on getting boards made.
Conor had overheating issue on board, fixed with Logan.
Conor got burnt, will now put in holders when turning on.

Relayed before meeting:

Josh (black hair) - SPI placement needs to be checked, having issues with voltage, Logan will talk with them tomorrow. Working on devkit, requesting assistance on software.

Josh (red hair) - nothing major, been working on testing a board, no other updates.

Final inspection need to be ready 20 September, apparently Shayne only said to save one day. Done in parallel, definitely need to prepare.

Conor has working second iteration of the board, have outputs which have been measured with oscilloscope, doesn't know what they mean/if they're good but has read SPI and i2c with waveforms and square waves. Only one LED on board working at this point, not erroring on startup. Temperature sensor seems to be working, but hasn't got serial monitor setup, will setup over next few days.

Logan has been working on power system, finished alkaline battery, looked into solar, found 3 power tracking circuits but going to run past Etzel because doesn't know power stuff, one needs Arduino so won't use and two analog ones, one use same as in solar car and other uses two 555 timers. These won't be built so should focus on other things.

In inspection anything we put up can be questioned, so should be very sure on what we work on, then if they ask about power we can talk about it being a stretch goal.

Chloe got esp32 communicating with the server, still wants to 

Comms board is what we're all waiting on which is what the Joshes are working on. Need to push for that to get done and programmed before inspection. In theory could all meet up Friday to get everything integrated.

Should definitely practice inspection but getting everything working is priority.

Take screenshots, paste into docs, write why you made decisions, etc. So writing report goes easily. 51 pages for final report recommended.

Will need router or maybe phone hotspot to connect esp32 at uc due to authentication and stuff.

If necessary could just use esp32 devkit, but would skip whole LoraWAN and gateway stuff which would not be ideal for inspection, without that part it's too simple and kind of pointless for environmentall monitoring.

May need some plan Bs if without middle part of design of comms board. Barry gave Josh a gateway which should be able to connect with Lora then send to cloud. That gateway has esp32 so could probably just put our code in.

Send email saying to meet up on Friday to everyone. Unfortunately Joshes busy with tests and assignments, and they are working on the stuff we need.

Conor, Logan and Chloe pretty much have something to present. Should have at least two different comms in inspection. May be able to communicate between two esp32s?