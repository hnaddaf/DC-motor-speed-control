int encoderPinA = 2;
int encoderPinB = 3;
int en1 = 9;
int en2 = 10;
int a;
int umabed;
long k = 0;
long Tstart = 0;
double RPM;
double Time;
double Tm;
double e;
double ehestory;
double output;
double NofR;
double TforSampling;
double newNofR;
double pastNofR = 0;
double Vrps;
double u;
double input;
double samplingtime = 78;
double uhestory;
double pe = 0;
volatile long encoderCount = 0;
void setup() {
Serial.begin (9600);
pinMode(encoderPinA, INPUT);
pinMode(encoderPinB, INPUT);
digitalWrite(encoderPinA, HIGH);
digitalWrite(encoderPinB, HIGH);
attachInterrupt(0, Encoder, CHANGE);
achInterrupt(att 1, Encoder, CHANGE);
input = 2;
e = 0;
u = 0;
ehestory = 0;
uhestory = 0;
}
void loop() {
Time = millis();
Tm = Time / 60000.0;
umabed = (255 / 12) * u;
analogWrite(en1, umabed);
analogWrite(en2, 0);
if (Serial.available() == !a) {
input = Serial.parseFloat();
}
a++;
if (millis() - Tstart >= 100) {
long currentTime;
currentTime = millis() - Tstart;
TforSampling = currentTime / 60000.0;
NofR = (encoderCount / 80160.0 );
newNofR = NofR - pastNofR;
RPM = (newNofR / TforSampling);
Vrps = RPM * (2 * 3.1415) / 60;
pastNofR = newNofR;
Tstart = currentTime;
output = Vrps;
e = input - output;
pe = (e / input) * 100;
u = uhestory + (e + ehestory) * 0.01057 + 0.0040 * (e - ehestory);
//u= uhestory + 1.1 * (e - ehestory);
// u = uhestory + (e + ehestory) * 0.013464 + 0.40 * (e - ehestory);
if (u > 12) {
u = 12;
}
21
if (u < 0) {
u = 0;
}
ehestory = e;
uhestory = u;
Serial.print("input=");
Serial.println(input);
Serial.print("output=");
Serial.println(output);
Serial.print("%erorr=");
Serial.println(pe);
Serial.print("input voltage to the motor=");
Serial.println(u);
Serial.print("spped in RPM=");
Serial.println(RPM);
}
}
void Encoder() {
encoderCount++;
}