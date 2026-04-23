#define LINE_LEN_MAX 256
#define NEWLINE '\n'


byte line[LINE_LEN_MAX];
int line_len;

void setup() {

  Serial.begin(9600);

}

void loop() {

  /* read line by line */
  line_len = Serial.readBytesUntil(NEWLINE,line,LINE_LEN_MAX);
 
  /* if no error ... */
  if (line_len > 0) {

    /* add line terminator stripped by read */
    line[line_len] = '\n';

    /* echo received line */
    Serial.write(line,line_len+1);      
  } 
}

/**** END ****/