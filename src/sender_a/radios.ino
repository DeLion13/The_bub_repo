void radioSetup() {
  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах
  radio.openWritingPipe(address[0]);   // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(CH_NUM);            // выбираем канал (в котором нет шумов!)
  radio.setPALevel(SIG_POWER);         // уровень мощности передатчика
  radio.setDataRate(SIG_SPEED);        // скорость обмена

  radio.powerUp();         // начать работу
  radio.stopListening();   // не слушаем радиоэфир, мы передатчик
}
