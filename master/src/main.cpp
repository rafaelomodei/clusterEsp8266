#include "header.h"

void setup()
{
    Serial.begin(115200);

    Wifi wifi;
    Database db;

    wifi.begin();

    Serial.print("Data base: ");

    serializeJsonPretty(db.getUnorderedList(1), Serial);
}

void loop()
{
    // o que quer que seja feito continuamente após a solicitação
}
