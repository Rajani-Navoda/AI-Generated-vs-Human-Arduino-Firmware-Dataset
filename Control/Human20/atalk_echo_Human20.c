#define DATA_SIZE_MAX 32
#define MSG_ENCODER BASE16
#define SPEED 9600
#define RECEIVE_TIMEOUT 5000


#include <aTalk.h>

#include "atalk_serial.h"


struct aTalk *atalk;
uint8_t data[DATA_SIZE_MAX];
uint8_t data_size;
int error;


void setup() {

  /* init aTalk */
  atalk = atalk_init(DATA_SIZE_MAX,MSG_ENCODER);
  if (atalk == NULL) {
    Serial.println("ERROR: atalk_init failed to allocate aTalk struc.");
    exit(1);
  }
  
  /* init serial link */
  error = atalk_serial_init(atalk,SPEED,RECEIVE_TIMEOUT);
  if (error) {
    Serial.println("ERROR: atalk_loop_init failed to allocate Queue struc.");
    exit(1);
  }

}


void loop() {
    
  /* receive data */
  error = atalk_receive(atalk,data,&data_size);
  
  /* if data is correctly received, echo it. */
  if (error == ATALK_RECEIVE_SUCCESS | error == ATALK_SEQ_NUM_ERROR)
    atalk_send(atalk,data,data_size);

}