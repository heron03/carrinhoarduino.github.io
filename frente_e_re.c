// inclusão de bibliotecas.    
#include <Servo.h>    // inclui biblioteca de manipulação de servos motores.    
#include <AFMotor.h>   // inclui biblioteca de manipulação de motores DCs.  
//Definindo os pinos  
#define trigPin A0 //Pino TRIG do sensor no pino analógico A0
#define echoPin A1 //Pino ECHO do sensor no pino analógico A1
#define    A2  // Define o pino do buzzer (Som) no pino ANALÓGICO A0  
AF_DCMotor motor1(1);    // Define o motor1 ligado ao M1  
AF_DCMotor motor2(2);    // Define o motor2 ligado ao M2  
int TempoGirar = 2;//esse é o tempo para o robô girar em 45º com uma bateria de 9v.
int distanciaObstaculo = 40; //distância para o robô parar e recalcular o melhor caminho
int velocidadeMotores = 80; // velocidade que os motores funcionarão na bateria 9v. Para a bateria 9v a velocidade 80 é ideal
Servo servo_ultra_sonico; // nomeando o servo motor    
//variáveis  para o sensor ultrassonico
long duracao;
long distancia_cm=0;
int minimumRange=5; //tempo de resposta do sensor
int maximumRange=200;
// executado na inicialização do Arduino    
void setup(){    
    Serial.begin(9600); // inicializa a comunicação serial para mostrar dados    
    servo_ultra_sonico.attach(10);  // Define o mini servo motor ligado no pino digital 10.    
    pinMode(trigPin, OUTPUT); //define o pino TRIG como saída
    pinMode(echoPin, INPUT);  //define o pino ECHO como entrada
    motor1.setSpeed(velocidadeMotores);     // Define a velocidade para os motores. A velocidade máxima é 255.
    motor2.setSpeed(velocidadeMotores);     //Usamos uma bateria de 9v 450mAh, com ela a velocidade ficou boa. Mas dependendo da bateria utilizada a velocidade deverá ser utilizada. Não use pilhas, pois são fracas
    servo_ultra_sonico.write(90);   // O servo do sensor se inicia a 90 graus (meio)    
    rotacao_Parado;  //inica com os motores parados    
}    
// Função principal do Arduino    
void loop(){    
    int distancia = lerSonar(); // Ler o sensor de distância  
    Serial.print("distancia em cm: ");
    Serial.println(distancia);   // Exibe no serial monitor
    if (distancia > distanciaObstaculo) {  // Se a distância for maior que 20 cm  
    rotacao_Frente(); //robô anda para frente  
    }else{  
        rotacao_Parado();  //para o robô  
        posicionaCarroMelhorCaminho(); //calcula o melhor caminho    
    pensar();    
    }  
}    
// Função para chamar outras funções e definir o que o robô fará  
void pensar(){    
    int distancia = lerSonar(); // Ler o sensor de distância  
    Serial.print("distancia em cm: ");
    Serial.println(distancia);   // Exibe no serial monitor
    if (distancia > distanciaObstaculo) {  // Se a distância for maior que 20 cm  
    rotacao_Frente(); //robô anda para frente  
    }else{  
        rotacao_Parado();  //para o robô  
        posicionaCarroMelhorCaminho(); //calcula o melhor caminho    
    pensar();    
    }  
}  
// Função para ler e calcular a distância do sensor ultrassônico    
int lerSonar(){    
    digitalWrite(trigPin, LOW); //não envia som
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH); //envia som
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW); //não envia o som e espera o retorno do som enviado
    duracao = pulseIn(echoPin,HIGH); //Captura a duração em tempo do retorno do som.
    distancia_cm = duracao/56; //Calcula a distância
    delay(30);  
    return distancia_cm;             // Retorna a distância  
}  
// Função para calcular a distância do centro    
int calcularDistanciaCentro(){    
servo_ultra_sonico.write(90);    
delay(20);  
int leituraDoSonar = lerSonar();  // Ler sensor de distância  
delay(500);  
leituraDoSonar = lerSonar();  
delay(500);  
Serial.print("Distancia do Centro: "); // Exibe no serial  
Serial.println(leituraDoSonar);  
return leituraDoSonar;       // Retorna a distância  
}    

char calculaMelhorDistancia(){    
   
    int centro = calcularDistanciaCentro();    
    int maiorDistancia = 0;  
    char melhorDistancia = '0';        
    melhorDistancia = 'c';    
    maiorDistancia = centro;    
    if (maiorDistancia <= distanciaObstaculo) { //distância limite para parar o robô  
    rotacao_Re();    
    posicionaCarroMelhorCaminho();    
    }    
    return melhorDistancia;    
}    
// Função para colocar o carrinho na melhor distância, isto é, girá-lo para a melhor distância    
void posicionaCarroMelhorCaminho(){    
    char melhorDist = calculaMelhorDistancia();    
    Serial.print("melhor Distancia em cm: ");  
    Serial.println(melhorDist);  
    if (melhorDist == 'c'){    
    pensar();    
    }else{    
    rotacao_Re();    
    }    
}       
// Função para fazer o carro parar    
void rotacao_Parado() {    
    Serial.println(" Motor: Parar ");
    motor1.run(RELEASE); // Motor para  
    motor2.run(RELEASE);  
}    
// Função para fazer o robô andar para frente    
void rotacao_Frente() {    
    Serial.println("Motor: Frente ");  
    motor1.run(FORWARD); // Roda vai para frente  
    motor2.run(FORWARD);  
    delay(50);    
}    
// Função que faz o robô andar para trás e emite som quando ele dá ré    
void rotacao_Re() {    
    Serial.println("Motor: ré ");  
    for (int i=0; i <= 3; i++){
    delay(100);
    motor1.run(BACKWARD);    // Roda vai para trás  
    motor2.run(BACKWARD);    // Roda vai para trás  
   
    }
    rotacao_Parado();    
} 

