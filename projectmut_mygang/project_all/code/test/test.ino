// กำหนดขาเชื่อมต่อกับ TCRT5000
const int TCRT1_PIN = 10;   // TCRT5000 ตัวที่ 1 เชื่อมต่อที่ขา D10
const int TCRT2_PIN = 11;   // TCRT5000 ตัวที่ 2 เชื่อมต่อที่ขา D11

// กำหนดขาเชื่อมต่อกับ L298N Motor Driver
const int IN1 = 3;
const int IN2 = 4;
const int ENA = 2;

const int IN3 = 5;
const int IN4 = 6;
const int ENB = 7;

// กำหนดความเร็วของมอเตอร์ (0-255)
const int speedMotorA = 200;
const int speedMotorB = 200;

#define TRIG_PIN 8  // ขา Trig ของ Ultrasonic Sensor
#define ECHO_PIN 9  // ขา Echo ของ Ultrasonic Sensor

void setup() {
  pinMode(TCRT1_PIN, INPUT);
  pinMode(TCRT2_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

   pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);  // เปิด Serial Monitor
}

void loop() {
  int tcrt1Value = digitalRead(TCRT1_PIN);  // อ่านค่าจาก TCRT5000 ตัวที่ 1
  int tcrt2Value = digitalRead(TCRT2_PIN);  // อ่านค่าจาก TCRT5000 ตัวที่ 2
 long duration;
  int distance;


  // ส่งสัญญาณไปยัง Trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // อ่านค่าจาก Echo และคำนวณระยะทาง (cm)
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 

 if (distance > 0 && distance <= 20) {  // ถ้าระยะ ≤ 20 cm → มอเตอร์เดินหน้า
    Serial.println("🔹 Motor ON (เดินหน้า)");
    moveForward();
    delay(500);
  }

  else if (tcrt1Value == HIGH) {
    Serial.println("a");  // แสดงค่า "a" เมื่อเจอสีขาว
    moveForward();
    delay(200); 
    stopMotor() ; 
    delay(500);   // ถอยหลัง
  }
  else if (tcrt2Value == HIGH) {
    Serial.println("b");  // แสดงค่า "b" เมื่อเจอสีขาว
    moveBackward();
    delay(200); 
    stopMotor() ;
    delay(500);       // เดินหน้า
  }
  else {
    Serial.println("s");
    stopMotor();  // ถ้าไม่เจออะไรเลยให้หยุด
  }





  delay(100);  // หน่วงเวลาเพื่อความเสถียร



}

// ฟังก์ชันถอยหลัง (ใช้ IN1, IN2, ENA)
void moveBackward() {
  analogWrite(ENB, speedMotorB);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ฟังก์ชันเดินหน้า (ใช้ IN3, IN4, ENB)
void moveForward() {
  analogWrite(ENB, speedMotorB);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ฟังก์ชันหยุดมอเตอร์
void stopMotor() {
  Serial.println("s");
 

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
