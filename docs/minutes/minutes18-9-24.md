# FYP meeting 18/9/24
Phillipa not here.
Conor leading, Chloe minutes

Trying to get demo ready, progress has been slow, mostly software issues. SPI Conor was using was the wrong one apparently. Issues with ioc file fixed half an hour ago, just need to go home and program it, should fix things for Josh (red hair) too. Most things will hopefully be ready by Friday inspection. 

Haltecs setup to communicate over Lora, ready for Friday. Josh (red hair) board closest to working, if can get Josh (black hair) board working we'll use that instead.

Having issues connecting to the server, thought it was a bad cert but doesn't seem to be the issue. Works on other boards/in python.

Stack on inspection - old board (has uart working) to comms to server. one laptop showing what board is sending and one showing grafana/logs. Probably just use counter for data but could use temp sensor.

Logan looked into battery life, 1ms/minute, can have in sleep mode up to 17hrs maybe longer, theoretically can last for a year but will probably discharge and if LEDs are on will decrease life. Turn off/on in demo while it's running.

Lui doesn't have any charts for battery life etc. Just go with optimal with some battery life factor.

Need nice diagram for overall system. Can show what parts working if not everything's working and show whos doing what.

Just paper, no powerpoints. Final oral inspection can have powerpoint.

Logan will work with Josh(red) to get esp32 communicating with server. two devkits with sx chips, one sends, one receives.

Conor can't program stm at uni because can't find a linker file, try asking phil or bruce for admin to download stm stuff. Could be network file issue. Been biking back and forth from uni and home to program then look on oscilloscope.

Plan for tomorrow: work through it in embedded lab.

Pretty sure reason Josh (black) not working is because of request type, not sure where it should go in nrf code.

Chris Hann probably want mihi and ask about comms, reliability and backups - sd card to store data (theoretically).

Just need to get back to work.