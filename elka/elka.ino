/*
name:LightDinamic Trees
developer:Sergey Savin
Kolibri Media Holding
*/
//Global SECTION

//--------PRIMITIVES-----------------
//--------Radial---------------------
class Radial{
  public:
    Radial(int pins[5]);
    void setNumOfRay(int num_of_rays);
    void setDirection(boolean dir);
    void Step();
    void Blink();
    void Stop();
  private:
    void lightMaping();
    int pinID[5];
    int numRaysVal;
    int stepVal;//max 5
    boolean lightMap[5];
    boolean realLight[5];
};
Radial::Radial(int pins[5]){
  stepVal=1;//max 5
  for(int i=0;i<5;i++){
    pinID[i]=pins[i];
    pinMode(pinID[i], OUTPUT);
  }
  numRaysVal = 1;
  stepVal=1;
  lightMaping();
}

void Radial::setNumOfRay(int num_of_rays){
  numRaysVal = num_of_rays;
  lightMaping();
}
void Radial::lightMaping(){
  int counter = numRaysVal;
  boolean state = true;
  for(int i=0;i<5;i++){
    lightMap[i]=state;
    counter--;
    if(counter==0){
      counter = numRaysVal;
      state=!state;
    }
  }
}
void Radial::Step(){
  if(stepVal>5)stepVal=1;
  for(int i=0;i<5;i++){//перенос матрицы
    if((stepVal+i)>5){
      realLight[(stepVal+i)-6] = lightMap[i];
    }
    else{
      realLight[stepVal+i-1] = lightMap[i];
    }    
  }  
  for(int i=0;i<5;i++){//Активация апаратной части
    digitalWrite(pinID[i], realLight[i]);
  }
  stepVal++;
}
void Radial::Blink(){  
  for(int i=0;i<5;i++){
    lightMap[i]=!lightMap[i];
  }
  for(int i=0;i<5;i++){//Активация апаратной части
    digitalWrite(pinID[i], lightMap[i]);
  }
}
void Radial::Stop(){
  for(int i=0;i<5;i++){//Активация апаратной части
    digitalWrite(pinID[i], LOW);
  }
}
//------------HORIZONT------------------------
class Horizont{
  public:
    Horizont(int pins[9],int pinsR[3],int pinsG[3],int pinsB[3]);
    void setColor(int color);
    void setMode(boolean mode);
    void setDirection(boolean dir);
    void Step();
    void Dance();
    void Stop();
  private:
    int PColor;
    boolean PFill;
    boolean PDirection;
    int PPinID[9];
    int PPinRed[3];
    int PPinGreen[3];
    int PPinBlue[3];
    int stepVal;//max 3
    boolean lightMap[3];
};
Horizont::Horizont(int pins[9],int pinsR[3],int pinsG[3],int pinsB[3]){
  for(int i=0;i<9;i++){
    PPinID[i]=pins[i];
  }
  for(int i=0;i<3;i++){
    PPinRed[i]=pinsR[i];
  }
  for(int i=0;i<3;i++){
    PPinGreen[i]=pinsG[i];
  }
  for(int i=0;i<3;i++){
    PPinBlue[i]=pinsB[i];
  }
  PColor=7;
  PFill=false;
  PDirection=true;
  stepVal=1;
}
void Horizont::setColor(int color){
  PColor=color;//1,2,3,4,5,6,7
}
void Horizont::setDirection(boolean dir){
  PDirection=dir;
}
void Horizont::setMode(boolean mode){
  PFill=mode;//false=single true=solid fill
}
void Horizont::Step(){
  if(PDirection==true&&stepVal>3)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=3;
  
  if(!PFill){//Без заполнения
    for(int i=0;i<3;i++){
      lightMap[i]=false;
    }    
    for(int i=0; i<3; i++){
      if(stepVal==i+1){
        lightMap[i]=true;
      }
      else;
    }
  }
  else{//С заполнением
    for(int i=0; i<3; i++){
      if(stepVal==i+1){
        lightMap[i]=!lightMap[i];
      }
      else;
    }
  }
  
  //Render
  Stop();
  for(int i=0;i<3;i++){
    Serial.print(lightMap[i]);
    
  }
  Serial.println(";");
  
  
  
  switch(PColor){
    case 1:  
      for(int i=0;i<3;i++){//красные
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        }
      }
      break;
    case 2:    
      for(int i=0;i<3;i++){//зеленые
      if(lightMap[i]){
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 3:  
      for(int i=0;i<3;i++){//синие
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        }
      }  
      break;
    case 4:  
      for(int i=0;i<3;i++){//красные + зеленые
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 5: 
      for(int i=0;i<3;i++){//красные + синии
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
        }
      }
      break;
    case 6:  
      for(int i=0;i<3;i++){//синии + зеленые
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 7:  
      for(int i=0;i<3;i++){//красные + зеленые + синии
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
        }
      }
      break;
    default:
      stepVal=1;
  }
  if(PDirection)stepVal++;
  else stepVal--;  
}

