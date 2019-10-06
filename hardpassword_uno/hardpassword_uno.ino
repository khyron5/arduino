#define MODIFIER_INDEX 0
#define INPUT_KEY_INDEX 2
#define KEY_RESET       0x00
#define KEY_ESC         0x29
#define SHIFT 0x02
uint8_t keyData[8] = { 0, 0, 0, 0, 0, 0, 0 };
String PASSWORD = "yourpassword";

const char _charmap[95] = {
  '\'',
  '!',
  '"',
  '#',
  '$',
  '%',
  '&',
  '\'',
  '(',
  ')',
  '*',
  '+',
  ',',
  '-',
  '.',
  '/',
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  ':',
  ';',
  '<',
  '=',
  '>',
  '?',
  '@',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z',
  '[',
  '\\',
  ']',
  '^',
  '_',
  '`',
  'a',
  'b',
  'c',
  'd',
  'e',
  'f',
  'g',
  'h',
  'i',
  'j',
  'k',
  'l',
  'm',
  'n',
  'o',
  'p',
  'q',
  'r',
  's',
  't',
  'u',
  'v',
  'w',
  'x',
  'y',
  'z',
  '{',
  '|',
  '}',
  '~'
 };
 
const uint8_t _asciimap[95] =
{
  0x2c,    //  ' '
  0x1e,    // !SHIFT
  0x34,    // "SHIFT
  0x20,    // #SHIFT
  0x21,    // $SHIFT
  0x22,    // %SHIFT
  0x24,    // &SHIFT
  0x34,    // '     
  0x26,    // (SHIFT
  0x27,    // )SHIFT
  0x25,    // *SHIFT
  0x2e,    // +SHIFT
  0x36,          // ,
  0x2d,          // -
  0x37,          // .
  0x38,          // /
  0x27,          // 0
  0x1e,          // 1
  0x1f,          // 2
  0x20,          // 3
  0x21,          // 4
  0x22,          // 5
  0x23,          // 6
  0x24,          // 7
  0x25,          // 8
  0x26,          // 9
  0x33,      // :SHIFT
  0x33,     // ;
  0x36,      // <SHIFT
  0x2e,     // =
  0x37,      // >SHIFT
  0x38,      // ?SHIFT
  0x1f,      // @SHIFT
  0x04,      // ASHIFT
  0x05,      // BSHIFT
  0x06,      // CSHIFT
  0x07,      // DSHIFT
  0x08,      // ESHIFT
  0x09,      // FSHIFT
  0x0a,      // GSHIFT
  0x0b,      // HSHIFT
  0x0c,      // ISHIFT
  0x0d,      // JSHIFT
  0x0e,      // KSHIFT
  0x0f,      // LSHIFT
  0x10,      // MSHIFT
  0x11,      // NSHIFT
  0x12,      // OSHIFT
  0x13,      // PSHIFT
  0x14,      // QSHIFT
  0x15,      // RSHIFT
  0x16,      // SSHIFT
  0x17,      // TSHIFT
  0x18,      // USHIFT
  0x19,      // VSHIFT
  0x1a,      // WSHIFT
  0x1b,      // XSHIFT
  0x1c,      // YSHIFT
  0x1d,      // ZSHIFT
  0x2f,          // [
  0x31,          // bslash
  0x30,          // ]
  0x23,    // ^SHIFT
  0x2d,    // _SHIFT
  0x35,          // `
  0x04,          // a
  0x05,          // b
  0x06,          // c
  0x07,          // d
  0x08,          // e
  0x09,          // f
  0x0a,          // g
  0x0b,          // h
  0x0c,          // i
  0x0d,          // j
  0x0e,          // k
  0x0f,          // l
  0x10,          // m
  0x11,          // n
  0x12,          // o
  0x13,          // p
  0x14,          // q
  0x15,          // r
  0x16,          // s
  0x17,          // t
  0x18,          // u
  0x19,          // v
  0x1a,          // w
  0x1b,          // x
  0x1c,          // y
  0x1d,          // z
  0x2f,    // {SHIFT
  0x31,    // |SHIFT
  0x30,    // }SHIFT
  0x35     // ~SHIFT
};

void handler(uint8_t keycode, uint8_t modifier_code) {
  keyData[MODIFIER_INDEX] = modifier_code;
  keyData[INPUT_KEY_INDEX] = keycode;
  Serial.write(keyData, 8);   // send keypress
  delay(10);
}

void reset() {
  keyData[MODIFIER_INDEX] = KEY_RESET;
  keyData[INPUT_KEY_INDEX] = KEY_RESET;
  Serial.write(keyData, 8);   // release key
}




void setup() {
  Serial.begin(9600);
  delay(2000);
  for (int i=0; i < PASSWORD.length(); i=i+1) {
    for (int j=0; j < sizeof(_charmap); j=j+1) {
      if(PASSWORD[i] == _charmap[j]){
        uint8_t modify = KEY_RESET;
        if((1<=j && j<=6) || (8<=j && j<=11) || j==26 || j==28 || (30<=j && j<=58) || (62<=j && j<=63) || (91<=j && j<=94)){
          modify = 0x02;
        }
        handler(_asciimap[j], modify);
        reset();
        break;
      }
    }
  }
}

void loop() {

}
