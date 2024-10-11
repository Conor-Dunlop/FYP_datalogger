# FYP Meeting Minutes 7/8/24

#### Steve and Josh (red hair) not here.

#### Conor leading, Chloe on minutes.

Opening karakia.

We did progress inspections last week, we got feedback on our presentations.

Steve and Lui want a full demo of system working in 4 weeks, for the final inspection.

Conor has devboard from josh for testing out sending data between boards.

Chloe designed new data format to reduce

Logan got uart working between stm and esp32, setup stm to send data to Chloe, connected to internet as easiest way to connect to gateway, which sends http request to server.
Could use Lora module from one of the devkits (sx chip). 
Josh gets a gateway sends it over. Use esp32 as main processor and sx chip to transmit. Shouldn't need another processor to convert between sx chip, just send between nrf and sx.

Josh hasn't been able to get into smd lab to manufacture board, Lui could do it. Josh booked for monday will do it then.
Nordic using http to turn on/off led and communicate to other boards, getting used to zephyr libraries. Might need help from Chloe with coding.

Conor should be able to use same code to communicate with Arduino as logan used to communicate with esp32 over uart.

Use second uart (pins 11/12?), code is on git - esp32 comms. Should also just be linked on discord.

Josh 2 shows up now.

For project handover would supervisors want us to hand over discord? no, should be documented elsewhere. Should be self explanatory, report vessel for that.

Josh 2 progress - haltex connected to things network, able to pick up public gateway from his house. Wanting to setup temp then sending over to Chloe. Sending between haltex and stm, trying to figure out if you can send directly to sx chip. 
Only have one sx chip, let's get more in, antenna for lora and container. Barry can give mobile gateway to Josh, just plug into ethernet.

Josh and Barry talking about mesh networking, (couldn't really hear over others), any experience sending between nodes to send to gateway?

(There were like three different conversations happening here)

Update on timeline - According to original Gantt should be finishing up test on site and preliminary comms, documentation. (definitely not accurate). . Not up to date Gantt not ideal, should just make table or trello we can all update easily. What do we need to get done before holidays.

Lui may be away during final inspection (week 3).

Presenting in front of peers in final week.

Biggest issue communicating between boards.

Feedback from Lui on presentations - we all spoke well (doesn't really remember to be honest), so probably fine.

Graeme has some feedback - Barry will send to us.

No self monologuing for Logan, post docs are gonna be weird.

Getting to business end of it - hopefully have boards communicating to each other by next week. (Flashing LEDs!!!)

Lui hates bright LEDs. Logan loves them.

Lui thinks might be able to use clock or something to estimate power budget.

Closing karakia.

Take a friday or something and get everyone together to get stuff working.