# simple ESP32 based uart repeater

Use PlatformIO IDE extension in vscode to build and upload to the board.

this repeats any uart message send to UART 2 which uses:
RX = GPIO : 16
TX = GPIO : 17
and will repeat that message over the software serial over USB