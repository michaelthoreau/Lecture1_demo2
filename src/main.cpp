#include <mbed.h>
#include <USBSerial.h>

USBSerial serial;

DigitalOut led1(LED1);
DigitalOut led2(LED2);

InterruptIn buttonInterrupt(USER_BUTTON);

void sosFunction(uint8_t* sos, uint8_t num) {
  for (uint8_t i = 0;  i < num; i++) {
    // led1 = sos[i];
    led1 = *sos++;
    wait_ms(200);
  }
}


uint8_t* globalPtr;

void buttonISR() {
  led2 = !led2;
  *globalPtr = 1;
}



int main() {

  uint8_t SOS[] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 
        0, 1, 0, 1, 0, 1, 0};

  buttonInterrupt.rise(buttonISR);

  uint8_t count = 0;
  while (1) {

    sosFunction(SOS, sizeof(SOS)/sizeof(uint8_t));


    // uint8_t myInt = 0;
    // globalPtr = &myInt;
    // while (1) {
    //   myInt = myInt;
    //   if (myInt > 0) {
    //     break;
    //   }
    // }

    serial.printf("test: %d\n\r", count++);
    // led2 = !led2;

    wait_ms(200);
    
  }

}













// DigitalOut led1(LED1);
// DigitalOut led2(LED2);

// InterruptIn buttonInterrupt(USER_BUTTON);

// void setLEDviaBuffer1(uint8_t* arr, uint8_t num) {
//   // for (uint8_t i = 0; i < strlen((const char*)arr); i++) {
//   for (uint8_t i = 0; i < num; i++) {
//     led1 = arr[i];
//     wait_ms(500);
//   }
// }

// void setLEDviaBuffer2(uint8_t* arr, uint8_t num) {
//   for (int i = 0; i < num; i++) {
//     led1 = *arr++;
//     wait_ms(500);
//   }
// }

// volatile uint8_t* globalPtr;


// void risingISR(void) {
//   led2 = !led2;
//   *globalPtr = 1;
// }



// int main() {

//   // uint8_t outBuffer[] = {0, 1, 1, 0, 1, 0, 0, 1};
//   uint8_t outBuffer[8] = {0, 1, 1, 0, 1, 0, 0, 1};

//   buttonInterrupt.rise(risingISR);

//   // __disable_irq();
//   // asm("cpsid i");

//   while(1) {
//     // setLEDviaBuffer1(outBuffer, 8);
//     // setLEDviaBuffer2(outBuffer, 8);


//     volatile uint8_t myInt = 0;
//     globalPtr = &myInt;
//     while (1) {
//       if (myInt > 0) {
//         break;
//       }
//     }
    
//     led1 = !led1;
//     wait_ms(100);

    
//   }
// }