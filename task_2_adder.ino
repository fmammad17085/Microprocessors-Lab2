
void setup() {
  Serial.begin(9600); //talk 9600 symbols per second

uint8_t R18;  // C++ variable for printing, u means only positive numbers (0-255), 8 bits fits the size of our registers

asm volatile ( //inline assembly block, run this code exactly as said
    "ldi r16, 5\n\t" // ldi = load immediate, put the number directly into this register, so now r16 = 5
    "ldi r17, 8\n\t" // r17 = 8
    "add r16, r17\n\t" // r16 = r16 + r17 = 13
    "mov r18, r16\n\t"    // copy r16 to r18, now "store in r18" is satisfied 
    "mov %0, r18\n\t"     // "%0" is a placeholder, move the value in r18 to first output (R18)
    : "=r" (R18)          // "=r" means output, store it in a register. "R18" means that the C++ variable R18 will get this value
    :                     // no inputs
    : "r16", "r17", "r18" // clobbered: do not use r16, r17, r18
);

  //result printer here

  Serial.print("Result = "); 
  Serial.println(R18); 
}

void loop() {
  // nothing
}



