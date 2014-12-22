/*
name:LightDinamic Trees
developer:Sergey Savin
Kolibri Media Holding
*/
//Global SECTION
int pinsRadial[5]={2,3,4,5,6};
int pinsHorizontAll[15]={22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
int pinsHorizontRed[5]={22,23,24,25,26};
int pinsHorizontGreen[5]={27,28,29,30,31};
int pinsHorizontBlue[5]={32,33,34,35,36};
int pinsStars[4]={8,9,10,11};
int pinStart = 19;//кнопка приветствия Елочка гори.
int pinCyrcle = 20;//кнопка включения стека паттернов
int pinStop =21;//кнопка полного останова
int pinMainStar = 52;
int pinIceFall = 51;
//--------PRIMITIVES-----------------
//--------Radial---------------------
class Radial{
  public:
    Radial(int pins[(sizeof(pinsRadial)/sizeof(*pinsRadial))]);
    void setNumOfRay(int num_of_rays);
    void setDirection(boolean dir);
    void Step();
    void Blink();
    void Stop();
    void Reset();
  private:
    void lightMaping();
    int pinID[5];
    int numRaysVal;
    int stepVal;//max 5
    boolean lightMap[(sizeof(pinsRadial)/sizeof(*pinsRadial))];
    boolean realLight[(sizeof(pinsRadial)/sizeof(*pinsRadial))];
};
Radial::Radial(int pins[(sizeof(pinsRadial)/sizeof(*pinsRadial))]){
  stepVal=1;//max 5
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){
    pinID[i]=pins[i];
    pinMode(pinID[i], OUTPUT);
  }
  numRaysVal = 3;
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
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){
    lightMap[i]=state;
    counter--;
    if(counter==0){
      counter = numRaysVal;
      state=!state;
    }
  }
}
void Radial::Step(){
  if(stepVal>(sizeof(pinsRadial)/sizeof(*pinsRadial)))stepVal=1;
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){//перенос матрицы
    if((stepVal+i)>(sizeof(pinsRadial)/sizeof(*pinsRadial))){
      realLight[(stepVal+i-1)-(sizeof(pinsRadial)/sizeof(*pinsRadial))] = lightMap[i];
    }
    else{
      realLight[stepVal+i-1] = lightMap[i];
    }    
  }  
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){//Активация апаратной части
    digitalWrite(pinID[i], realLight[i]);
  }
  stepVal++;
}
void Radial::Blink(){  
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){
    lightMap[i]=!lightMap[i];
  }
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){//Активация апаратной части
    digitalWrite(pinID[i], lightMap[i]);
  }
}
void Radial::Stop(){
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){//Активация апаратной части
    digitalWrite(pinID[i], LOW);
  }
}
void Radial::Reset(){
  Stop();
  numRaysVal = 1;
  stepVal=1;
  lightMaping();
}
//------------HORIZONT------------------------
class Horizont{
  public:
    Horizont(int pins[(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll))],int pinsR[(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed))],int pinsG[(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen))],int pinsB[(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue))]);
    void setColor(int color);
    void setMode(boolean mode);
    void setDirection(boolean dir);
    void Step();
    void Dance();
    void Stop();
    void Reset();
  private:
    int PColor;
    boolean PFill;
    boolean PDirection;
    int PPinID[(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll))];
    int PPinRed[(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed))];
    int PPinGreen[(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen))];
    int PPinBlue[(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue))];
    int stepVal;//max 3
    boolean lightMap[(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed))];
};
Horizont::Horizont(int pins[(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll))],int pinsR[(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed))],int pinsG[(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen))],int pinsB[(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue))]){
  for(int i=0;i<(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));i++){
    PPinID[i]=pins[i];
    pinMode(PPinID[i],OUTPUT);
  }
  for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){
    PPinRed[i]=pinsR[i];
  }
  for(int i=0;i<(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen));i++){
    PPinGreen[i]=pinsG[i];
  }
  for(int i=0;i<(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue));i++){
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
  if(PDirection==true&&stepVal>(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed)))stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));
  
  if(!PFill){//Без заполнения
    for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){
      lightMap[i]=false;
    }    
    for(int i=0; i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed)); i++){
      if(stepVal==i+1){
        lightMap[i]=true;
      }
      else;
    }
  }
  else{//С заполнением
    for(int i=0; i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed)); i++){
      if(stepVal==i+1){
        lightMap[i]=!lightMap[i];
      }
      else;
    }
  }
  
  //Render
  Stop();
  for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){
    Serial.print(lightMap[i]);
    
  }
  Serial.println(";");
  
  
  
  switch(PColor){
    case 1:  
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//красные
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        }
      }
      break;
    case 2:    
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//зеленые
      if(lightMap[i]){
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 3:  
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//синие
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        }
      }  
      break;
    case 4:  
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//красные + зеленые
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 5: 
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//красные + синии
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
        }
      }
      break;
    case 6:  
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//синии + зеленые
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 7:  
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){//красные + зеленые + синии
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
  Stop();
  if(PDirection==true&&stepVal>7)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=7;
  switch(stepVal){
    case 1://All Red
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){ 
        digitalWrite(PPinRed[i], HIGH);
      }
      break;
    case 2://All Green
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 3://All Blue
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){ 
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 4://Red+Green
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){ 
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 5://Green+Blue
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){ 
        digitalWrite(PPinGreen[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 6://Red+Blue
      for(int i=0;i<(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));i++){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 7://All
      for(int i=0;i<(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));i++){
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
  for(int i=0;i<(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
  }
}
void Horizont::Reset(){
  PColor=7;
  PFill=false;
  PDirection=true;
  stepVal=1;
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
  if(PDirection==true&&stepVal>(sizeof(pinsStars)/sizeof(*pinsStars)))stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=(sizeof(pinsStars)/sizeof(*pinsStars));
  
  if(!PFill){//Без заполнения
    for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){
      lightMap[i]=false;
    }    
    for(int i=0; i<(sizeof(pinsStars)/sizeof(*pinsStars)); i++){
      if(stepVal==i+1){
        lightMap[i]=true;
      }
      else;
    }
  }
  else{//С заполнением
    for(int i=0; i<(sizeof(pinsStars)/sizeof(*pinsStars)); i++){
      if(stepVal==i+1){
        lightMap[i]=!lightMap[i];
      }
      else;
    }
  }
  
  //Render
  Stop();  
  
  for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){
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
  if(PDirection==true&&stepVal>(sizeof(pinsStars)/sizeof(*pinsStars)))stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=(sizeof(pinsStars)/sizeof(*pinsStars));
  
  if(stepVal%2==0){
    for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
    }
  }
  else{
    for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){
    digitalWrite(PPinID[i], HIGH);
    }
  }
  
  if(PDirection)stepVal++;
  else stepVal--;  
}
void Stars::Start(){
  for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){//обнуляем все
    digitalWrite(PPinID[i], HIGH);
  }
}

void Stars::Stop(){
  for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
  }
}
void Stars::Reset(){
  PFill=false;
  PDirection=true;
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

Radial rad(pinsRadial);
Horizont hor(pinsHorizontAll,pinsHorizontRed,pinsHorizontGreen,pinsHorizontBlue);
Stars stars(pinsStars);
IceFall ice(pinIceFall);
MainStar mainstar(pinMainStar);

int GlobalMode=0;//0-test 1-standby 2-start 3-cyrcle

void FullTest(){
  //Сюда делаем полный перебор каналов
  Serial.println(sizeof(pinsRadial)/sizeof(*pinsRadial));
  Serial.println(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));
  Serial.println(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));
  Serial.println(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen));
  Serial.println(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue));
  Serial.println(sizeof(pinsStars)/sizeof(*pinsStars));

  for(int i=0;i<100;i++){
    ice.Blink();
    mainstar.Blink();
    delay(200);    
  }
  ice.Stop();
  mainstar.Stop();
}


void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  FullTest();
}
void loop(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}


