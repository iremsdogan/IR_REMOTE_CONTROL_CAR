#include <IRremote.h>     // IR libraries are added to the program.

const int RECV_PIN = 2;         // The pin of the infrared receiver is determined.
                                // Const means that a value will not change that it is a constant.

IRrecv irrecv(RECV_PIN);  // A new object of type IRrecv is derived.   // Specifies which pin to use.
decode_results results;   // A definition of the results is made.

void setup() 
{
Serial.begin(9600);  // Serial communication is started.
Serial.println("Enabling IR receiver..."); // A notification message is given to the user that the program is running.
irrecv.enableIRIn();  // Initialization of the receiver is provided.
Serial.println("IR receiver activated...");  // Another notification message is given to the user.
}
void loop()
{
if (irrecv.decode(&results)) // The IR signal is decoded and stored in a result as a variable.
                                       // It works if there is a command from the remote.
{                                      // If no command is received, this returns 0.  // Block does not work.
  Serial.println(results.value);       // Prints the incoming command. 
  irrecv.resume();                     // To receive data from the remote again. 
}                                      // If the HEX expression is written after the results.value, the key code
                                       // will be written to the screen in the 16-digit system, 
                                       // otherwise the key code will be written to the screen in the 10-digit system.                 
 delay(100);                           // 100ms delay is created for the program to produce results correctly.
}
