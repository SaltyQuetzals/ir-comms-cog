/**
 * Modified example of examples/SimpleReceiver.cpp from https://github.com/Arduino-IRremote/Arduino-IRremote
 * Rather than just outputting to the serial monitor, 
 * this secondary board will output a signal to the primary 
 * board to indicate that it got something. 
 */
#include <IRremote.h>
#define IR_RECEIVE_PIN 3
#define OUTPUT_PIN 4

void setup()
{
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    /*
     * Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
     */
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
    pinMode(OUTPUT_PIN, OUTPUT);
    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
}

void loop()
{
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode())
    {

        // Print a short summary of received data
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN)
        {
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value
        digitalWrite(OUTPUT_PIN, HIGH);
        delay(60);
    } else {
        digitalWrite(OUTPUT_PIN, LOW);
    }
}
