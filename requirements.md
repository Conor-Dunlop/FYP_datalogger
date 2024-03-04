// this document is incomplete please add more to it <br>
// it good to use as a check list during the project and final report

# block diagram of project

![alt text](res/Blank%20diagram.png)

# datalogger requirements

| requirements                          | hard/soft |
| ------------------------------------- | --------- |
| can handle large tempureture change   | hard      |
| can handle drastic changes in weather | hard      |
| less than $ to produce                | hard      |
| less than $ to run per x time         | hard      |

# high level testing requirements

| requirements                       | hard/soft |
| ---------------------------------- | --------- |
| can recreate the bug trapper       | soft      |
| can take pictures at set intervals | soft      |
| measure weather data               | soft      |

# micro controller requirements

| requirements                   | hard/soft |
| ------------------------------ | --------- |
| sleep mode                     | hard      |
| deep sleep mode                | soft      |
| at least 1 spi bus             | hard      |
| at least 1 I2C bus             | hard      |
| at least x PWMs                | hard      |
| at least x ADC                 | hard      |
| at least x gpio                | hard      |
| can be powered from a battery  | hard      |
| interface with wireless comms  | hard      |
| needs x amount of ram          | hard      |
| has a peak current draw of x   | hard      |
| has an idle current draw of x  | hard      |
| interface with a camera        | soft      |
| interface with a comms modules | soft      |
| output an analogue voltage     | soft      |

# comms requirements

| requirements                                      | hard/soft |
| ------------------------------------------------- | --------- |
| sleep mode                                        | hard      |
| 2 way comms                                       | soft      |
| mesh networking with other dataloggers            | soft      |
| wifi                                              | hard      |
| bluetooth                                         | hard      |
| narrowband (cellular)                             | hard      |
| loRaWan                                           | hard      |
| iridium sateilite comms                           | soft      |
| send data to some cloud based storage/data portal | hard      |
| support multiple over the air comms               | hard      |
| can connect to pre existing networks              | hard      |
| can connect to pre existing networks              | hard      |

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
