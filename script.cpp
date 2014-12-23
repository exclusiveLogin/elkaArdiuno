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
    void Start();
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
void Radial::Start(){
  for(int i=0;i<(sizeof(pinsRadial)/sizeof(*pinsRadial));i++){//Активация апаратной части
    digitalWrite(pinID[i], HIGH);
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
    void Start();
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
void Horizont::Start(){
  for(int i=0;i<(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));i++){
    digitalWrite(PPinID[i], HIGH);
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
    Stars(int pins[(sizeof(pinsStars)/sizeof(*pinsStars))]);
    void setMode(boolean mode);
    void setDirection(boolean dir);
    void Step();
    void Blink();
    void Stop();
    void Start();
    void Reset();
  private:
    boolean PFill;
    boolean PDirection;
    int PPinID[(sizeof(pinsStars)/sizeof(*pinsStars))];
    int stepVal;
    boolean lightMap[(sizeof(pinsStars)/sizeof(*pinsStars))];
};
Stars::Stars(int pins[(sizeof(pinsStars)/sizeof(*pinsStars))]){
  for(int i=0;i<(sizeof(pinsStars)/sizeof(*pinsStars));i++){
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
void Stars::setDirection(boolean dir){
  PDirection=dir;//false=reverse true=forward
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
//--------PRIMITIVES END----------------------------

//--------Objects init------------------------------
Radial rad(pinsRadial);
Horizont hor(pinsHorizontAll,pinsHorizontRed,pinsHorizontGreen,pinsHorizontBlue);
Stars stars(pinsStars);
IceFall ice(pinIceFall);
MainStar mainstar(pinMainStar);

int GlobalMode=0;//0-test 1-standby 2-start 3-cyrcle

void FullTest(){
  //Первичный тест системы
  Serial.println("Wait 10 seconds");
  Serial.println("System preparing...");
  digitalWrite(13, HIGH);
  delay(10000);
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Starting...");
  digitalWrite(13, LOW);
  delay(2500);
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Preparing for full test");
  digitalWrite(13, HIGH);
  delay(2500);
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Num of Radial chanels: ");
  Serial.print(sizeof(pinsRadial)/sizeof(*pinsRadial));
  delay(1000);
  Serial.println("Num of Horizontal loop ALL chanels: ");
  Serial.print(sizeof(pinsHorizontAll)/sizeof(*pinsHorizontAll));
  delay(1000);
  Serial.println("Num of Horizontal loop RED chanels: ");
  Serial.print(sizeof(pinsHorizontRed)/sizeof(*pinsHorizontRed));
  delay(1000);
  Serial.println("Num of Horizontal loop GREEN chanels: ");
  Serial.print(sizeof(pinsHorizontGreen)/sizeof(*pinsHorizontGreen));
  delay(1000);
  Serial.println("Num of Horizontal loop BLUE chanels: ");
  Serial.print(sizeof(pinsHorizontBlue)/sizeof(*pinsHorizontBlue));
  delay(1000);
  Serial.println("Num of STARS chanels: ");
  Serial.print(sizeof(pinsStars)/sizeof(*pinsStars));
  delay(1000);
  Serial.println("Reseting ALL FX");
  digitalWrite(13, LOW);
  rad.Reset();
  hor.Reset();
  stars.Reset();
  Serial.println("FX reseted");
  Serial.println("Testing Hardware IO");
  Serial.println("Radial TEST");
  digitalWrite(13, HIGH);
  delay(3000);
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  //-----------------------------------------
  Serial.println("Radial loop 50 steps 1 preset");
  rad.setNumOfRay(1);
  for(int i=0;i<50;i++){
    rad.Step();
    delay(500);    
  }
  rad.Stop();
  rad.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Radial loop 50 steps 2 preset");
  rad.setNumOfRay(2);
  for(int i=0;i<50;i++){
    rad.Step();
    delay(500);    
  }
  rad.Stop();
  rad.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Radial blinks 50 steps 3 preset");
  rad.setNumOfRay(3);
  for(int i=0;i<50;i++){
    rad.Blink();
    delay(500);    
  }
  rad.Stop();
  rad.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Radial blinks 50 steps 4 preset");
  rad.setNumOfRay(4);
  for(int i=0;i<50;i++){
    rad.Blink();
    delay(500);    
  }
  rad.Stop();
  rad.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Radial blinks 50 steps 5 preset");
  rad.setNumOfRay(5);
  for(int i=0;i<50;i++){
    rad.Blink();
    delay(500);    
  }
  rad.Stop();
  rad.Reset();
  //-----------------------------------------  
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  digitalWrite(13, LOW);
  Serial.println("Horizont TEST");
  delay(3000);
  digitalWrite(13, HIGH);
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Horizont loop 50 steps");
  for(int i=0;i<50;i++){
    hor.Step();
    delay(500);    
  }
  hor.Stop();
  hor.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Horizont loop 50 steps with fill");
  for(int i=0;i<50;i++){
    hor.Step();
    delay(500);    
  }
  hor.Stop();
  hor.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Horizont Dance 50 steps");
  for(int i=0;i<50;i++){
    hor.Dance();
    delay(500);    
  }
  hor.Stop();
  hor.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Horizont Start");
  hor.Start();
  delay(2000);
  hor.Stop();
  hor.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  digitalWrite(13, LOW);  
  Serial.println("Stars TEST");
  delay(3000);
  digitalWrite(13, HIGH);
  //----------------------------------------- 
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Stars loop 50 steps without fill");
  for(int i=0;i<50;i++){
    stars.Step();
    delay(500);    
  }
  stars.Stop();
  stars.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Stars loop 50 steps without fill REVERSE");
  stars.setDirection(false);
  for(int i=0;i<50;i++){
    stars.Step();
    delay(500);    
  }
  stars.Stop();
  stars.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Stars loop 50 steps with fill");
  stars.setMode(true);
  for(int i=0;i<50;i++){
    stars.Step();
    delay(500);
  }
  stars.Stop();
  stars.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Stars loop 50 steps with fill REVERSE");
  stars.setMode(true);
  stars.setDirection(false);
  for(int i=0;i<50;i++){
    stars.Step();
    delay(500);
  }
  stars.Stop();
  stars.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("Stars Blinks 50 steps");
  for(int i=0;i<50;i++){
    stars.Blink();
    delay(500);    
  }
  stars.Stop();
  stars.Reset();
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("MainStar TEST");
  delay(1000);
  mainstar.Start();
  Serial.println("Main Star is ON");
  delay(1000);
  mainstar.Stop();
  Serial.println("Main Star is OFF");
  delay(1000);
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------
  Serial.println("IceFall TEST");
  delay(1000);
  ice.Start();
  Serial.println("IceFall is ON");
  delay(1000);
  ice.Stop();
  Serial.println("IceFall is OFF");
  delay(1000);
  //-----------------------------------------
  //--------------------------------
  if(GlobalMode){
    Serial.println("Test aborted");
    return;
  }
  //--------------------------------  
  Serial.println("Stress TEST");
  for(int i=0; i<10; i++){
    if(i%2==0){
      digitalWrite(13, HIGH);
      delay(500);
    }
    else{
      digitalWrite(13, LOW);
      delay(500);
    }
  }
  Serial.println("Radial Start");
  rad.Start();
  delay(1000);
  Serial.println("Horizont Start");
  hor.Start();
  delay(1000);
  Serial.println("Stars Start");
  stars.Start();
  delay(1000);
  Serial.println("Main Star Start");
  mainstar.Start();
  delay(1000);
  Serial.println("IceFall Start");
  ice.Start();
  delay(10000);
  for(int i=0; i<10; i++){
    //--------------------------------
    if(GlobalMode){
    Serial.println("Test aborted");
    return;
    }
    //--------------------------------
    if(i%2==0){
      Serial.println("All OFF");
      rad.Stop();
      hor.Stop();
      stars.Stop();
      mainstar.Stop();
      ice.Stop();
      delay(10000);
    }
    else{
      Serial.println("All ON");
      rad.Start();
      hor.Start();
      stars.Start();
      mainstar.Start();
      ice.Start();
      delay(10000);
    }
  } 
  Serial.println("Test completed");
  Serial.println("System READY");
  for(int i=0; i<10; i++){
    if(i%2==0){
      digitalWrite(13, HIGH);
      delay(500);
    }
    else{
      digitalWrite(13, LOW);
      delay(500);
    }
  }
  void standBy();
}
//--------------------------------------------------
void Starting(){
  stars.Step();
  delay(400);
  stars.Step();
  delay(400);
  stars.Step();
  delay(400);
  stars.Step();
  delay(400);
  stars.Step();
  delay(400);
  stars.Step();
  delay(700);
  stars.Step();
  delay(200);
  stars.Step();
  delay(1200);
  stars.Step();
  delay(700);
  stars.Step();
  delay(200);
  stars.Step();  
  delay(1000);
  stars.Start();
  delay(400);
  hor.Step();
  delay(400);
  hor.Step();
  delay(400);
  hor.Step();
  delay(400);
  hor.Step();
  delay(400);
  hor.Step();
  delay(400);
  hor.Step();
  delay(700);
  hor.Step();
  delay(200);
  hor.Step();
  delay(200);
  hor.Step();
  delay(600);
  hor.Step();
  delay(200);
  hor.Step();
  delay(200);
  hor.Step();
  delay(200);
  hor.Step();
  delay(200);
  hor.Reset();
  hor.setMode(true);
  for(int i=0; i<10; i++){
    hor.Step();
    delay(200);
  }
  hor.Start();
  stars.Stop();
  hor.Reset();
  stars.Reset();
  stars.setMode(true);
  hor.setMode(true);
  rad.setNumOfRay(2);
  ice.Start();
  for(int i=0;i<30;i++){
    hor.Dance();
    stars.Step();
    delay(250);
  }
  hor.Reset();
  stars.Stop();
  stars.Reset();
  for(int i=0;i<20;i++){
    rad.Step();
    hor.Step();
    delay(200);
  }
  stars.setMode(true);
  mainstar.Start();
  hor.Start();
  for(int i=0;i<18;i++){
    rad.Blink();
    hor.Step();
    stars.Step();
    delay(200);
  }
  rad.Stop();
  hor.Stop();
  rad.Reset();
  hor.Reset();
  for(int i=0;i<10;i++){
    rad.Step();
    hor.Step();
    mainstar.Blink();
    delay(200);
  }
  hor.Start();
  delay(200);
  stars.Start();
  delay(200);
  mainstar.Start();
  delay(3000);
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
  
  GlobalMode = 3;
}
//-----------PATTERNS-----------------
void PatternOne(){
  mainstar.Start();
  ice.Start();
  stars.Start();
  for(int i=0;i<100;i++){
    rad.Step();
    hor.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternTwo(){
  hor.setMode(true);
  hor.setDirection(false);
  mainstar.Start();
  ice.Start();
  for(int i=0;i<100;i++){
    mainstar.Blink();
    hor.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternThree(){
  hor.setDirection(false);
  for(int i=0;i<100;i++){
    mainstar.Blink();
    hor.Step();
    stars.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternFour(){
  stars.Start();
  mainstar.Start();
  ice.Start();
  hor.setMode(true);
  for(int i=0;i<100;i++){
    hor.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternFive(){
  mainstar.Start();
  rad.setNumOfRay(3);
  for(int i=0;i<100;i++){
    stars.Step();
    rad.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternSix(){
  ice.Start();
  hor.Start();
  rad.setNumOfRay(3);
  for(int i=0;i<100;i++){
    mainstar.Blink();
    rad.Step();        
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternSeven(){
  mainstar.Start();
  stars.setMode(true);
  hor.setMode(true);
  for(int i=0;i<100;i++){
    stars.Step();
    hor.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}
void PatternEight(){
  mainstar.Start();
  ice.Start();
  stars.Start();
  hor.setMode(true);
  hor.setDirection(false);
  for(int i=0;i<100;i++){
    hor.Step();
    delay(300);
    //--------------------------------
    if(GlobalMode!=3){
    Serial.println("Loop aborted");
    return;
    }
    //--------------------------------
  }  
  hor.Stop();
  stars.Stop();
  rad.Stop();
  mainstar.Stop();
  ice.Stop();
  hor.Reset();
  stars.Reset();
  rad.Reset();
}



void standBy(){
  GlobalMode = 1;//StandBy mode
}
void greeting(){
  GlobalMode = 2;//Starting mode
}
void PatternStack(){
  GlobalMode = 3;//Loop mode
}
void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  attachInterrupt(4, greeting, FALLING);
  attachInterrupt(3, standBy, FALLING);
  attachInterrupt(2, PatternStack, FALLING);
  FullTest();
}
void loop(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  if(GlobalMode==2){
    Starting();
  }  
  if(GlobalMode==3){
    PatternOne();
  }  
  if(GlobalMode==3){
    PatternTwo();
  }
  if(GlobalMode==3){
    PatternThree();
  }
  if(GlobalMode==3){
    PatternFour();
  }
  if(GlobalMode==3){
    PatternFive();
  }
  if(GlobalMode==3){
    PatternSix();
  }
  if(GlobalMode==3){
    PatternSeven();
  }
  if(GlobalMode==3){
    PatternEight();
  }
}