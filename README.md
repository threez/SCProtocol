# SCProtocol (Simple Command Protocol)

This is a simple protocol helper to send commands to the arduino. It is much less complex and has much less code than other communication protocols for the arduino. It has this limitations:

* The command is allways the first byte (max. 255 commands possible)
* The length of the command must be known in advance
* The command data are always passed as a char array (since the length is known before it is not passed to the method again)

## Installation

Extract a ZIP of the library in the arduinos library folder.

## Example

    #include <SCProtocol.h>

    SCProtocol scProtocol = SCProtocol();

    void checkCallback(char* data) {
      Serial.println("OK AwesomeApp Version: 0.0.1");
    }

    void addTwo(char* data) {
      short a = data[0] - '0';
      short b = data[1] - '0'; 
      Serial.print("OK ");
      Serial.println(a + b);
    }

    void setup() {
      Serial.begin(9600);
      scProtocol.attach('C', checkCallback, 0);
      scProtocol.attach('+', addTwo, 2);
    }

    void loop() {
      while(Serial.available()) scProtocol.process(Serial.read());
    }
    
### Adding a method

The following method should be called by the library.
	
    void checkCallback(char* data) {
      Serial.println("OK AwesomeApp Version: 0.0.1");
    }

To attach it, we specify a command name (first byte) the callback function we defined above and the number of bytes we expect. If there are no bytes (*0*). The passed data array will be *NULL* if the command has 0 bytes data length.

    scProtocol.attach('C', checkCallback, 0);


### Result in a SerialPort session:

If the code is uploaded to the arduino, one can use the serial console to test the interface. 

*(Take care, there are now new lines at the end of the command)*

    -> "C"
    <- "OK AwesomeApp Version: 0.0.1\n"
    -> "+12"
    <- "OK 3\n"
    -> "+99"
    <- "OK 18\n"
    -> "X"
    <- "BAD command unknown\n"

