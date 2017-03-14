#include <SoftwareSerial.h>// import the serial library
#include <avr/pgmspace.h>
#include <EEPROM.h>

SoftwareSerial Bluetooth(10, 11); // RX, TX

int BluetoothData; 
int btIdx;
String tempText = "";
String text = "";

const PROGMEM boolean letterA[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1
  };

const PROGMEM boolean letterB[] = {
  1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,0,
  1,1,1,1,1,1,0,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,0
  };

const PROGMEM boolean letterC[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0
  };

const PROGMEM boolean letterD[] = {
  1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,0
  };

const PROGMEM boolean letterE[] = {
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,0,0,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,0,0,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1
};

const PROGMEM boolean letterF[] = {
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,0,0,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0
};

const PROGMEM boolean letterG[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,0,0,
  1,1,0,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0
};

const PROGMEM boolean letterH[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1
};

const PROGMEM boolean letterI[] = {
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1
};

const PROGMEM boolean letterJ[] = {
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  1,1,1,1,1,0,0,
  1,1,1,1,0,0,0
};

const PROGMEM boolean letterK[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,1,1,0,
  1,1,1,1,1,0,0,
  1,1,1,1,1,0,0,
  1,1,0,0,1,1,0,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1
};

const PROGMEM boolean letterL[] = {
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1
};

const PROGMEM boolean letterM[] = {
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,1,1,0,0,0,1,1,1,1,
  1,1,0,1,1,0,1,1,0,1,1,
  1,1,0,0,1,1,1,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1
};

const PROGMEM boolean letterN[] = {
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,1,1,0,0,0,0,0,1,1,
  1,1,0,1,1,0,0,0,0,1,1,
  1,1,0,0,1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,0,0,1,1,
  1,1,0,0,0,0,1,1,0,1,1,
  1,1,0,0,0,0,0,1,1,1,1,
  1,1,0,0,0,0,0,0,0,1,1
};

const PROGMEM boolean letterO[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0
};

const PROGMEM boolean letterP[] = {
  1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0,
  1,1,0,0,0,0,0
};

const PROGMEM boolean letterQ[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,1,0,1,1,
  1,1,0,0,1,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,1
};

const PROGMEM boolean letterR[] = {
  1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,0,
  1,1,0,0,1,1,0,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1
};

const PROGMEM boolean letterS[] = {
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  1,1,0,0,0,0,1,
  0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,
  1,0,0,0,0,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0
};

const PROGMEM boolean letterT[] = {
  1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0
};

const PROGMEM boolean letterU[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0
};

const PROGMEM boolean letterV[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  0,1,1,0,1,1,0,
  0,1,1,1,1,1,0,
  0,0,1,1,1,0,0
};

const PROGMEM boolean letterW[] = {
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,0,0,0,0,0,1,1,
  1,1,0,0,1,1,1,0,0,1,1,
  1,1,0,1,1,0,1,1,0,1,1,
  1,1,1,1,0,0,0,1,1,1,1
};

const PROGMEM boolean letterX[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  0,1,1,0,1,1,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,1,1,0,1,1,0,
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1
};

const PROGMEM boolean letterY[] = {
  1,1,0,0,0,1,1,
  1,1,0,0,0,1,1,
  0,1,1,0,1,1,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,
  0,0,1,1,1,0,0
};

const PROGMEM boolean letterZ[] = {
  1,1,1,1,1,1,1,
  1,1,0,0,0,1,1,
  0,0,0,0,1,1,0,
  0,0,0,1,1,0,0,
  0,0,1,1,0,0,0,
  0,1,1,0,0,0,0,
  1,1,0,0,0,1,1,
  1,1,1,1,1,1,1
};

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial.begin(9600);
  
  // initialize digital pin 13 as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  int tmp = 0;
  int idx = 0;
  while(1) {
    tmp = EEPROM.read(idx);
    if(tmp == 13 || tmp == 255) {
      break;
    }
    text += (char) tmp;
    idx++;
  }
  text.toUpperCase();
  //Serial.println(text);

  Bluetooth.begin(9600);
  Bluetooth.println("Enter text:");
}

