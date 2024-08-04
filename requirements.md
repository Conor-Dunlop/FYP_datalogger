// this document is incomplete please add more to it <br>
// it good to use as a check list during the project and final report

# block diagram of project

![alt text](res/Blank%20diagram.png)

# datalogger requirements

| requirements                          | hard/soft | notes                                                                              |
| ------------------------------------- | --------- | ---------------------------------------------------------------------------------- |
| can handle large tempureture change   | hard      | this is done as its required to be outside which can experience large temp changes |
| can handle drastic changes in weather | hard      | "                                                                              "   |
| less than $ to produce                | hard      | this is product cost not development cost                                          |
| less than $ to run per x time         | hard      | this for any subscription based services that might be required                    |

# high level testing requirements

| requirements                       | hard/soft | notes                                            |
| ---------------------------------- | --------- | ------------------------------------------------ |
| can recreate the bug trapper       | soft      | these are functional tests for product baselines |
| can take pictures at set intervals | soft      |
| measure weather data               | soft      |

# micro controller requirements

| requirements                  | hard/soft | notes                                                                    |
| ----------------------------- | --------- | ------------------------------------------------------------------------ |
| sleep mode                    | hard      | required to extend the battery life                                      |
| deep sleep mode               | soft      | ""                                                                       |
| at least 1 spi bus            | hard      | needed for comms as well as other digital based sensors                  |
| at least 1 I2C bus            | hard      | needed for digital based sensors                                         |
| at least x PWMs               | hard      | needed for actuators leds, buzzers, servos, motors                       |
| at least x ADC                | hard      | needed to mesure sensors                                                 |
| at least x gpio               | hard      | for multiplexers and other digital/status interfaces                     |
| can be powered from a battery | hard      | needed for remote operation                                              |
| interface with wireless comms | hard      | required to meet for function req                                        |
| needs x amount of ram         | hard      | for running the program and caching data to be sent                      |
| has a peak current draw of x  | hard      | estamating battery life                                                  |
| has an idel current draw of x | hard      | estamating battery life                                                  |
| interface with a camera       | soft      | soft requirement wanted for taking pictures of birds and insects         |
| interface with comms modules  | soft      | soft since making a comms sheild isnt strictly necessary                 |
| output an analogue voltage    | soft      | should be good to use with like a speaker for bird sounds/warning noises |

# comms requirements

| requirements                                      | hard/soft | notes                                                                       |
| ------------------------------------------------- | --------- | --------------------------------------------------------------------------- |
| sleep mode                                        | hard      | required to extend the battery life                                         |
| 2 way comms                                       | soft      | for receiving sensor data and activating actuators                          |
| mesh networking with other dataloggers            | soft      | for when a narrowabnd interface or a loraWan network isnt available         |
| wifi                                              | soft      | useful for operating within building or urbanized areas with local networks |
| bluetooth                                         | soft      | ""                                                                          |
| narrowband (cellular)                             | hard      | for when a loraWan network isnt doesnt exist and when out in the bush       |
| loRaWan                                           | hard      | needed                                                                      |
| iridium sateilite comms                           | soft      | for when loraWan and cellular isnt practical                                |
| send data to some cloud based storage/data portal | hard      | need to access/store data somehow                                           |
| support multiple over the air comms               | hard      | makes it more modular                                                       |
| can connect to pre existing networks              | hard      | so the product does not need its own network to be setup                    |

base stations/access points? - if needed

# Sensors and board requirements

| requirements                                      | hard/soft |
| ------------------------------------------------- | --------- |
| has a GPS module                                  | soft      |
| has a physical data backup                        | hard      |
| low power shut off                                | hard      |
| camera interface                                  | soft      |
| some common interface for sensor                  | hard      |
| not be larger then XxYmm                          | hard      |
| be able to mount with x fastener                  | hard      |
| way to view error code that isnt leds             | hard      |
| interface with at least 2 "off the shelf" sensors | hard      |
| interface with at least 2 actuators               | hard      |

# Power requiremenets

| requirements                     | hard/soft |
| -------------------------------- | --------- |
| system can last x number of days | hard      |
| low power shut off               | hard      |
| renewable charging               | soft      |
| atleast x volts                  | soft      |
| not impose a fire risk           | hard      |
| tempureture shut off             | soft      |
| external power input             | hard      |

# enclosure requiremenets

| requirements                             | hard/soft |
| ---------------------------------------- | --------- |
| waterproof                               | hard      |
| mount to trees/posts                     | soft      |
| stake in to the ground                   | soft      |
| attatch to rocks                         | soft      |
| attatch to some common mounting standard | soft      |
| can be made to be seen or hidden         | soft      |
| mounting plate for top of fances         | hard      |
| easy to carry/lug                        | hard      |

# storage/database requiremenets

| requirements                         | hard/soft        |
| ------------------------------------ | ---------------- |
| store small amount of data at a time | hard             |
| interface with comms modules         | hard             |
| easy to use                          | hard             |
| hosted in the cloud                  | soft but desired |
| should be an x database              | soft             |

# user interface requiremenets

| requirements                                   | hard/soft |
| ---------------------------------------------- | --------- |
| can see dataloggers on a map                   | soft      |
| see historical data of data loggers            | hard      |
| accessible on the web                          | hard      |
| access to data visualisation tools             | hard      |
| have a content content management system       | soft      |
| interface with the data base                   | hard      |
| control any output devices on each data logger | hard      |
| localisation in te reo maori                   | hard      |

# embedded software requiremenets

| requirements                                      | hard/soft |
| ------------------------------------------------- | --------- |
| modular code blocks for sensors                   | soft      |
| pacer based scheduling                            | soft      |
| put mcu in to sleep state when nothing is happing | soft      |
| show error codes when prompted                    | hard      |
| can handle all off the shelf sensors              | hard      |
| program can be creating from building blocks      | soft      |

# sustainability requiremenets

should discuss where lost devices can be bio degrade back into nature, or should they be strong enough they dont leach out anything

theta_1*​cos(2*pi*f*t+theta_2​)+theta_3​*sin(2*pi*ft+theta_4​)+theta_5
theta_1*cos(2*pi*f*t+theta_2)+theta_3*sin(2*pi*f*t+theta_4)+theta_5