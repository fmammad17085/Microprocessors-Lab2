  void setup() {
    DDRB |= (1 << DDB5);   // Set PB5 (pin 13, onboard LED) as OUTPUT (00100000, 1 = output)
    DDRD &= ~(1 << DDD2);  // Set PD2 (pin 2) as INPUT (0 is input)
  }

  void loop() {
    if (PIND & (1 << PIND2)) {       // checks if button is pressed, also explained in the report 
      PORTB ^= (1 << PORTB5);        // toggle LED (we use XOR by ^=)
      delay(200);                    // small delay to avoid bouncing
    }
  }
