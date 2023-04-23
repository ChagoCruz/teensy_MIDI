#include <config.h>
#include <Control_Surface.h>
#include <ResponsiveAnalogRead.h>

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

const int maxTransposition = 4;
const int minTransposition = -1 * maxTransposition;
const int transpositionSemitones = 12;
Transposer<minTransposition, maxTransposition>transposer(transpositionSemitones);

//keyboard notes section
const AddressMatrix<2, 14> noteAddresses = {{
                                                {1, 54, 56, 58, 1, 61, 63, 1, 66, 68, 70, 1, 73, 75},
                                                {53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76},  
                                            }};

Bankable::NoteButtonMatrix<2, 14> noteButtonMatrix = {
    transposer,
    {ROW_3, ROW_4}, // row pins
    {COL_0, COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, COL_9, COL_10, COL_11, COL_12, COL_13},    // column pins
    noteAddresses,    // address matrix
    CHANNEL_1,    // channel and cable number
};

//top row buttons section
const AddressMatrix<1,11> presetAddresses = {{
                                                {59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76}
                                            }};

Bankable::NoteButtonMatrix<1, 11> presetButtonMatrix = {
    transposer,
    {ROW_2}, // row pins
    {COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, COL_9, COL_10, COL_11, COL_12, COL_13},    // column pins
    presetAddresses,    // address matrix
    CHANNEL_1,    // channel and cable number
};

void setup() {
    Serial.begin(9600); 
    Control_Surface.begin(); // Initialize Control Surface
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Control_Surface.loop(); // Update the Control Surface
    Serial.print("noteButtonMatrix");
    digitalWrite(LED_BUILTIN, HIGH);
    //delay(20);
}