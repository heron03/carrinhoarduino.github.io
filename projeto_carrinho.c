#include <Servo.h> 
#include <AFMotor.h>     
#define trigPin
#define echoPin 
AF_DCMotor motor1(1);     
AF_DCMotor motor2(2);     
int TempoGirar = 1;
int distanciaObstaculo = 30;
int velocidadeMotores = 80;
Servo servo_ultra_sonico;
long duracao;
long distancia_cm=0;
int minimumRange=5;
int maximumRange=200;
void setup(){    
    Serial.begin(9600);  
    servo_ultra_sonico.attach(10); 
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    motor1.setSpeed(velocidadeMotores);
    motor2.setSpeed(velocidadeMotores)
    servo_ultra_sonico.write(90);    
    rotacao_Parado;
}    
void loop(){    
    pensar(); 
}    
void pensar(){    
    reposicionaServoSonar();
    int distancia = lerSonar();
    Serial.print("distancia em cm: "); 
    Serial.println(distancia);
    if (distancia > distanciaObstaculo) {
    rotacao_Frente();
    }else{   
        rotacao_Parado();
        posicionaCarroMelhorCaminho(); 
    pensar();    
    }   
}  
int lerSonar(){    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    duracao = pulseIn(echoPin,HIGH);
    distancia_cm = duracao/56;
    delay(30);  

    return distancia_cm;
}   
int calcularDistanciaCentro(){    
servo_ultra_sonico.write(90);    
delay(20);   
int leituraDoSonar = lerSonar(); 
delay(500);   
leituraDoSonar = lerSonar();   
delay(500);   
Serial.print("Distancia do Centro: ");
Serial.println(leituraDoSonar);   
return leituraDoSonar;
}    
int calcularDistanciaDireita(){    
servo_ultra_sonico.write(0);   
delay(200);  
int leituraDoSonar = lerSonar();   
delay(500);   
leituraDoSonar = lerSonar();   
delay(500);   
Serial.print("Distancia da Direita: ");  
Serial.println(leituraDoSonar);   
return leituraDoSonar;    
}    
int calcularDistanciaEsquerda(){    
    servo_ultra_sonico.write(180);   
    delay(200);  
    int leituraDoSonar = lerSonar();   
    delay(500);   
    leituraDoSonar = lerSonar();   
    delay(500);   
    Serial.print("Distancia Esquerda: ");  
    Serial.println(leituraDoSonar);   
    return leituraDoSonar;    
}    
char calculaMelhorDistancia(){    
    int esquerda = calcularDistanciaEsquerda();    
    int centro = calcularDistanciaCentro();    
    int direita = calcularDistanciaDireita();    
    reposicionaServoSonar();    
    int maiorDistancia = 0;   
    char melhorDistancia = '0';     
    if (centro > direita && centro > esquerda){    
    melhorDistancia = 'c';    
    maiorDistancia = centro;    
    }else   
    if (direita > centro && direita > esquerda){    
    melhorDistancia = 'd';    
    maiorDistancia = direita;    
    }else  
    if (esquerda > centro && esquerda > direita){    
    melhorDistancia = 'e';    
    maiorDistancia = esquerda;    
    }    
    if (maiorDistancia <= distanciaObstaculo) { 
    rotacao_Re();    
    posicionaCarroMelhorCaminho();    
    }    
    reposicionaServoSonar();  
    return melhorDistancia;    
}    
void posicionaCarroMelhorCaminho(){    
    char melhorDist = calculaMelhorDistancia();     
    Serial.print("melhor Distancia em cm: ");  
    Serial.println(melhorDist);  
    if (melhorDist == 'c'){    
    pensar();    
    }else  if (melhorDist == 'd'){    
    rotacao_Direita();    
    }else  if (melhorDist == 'e'){    
    rotacao_Esquerda();     
    }else{    
    rotacao_Re();    
    }    
    reposicionaServoSonar();    
}    
void reposicionaServoSonar(){    
    servo_ultra_sonico.write(90);   
    delay(200);   
}    
void rotacao_Parado() {    
    Serial.println(" Motor: Parar ");
    motor1.run(RELEASE); 
    motor2.run(RELEASE);  
}    
void rotacao_Frente() {    
    Serial.println("Motor: Frente ");   
    motor1.run(FORWARD); 
    motor2.run(FORWARD);   
    delay(50);    
}    
void rotacao_Re() {    
    Serial.println("Motor: ré ");  
    for (int i=0; i <= 3; i++){
    delay(100);
    motor1.run(BACKWARD);    
    motor2.run(BACKWARD);    
    delay(100);  
    delay(100);
    } 
    rotacao_Parado();    
}    
void rotacao_Direita() {    
    delay(100);
    motor1.run(BACKWARD);    
    motor2.run(BACKWARD);      
    delay(50);  
    delay(100);
    Serial.println(" Para a direita ");  
    motor1.run(FORWARD); 
    motor2.run(BACKWARD); 
    delay(TempoGirar);    
}    
void rotacao_Esquerda() {    
    delay(100);
    motor1.run(BACKWARD);    
    motor2.run(BACKWARD);   
    delay(50);  
    delay(100);
    Serial.println(" Para a esquerda ");  
    motor1.run(BACKWARD); 
    motor2.run(FORWARD); 
    delay(TempoGirar);    
} 