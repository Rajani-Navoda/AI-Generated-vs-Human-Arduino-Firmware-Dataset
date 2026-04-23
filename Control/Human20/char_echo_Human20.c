char rxchar;

void setup() {

    Serial.begin(9600);

}


void loop() {
 
    if (Serial.available() > 0) {

        rxchar = Serial.read();
        Serial.print(rxchar);
    }
}

/**** END ****/