void Horizont::Dance(){
  if(PDirection==true&&stepVal>7)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=7;
  switch(stepVal){
    case 1://All Red
      for(int i=0;i<3;i++){ 
        digitalWrite(PPinRed[i], HIGH);
      }
      break;
    case 2://All Green
      for(int i=0;i<3;i++){
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 3://All Blue
      for(int i=0;i<3;i++){ 
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 4://Red+Green
      for(int i=0;i<3;i++){ 
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 5://Green+Blue
      for(int i=0;i<3;i++){ 
        digitalWrite(PPinGreen[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 6://Red+Blue
      for(int i=0;i<3;i++){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 7://All
      for(int i=0;i<9;i++){
        digitalWrite(PPinID[i], HIGH);
      }
      break; 
    default:
       stepVal=1;
       Stop();
  }
  if(PDirection)stepVal++;
  else stepVal--;
}
void Horizont::Stop(){
  for(int i=0;i<9;i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
  }
}
//------------MainStar-----------------
class MainStar{
  public:
    MainStar(int pin);
    void Blink();
    void Stop();
    void Start();
  private:
    boolean PState;
    int PPinID;
};

MainStar::MainStar(int pin){
  PPinID = pin;
  PState = true;
}
void MainStar::Stop(){
  digitalWrite(PPinID, LOW);
  PState=false;
}
void MainStar::Start(){
  digitalWrite(PPinID, HIGH);
  PState=true;
}
void MainStar::Blink(){
  PState=!PState;
  digitalWrite(PPinID, PState);
}
//------------Icefall-----------------
class IceFall{
  public:
    IceFall(int pin);
    void Blink();
    void Stop();
    void Start();
  private:
    boolean PState;
    int PPinID;
};

IceFall::IceFall(int pin){
  PPinID = pin;
  PState = true;
}
void IceFall::Stop(){
  digitalWrite(PPinID, LOW);
  PState=false;
}
void IceFall::Start(){
  digitalWrite(PPinID, HIGH);
  PState=true;
}
void IceFall::Blink(){
  PState=!PState;
  digitalWrite(PPinID, PState);
}
//------------Stars-----------------
class Stars{
  public:
    Stars(int pins[12]);
    void setMode(boolean mode);
    void Step();
    void Blink();
    void Stop();
    void Start();
    void Reset();
  private:
    boolean PFill;
    boolean PDirection;
    int PPinID[12];
    int stepVal;//max 12
    boolean lightMap[12];
};
Stars::Stars(int pins[12]){
  for(int i=0;i<12;i++){
    PPinID[i]=pins[i];
    pinMode(PPinID[i], OUTPUT);
  }
  PFill=false;
  PDirection=true;
  stepVal=1;
}
void Stars::setMode(boolean mode){
  PFill=mode;//false=single true=solid fill
}
void Stars::Step(){
  if(PDirection==true&&stepVal>12)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=12;
  
  if(!PFill){//Без заполнения
    for(int i=0;i<12;i++){
      lightMap[i]=false;
    }    
    for(int i=0; i<12; i++){
      if(stepVal==i+1){
        lightMap[i]=true;
      }
      else;
    }
  }
  else{//С заполнением
    for(int i=0; i<12; i++){
      if(stepVal==i+1){
        lightMap[i]=!lightMap[i];
      }
      else;
    }
  }
  
  //Render
  Stop();  
  
  for(int i=0;i<12;i++){
   if(lightMap[i]){
     digitalWrite(PPinID[i], HIGH);
    }
   else{
     digitalWrite(PPinID[i], LOW);
   }
  }
  if(PDirection)stepVal++;
  else stepVal--;  
}
void Stars::Blink(){
  if(PDirection==true&&stepVal>12)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=12;
  
  if(stepVal%2==0){
    for(int i=0;i<12;i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
    }
  }
  else{
    for(int i=0;i<12;i++){
    digitalWrite(PPinID[i], HIGH);
    }
  }
  
  if(PDirection)stepVal++;
  else stepVal--;  
}
void Stars::Start(){
  for(int i=0;i<12;i++){//обнуляем все
    digitalWrite(PPinID[i], HIGH);
  }
}

void Stars::Stop(){
  for(int i=0;i<12;i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
    //stepVal=1;
  }
}
void Stars::Reset(){
  stepVal=1;
}
//-------------SUBTREES------------------------
/*class SubTrees{
  public:
    SubTrees(int pinr,int ping,int pinb,int pinstart);
    void Start();
    void Stop();
    void Flash(int color);
  private:
    int PPinR;
    int PPinG;
    int PPinB;
    int PPinStart;
    int PColor;//1.2.3
};
SubTrees::SubTrees(int pinr,int ping,int pinb,int pinstart){
  pinMode(PPinR, OUTPUT);
  pinMode(PPinG, OUTPUT);
  pinMode(PPinB, OUTPUT);
  pinMode(PPinStart, OUTPUT);
  PPinR=pinr;
  PPinG=ping;
  PPinB=pinb;
  PPinStart=pinstart;
  PColor=1;
}
void SubTrees::Flash(int color){
  PColor = color;
  switch(PColor){
  case 1:
    Stop();
    digitalWrite(PPinR, HIGH);
    break;
  case 2:
    Stop();
    digitalWrite(PPinG, HIGH);
    break;
  case 3:
    Stop();
    digitalWrite(PPinB, HIGH);
    break;
  default:
    break;
  }
}

void SubTrees::Start(){
  digitalWrite(PPinStart, HIGH);
}

void SubTrees::Stop(){
  digitalWrite(PPinR, LOW);
  digitalWrite(PPinG, LOW);
  digitalWrite(PPinB, LOW);
  digitalWrite(PPinStart, LOW);
}*/
//--------------------------------------------------
//--------PRIMITIVES END----------------------------

int pinsRadial[5]={3,4,5,6,7};
int pinsHorizontAll[9]={22,23,24,25,26,27,28,29,30};
int pinsHorizontRed[9]={22,25,28};
int pinsHorizontGreen[9]={23,26,29};
int pinsHorizontBlue[9]={24,27,30};
int pinsStars[12]={31,32,33,34,35,36,37,38,39,40,41,42};
Radial rad(pinsRadial);
Horizont hor(pinsHorizontAll,pinsHorizontRed,pinsHorizontGreen,pinsHorizontBlue);
Stars stars(pinsStars);

void PatternOne(){
  stars.setMode(true);
  for(int i=0; i<1000; i++){
    stars.Step();
    delay(100);
  }
  stars.Stop();
  
  
  
/*  
  rad.setNumOfRay(1);
  for(int i=0; i<10; i++){
    rad.Step();
    delay(250);
  }
  rad.Stop();
//-----
  hor.setDirection(false);
  hor.setMode(true);
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(1);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(2);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(3);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(4);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(5);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(6);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(7);
//-------------------------  
  hor.setMode(false);
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(1);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(2);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(3);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(4);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(5);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(6);
  
  for(int i=0; i<30; i++){
    hor.Step();
    delay(150);
  }
  hor.Stop();
  hor.setColor(7);*/
  
  
  //Dance
  /*for(int i=0; i<100; i++){
    hor.Dance();    
    delay(500);
    hor.Stop();
  }*/
  
}

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  PatternOne();
}
void loop(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}



