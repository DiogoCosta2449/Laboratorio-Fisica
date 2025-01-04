#include <Arduino_BMI270_BMM150.h>  // Sensor IMU (acelerômetro, giroscópio, magnetômetro)
#include <Arduino_LPS22HB.h>        // Sensor de pressão barométrica
#include <Arduino_HS300x.h>         // Sensor de temperatura e umidade (HS300x)

// Variáveis globais
float temperature, humidity, pressure, x, y, z, gx, gy, gz, mx, my, mz;
unsigned long previousMillis = 0;  // Armazena o último tempo de execução
const long interval = 1000;        // Intervalo de 1 segundos (1000 ms)

// Variável para armazenar dados em formato CSV
String csvHeader = "Timestamp (s),Temperature (C),Humidity (%),Pressure (hPa),Acc X,Acc Y,Acc Z,Gyro X,Gyro Y,Gyro Z,Mag X,Mag Y,Mag Z\n";
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

  // Executa apenas a cada 1 segundo
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Leitura dos sensores
    temperature = HS300x.readTemperature();
    humidity = HS300x.readHumidity();
    pressure = BARO.readPressure();

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);
    }

    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(gx, gy, gz);
    }

    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(mx, my, mz);
    }

    // Timestamp em segundos
    float timestamp = currentMillis / 1000.0;

    // Exibir dados no monitor serial
    Serial.print("Timestamp: ");
    Serial.print(timestamp);
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

    Serial.print("Giroscópio X: ");
    Serial.print(gx);
    Serial.println(" º/s");

    Serial.print("Giroscópio Y: ");
    Serial.print(gy);
    Serial.println(" º/s");

    Serial.print("Giroscópio Z: ");
    Serial.print(gz);
    Serial.println(" º/s");

    Serial.print("Magnetômetro X: ");
    Serial.print(mx);
    Serial.println(" µT");

    Serial.print("Magnetômetro Y: ");
    Serial.print(my);
    Serial.println(" µT");

    Serial.print("Magnetômetro Z: ");
    Serial.print(mz);
    Serial.println(" µT");

    // Armazenar os dados no formato CSV
    csvData += String(timestamp) + "," + String(temperature) + "," + String(humidity) + "," + String(pressure) + ","
               + String(x) + "," + String(y) + "," + String(z) + "," + String(gx) + "," + String(gy) + "," + String(gz) + ","
               + String(mx) + "," + String(my) + "," + String(mz) + "\n";
    
    // Exibir a separação de blocos no monitor serial
    Serial.println("-------------------------");

    // Exibir CSV no monitor serial
    // Serial.print(csvData); // Para exibir todos os dados CSV no monitor serial
    // Se quiser armazenar ou enviar esses dados, pode fazer isso aqui
    // Por exemplo, salvando em um cartão SD ou enviando para um servidor.
  }
}