// the loop function runs over and over again forever
void loop() {  
  int i,j;

  if (Bluetooth.available()){
    BluetoothData = Bluetooth.read();
    if(BluetoothData == 10) {
      tempText.toUpperCase();
      text = tempText;
      tempText = "";
      EEPROM.write(btIdx, 13);
      btIdx = 0;
    }
    else if(BluetoothData != 13) {
      tempText += (char) BluetoothData;
      EEPROM.write(btIdx, BluetoothData);
      btIdx++;
    }
  }

  //Bluetooth.println(text);
  
  for(i=0;i<text.length();i++) {
    switch(text.charAt(i)) {
      case 'A' :
        for(j=0;j<7;j++) {
          showColumn(letterA, j, 7);
          delay(1);
        }
        break;
      case 'B' :
        for(j=0;j<7;j++) {
          showColumn(letterB, j, 7);
          delay(1);
        }
        break;
      case 'C' :
        for(j=0;j<7;j++) {
          showColumn(letterC, j, 7);
          delay(1);
        }
        break;
      case 'D' :
        for(j=0;j<7;j++) {
          showColumn(letterD, j, 7);
          delay(1);
        }
        break;
      case 'E' :
        for(j=0;j<7;j++) {
          showColumn(letterE, j, 7);
          delay(1);
        }
        break;
      case 'F' :
        for(j=0;j<7;j++) {
          showColumn(letterF, j, 7);
          delay(1);
        }
        break;
      case 'G' :
        for(j=0;j<7;j++) {
          showColumn(letterG, j, 7);
          delay(1);
        }
        break;
      case 'H' :
        for(j=0;j<7;j++) {
          showColumn(letterH, j, 7);
          delay(1);
        }
        break;
      case 'I' :
        for(j=0;j<7;j++) {
          showColumn(letterI, j, 7);
          delay(1);
        }
        break;
      case 'J' :
        for(j=0;j<7;j++) {
          showColumn(letterJ, j, 7);
          delay(1);
        }
        break;
      case 'K' :
        for(j=0;j<7;j++) {
          showColumn(letterK, j, 7);
          delay(1);
        }
        break;
      case 'L' :
        for(j=0;j<7;j++) {
          showColumn(letterL, j, 7);
          delay(1);
        }
        break;
      case 'M' :
        for(j=0;j<11;j++) {
          showColumn(letterM, j, 11);
          delay(1);
        }
        break;
      case 'N' :
        for(j=0;j<11;j++) {
          showColumn(letterN, j, 11);
          delay(1);
        }
        break;
      case 'O' :
        for(j=0;j<7;j++) {
          showColumn(letterO, j, 7);
          delay(1);
        }
        break;
      case 'P' :
        for(j=0;j<7;j++) {
          showColumn(letterP, j, 7);
          delay(1);
        }
        break;
      case 'Q' :
        for(j=0;j<7;j++) {
          showColumn(letterQ, j, 7);
          delay(1);
        }
        break;
      case 'R' :
        for(j=0;j<7;j++) {
          showColumn(letterR, j, 7);
          delay(1);
        }
        break;
      case 'S' :
        for(j=0;j<7;j++) {
          showColumn(letterS, j, 7);
          delay(1);
        }
        break;
      case 'T' :
        for(j=0;j<7;j++) {
          showColumn(letterT, j, 7);
          delay(1);
        }
        break;
      case 'U' :
        for(j=0;j<7;j++) {
          showColumn(letterU, j, 7);
          delay(1);
        }
        break;
      case 'V' :
        for(j=0;j<7;j++) {
          showColumn(letterV, j, 7);
          delay(1);
        }
        break;
      case 'W' :
        for(j=0;j<11;j++) {
          showColumn(letterW, j, 11);
          delay(1);
        }
        break;
      case 'X' :
        for(j=0;j<7;j++) {
          showColumn(letterX, j, 7);
          delay(1);
        }
        break;
      case 'Y' :
        for(j=0;j<7;j++) {
          showColumn(letterY, j, 7);
          delay(1);
        }
        break;
      case 'Z' :
        for(j=0;j<7;j++) {
          showColumn(letterZ, j, 7);
          delay(1);
        }
        break;
      case ' ' :
        showSpace(7);
        break;
      case '_' :
        showSpace(7);
        break;
    }
    showSpace(1);
  }
}

void showColumn(const boolean letter[], int colIdx, int width) {
  int i;
  for(i=0;i<8;i++) {
    digitalWrite(i+2, pgm_read_byte_near(letter+(i*width+colIdx)));
  }
}

void showSpace(int width) {
  int i,j;
  for(j=0;j<width;j++) {
    for(i=0;i<8;i++) {
      digitalWrite(i+2, LOW);
    }
    delay(1);
  }
}
