//Motor 
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
int pulso =2; //ponerlos
int rebote= 4;//ponerlos
int distancia;
float tiempo;

//bluethootn

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


void turnLeft(){
 digitalWrite(enM1,HIGH);
 digitalWrite(enM2,LOW);
digitalWrite(enM3,LOW);
 digitalWrite(enM4,HIGH);
   Serial.println("Girando izq");
}
void turnRight(){
    digitalWrite(enM1,LOW);
  digitalWrite(enM2,HIGH);
  
  digitalWrite(enM3,HIGH);
  digitalWrite(enM4,LOW);

  Serial.println("Girando der");
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
  Serial.println("Avanza");
}
void back(){
  digitalWrite(enM1,LOW);
  digitalWrite(enM2,HIGH);

  digitalWrite(enM3,LOW);
  digitalWrite(enM4,HIGH);
    Serial.println("Retrocede");
}
void luz(){
char data = Serial.read();
while(data != 's'){
  digitalWrite(pulso,HIGH);
  tiempo = pulseIn(rebote,HIGH);
  distancia = 0.01715*tiempo;
  if(distancia >= 16){
    int a=analogRead(pinIzq);
    int b=analogRead(pinDer);
    if(a > 900 && b > 900 ){
        go();
     }
    else if(a>900){
       turnRight();
    }
    else if(b>900){
       turnLeft();
    }
    else{
      parar();
     }
  }
  else{
    int a  = (int)analogRead(pinIzq);
    int b=(int)analogRead(pinDer);
    digitalWrite(pulso,HIGH);
    tiempo = pulseIn(rebote,HIGH);
    distancia = 0.01715*tiempo; 
    if(a>900 && distancia>=16){
      
       do{
         digitalWrite(pulso,HIGH);
         tiempo = pulseIn(rebote,HIGH);
         distancia = 0.01715*tiempo;
         turnRight();
        }while(distancia < 10);
        go();
        delay(distancia*1000);
   }
   else if(b>900){
     if(distancia>=16){
    do{
      digitalWrite(pulso,HIGH);
      tiempo = pulseIn(rebote,HIGH);
      distancia = 0.01715*tiempo;
      turnLeft();
    }while(distancia < 16);
    go();
    delay(distancia*1000);     
   }
   parar();
  }
  data = Serial.read();
}
}
}

void manual(){
  char entrada = Serial.read();//obtener entrada
  while(entrada!='s'){
   switch(entrada){
    case 'a'://b
      while(entrada!='b'){
      go();
      entrada = Serial.read();}
      break;
    case 'c'://d
      while(entrada!='d'){
      back();
      entrada = Serial.read();  
      }
      break;
    case 'g'://h
      while(entrada!='h'){
      turnRight();
      entrada = Serial.read();
      }
      break;
    case 'e'://f
      while(entrada!='f'){
      turnLeft();
      entrada = Serial.read(); 
    }
      break;
    default:
      parar();
   }
    entrada = Serial.read();//obtener entrada
  }
  parar();
}


void loop(){
  if(Serial.available()>0){
  char opcion = Serial.read(); //opcion por bluethoot
  Serial.println(opcion);
  switch(opcion)
  {
    case 'i':
      manual();
       break;
     case 'l':
       luz();
       break;
     default:
        parar();
        break;  
  }
  //manual();

  //gira en otro sentido
  } 
}
