void setup() {
  Serial.begin(9600); //talk 9600 symbols per second

  uint8_t result; //C++ variable for printing, u means only positive numbers (0-255), 8 bits fits the size of our registers
  uint8_t sreg;   //C++ variable, SREG is status register, it stores flags (bits that tell the CPU what happened after calculations)
  
  // Zero Flag (Z) - is the result exactly zero? 1 = yes, 0 = no, not zero.
  // Carry Flag (C) - Did the substaction borrow (or add overflow)? 1 = yes, 0 = no, it did not

  asm volatile ( //inline assembly block, run this code exactly as said
    "ldi r16, 50\n\t"   // ldi = load immediate, put the number directly into this register, so now r16 = 50
    "ldi r17, 200\n\t"   // r17 = 200
    "sub r16, r17\n\t"   // r16 = r16 - r17 = 50 - 200 (8-bit wrap). in 8-bits this is 50 - 200 + 256 = 106. C becomes 1, it borrows to perform this operation. Z = 0, 106 ≠ 0.
    //we cannot move the value of SREG directly. CPU registers and I/O registers are different. mov is for CPU registers, in is for I/O registers
    "in __tmp_reg__, __SREG__ \n\t"  // "in" = read from "I/O" register, "SREG" = status register, "__tmp_reg__" = special temporary register (r0). Copies the CPU flags into a temporary register.
    "mov %1, __tmp_reg__       \n\t" // move SREG to second output (first is result, second is sreg)
    "mov %0, r16               \n\t" // move result to first C variable (it is "result")
    : "=r"(result), "=r"(sreg)       // outputs
    :                                 // no inputs
    : "r16", "r17"                    // clobbered registers: do not use those.
  );

  // Extract flags from SREG
  bool Z = (sreg & (1 << 1));   // "bool" = either true or false (1, 0). "1 << 1" = shift left by 1 bit, 00000010. Keeps only 1 bit of sreg
  bool C = (sreg & (1 << 0));   // "1 << 0", 00000001

  // Print results
  Serial.print("Result = ");
  Serial.println(result);        // 8-bit wrapped result

  Serial.print("SREG (bin) = ");
  Serial.println(sreg, BIN); // bin = binary

  Serial.print("Z (zero) = ");
  Serial.println(Z);

  Serial.print("C (carry/borrow) = ");
  Serial.println(C);
}

void loop() {
  // nothing to do here

  
}


