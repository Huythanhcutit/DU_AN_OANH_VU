if (N == "CSK" ) {
      if (TDCSK == 0) {
        Servo3(0, 5);
        TDCSK = 1;
      }
      else {
        Servo3(93, 5);
        TDCSK = 0;
      }
      //   Serial.flush();
    }
    if (N == "FK" ) {
      if (TDFK == 0) {
        digitalWrite(FAN_KHACH, 1);
        TDFK = 1;
      }
      else {
        digitalWrite(FAN_KHACH, 0);
        TDFK = 0;
      }
      //   Serial.flush();
    }
    if (N == "LK" ) {
      if (TDLK == 0) {
        digitalWrite(LED_KHACH, 1);
        TDLK = 1;
      }
      else {
        digitalWrite(LED_KHACH, 0);
        TDLK = 0;
      }
      //   Serial.flush();
    }
