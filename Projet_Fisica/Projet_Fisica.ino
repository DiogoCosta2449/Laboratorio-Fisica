#include <Arduino_BMI270_BMM150.h>  // Sensor IMU (acelerômetro, giroscópio, magnetômetro)
#include <Arduino_LPS22HB.h>        // Sensor de pressão barométrica
#include <Arduino_HS300x.h>         // Sensor de temperatura e umidade (HS300x)

float temperature, humidity, pressure, x, y, z;
unsigned long previousMillis = 0;  // Armazena o último tempo de execução
const long interval = 2000;        // Intervalo de 2 segundos (2000 ms)

String csvHeader = "Timestamp,Temperature (C),Humidity (%),Pressure (hPa),Acc X,Acc Y,Acc Z\n";
String csvData = csvHeader;        // Dados em CSV, começando pelo cabeçalho

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Inicializar os sensores
  if (!IMU.begin()) {
    Serial.println("Falha ao inicializar o IMU!");
    while (1);
  }

  if (!BARO.begin()) {
    Serial.println("Falha ao inicializar o sensor de pressão!");
    while (1);
  }

  if (!HS300x.begin()) {
    Serial.println("Falha ao inicializar o sensor de temperatura e umidade!");
    while (1);
  }

  Serial.println("Sensores inicializados com sucesso!");
  Serial.println(csvHeader); // Exibir cabeçalho no monitor serial
}

void loop() {
  unsigned long currentMillis = millis();

  // Executa apenas a cada 2 segundos
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Leitura dos sensores
    temperature = HS300x.readTemperature();
    humidity = HS300x.readHumidity();
    pressure = BARO.readPressure();

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);
    }

    // Armazenar os dados no formato CSV
    String row = String(currentMillis / 1000.0) + "," + String(temperature) + "," +
                 String(humidity) + "," + String(pressure) + "," +
                 String(x) + "," + String(y) + "," + String(z) + "\n";
    csvData += row;

    // Enviar dados ao monitor serial com o formato especificado
    Serial.print("Timestamp: ");
    Serial.print(currentMillis / 1000.0);
    Serial.println(" s");

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" ºC");

    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Pressão: ");
    Serial.print(pressure);
    Serial.println(" hPa");

    Serial.print("Aceleração X: ");
    Serial.print(x);
    Serial.println(" m/s²");

    Serial.print("Aceleração Y: ");
    Serial.print(y);
    Serial.println(" m/s²");

    Serial.print("Aceleração Z: ");
    Serial.print(z);
    Serial.println(" m/s²");

    Serial.println("-------------------------");
  }
}
