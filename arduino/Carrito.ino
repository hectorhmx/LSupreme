int pinVel = 9;//Pin enable
int enM1 = 3;//input1  2
int enM2 = 6; //input2 7
 
int pinVel2 = 10;
int enM3 = 11;//input3 
int enM4 = 5;//input4 
//Luz
int pinIzq = A5;
int pinDer = A4;
//detenerse
int pulso =1;
int rebote= 2;
int distancia;
float tiempo;

void setup(){
  pinMode(pinVel,OUTPUT);//Determina la velocidad
  pinMode(enM1,OUTPUT); 
  pinMode(enM2,OUTPUT);
  analogWrite(pinVel,250);
  //Motor 2
  pinMode(pinVel2,OUTPUT);
  pinMode(enM3,OUTPUT);
  pinMode(enM4,OUTPUT);
  analogWrite(pinVel2,250);
  //Luz
  pinMode(pinIzq,INPUT);
  pinMode(pinDer,INPUT);
  Serial.begin(9600);
  //detenerse
  pinMode(pulso,OUTPUT);
  pinMode(rebote,INPUT);
}

void turnLeft(int tiempo){
 digitalWrite(enM1,HIGH);
 digitalWrite(enM2,LOW);

digitalWrite(enM3,LOW);
 digitalWrite(enM4,HIGH);
}
void turnRight(int tiempo){
    digitalWrite(enM1,LOW);
  digitalWrite(enM2,HIGH);
  
  digitalWrite(enM3,HIGH);
  digitalWrite(enM4,LOW);

}
void parar(){
  digitalWrite(enM1,LOW);
  digitalWrite(enM2,LOW);
  
  digitalWrite(enM3,LOW);
  digitalWrite(enM4,LOW);
  
}
void go(){
  digitalWrite(enM1,HIGH);
  digitalWrite(enM2,LOW);
  
  digitalWrite(enM3,HIGH);
  digitalWrite(enM4,LOW);
}
void back(){
  digitalWrite(enM1,LOW);
  digitalWrite(enM2,HIGH);

  digitalWrite(enM3,LOW);
  digitalWrite(enM4,HIGH);
}



void loop(){
  //gira en un sentido
/*  if(digitalRead(pinIzq) == HIGH or digitalRead(pinDer == HIGH)){
    if(digitalRead(pinIzq) == LOW){
      turnLeft(1000);
    }
    else if(digitalRead(pinDer) == LOW){
      turnRight(1000);
    }
    else{
      go(1000);
    }
  }*/
  digitalWrite(pulso,HIGH);
  tiempo = pulseIn(rebote,HIGH);
  distancia = 0.01715*tiempo;
  if(distancia >= 8){
  int a  = (int)analogRead(pinIzq);
  int b=(int)analogRead(pinDer);
  if(a > 900 && b > 900 ){
      Serial.print("Pin izq ");
      Serial.println(a);
      Serial.print("Pin der ");
      Serial.println(b);
    go();
    Serial.println("Avanzando");
  }
  else if(a<800   && b<800){
   back();
   Serial.println("Retrocediendo"); 
  }
  else{
  parar();
  }
  }
  else{
    Serial.println("Limite");
   parar(); 
    
  }
  
  //gira en otro sentido
  
}

