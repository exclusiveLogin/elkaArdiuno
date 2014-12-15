/*
name:LightDinamic Trees
developer:Sergey Savin
Kolibri Media Holding
*/
void setup(){
  Serial.begin(9600);
}
void loop(){

}
//--------Radial------
class Radial{
  public:
    Radial(int pins[24]);
    void setNumOfRay(int num_of_rays);
    void setDirection(boolean dir);
    void Step();
    void Blink();
    void Stop();
  private:
    void lightMaping();
    boolean direct;
    int pinID[24];
    int numRaysVal;
    int stepVal;//max 24
    boolean lightMap[24];
};

Radial::Radial(int pins[24]){
  stepVal=1;//max 24
  for(int i=0;i<24;i++){
    pinID[i]=pins[i];
    pinMode(pinID[i], OUTPUT);
  }
  numRaysVal = 1;
  stepVal=1;
  direct=true;
}

void Radial::setDirection(boolean dir){
  direct=dir;
}

void Radial::setNumOfRay(int num_of_rays){
  numRaysVal = num_of_rays;
  lightMaping();
}
void Radial::lightMaping(){
  int counter = numRaysVal;
  boolean state = true;
  for(int i=24;i>0;i--){
    lightMap[i]=state;
    counter--;
    if(counter==0){
      counter = numRaysVal;
      state=!state;
    }
  }
}
void Radial::Step(){
  boolean realLight[24];
  if(direct==true&&stepVal>24)stepVal=1;
  if(direct==false&&stepVal<1)stepVal=24;
  for(int i=0;i<24;i++){//перенос матрицы
    if((stepVal+i)>24){
      realLight[(stepVal+i)-24] = lightMap[i];
    }
    else{
      realLight[stepVal+i] = lightMap[i];
    }    
  }  
  for(int i=0;i<24;i++){//Активация апаратной части
    digitalWrite(pinID[i], realLight[i]);
  }
  if(direct==true) stepVal++;
  else stepVal--;
}
void Radial::Blink(){  
  for(int i=0;i<24;i++){
    lightMap[i]=!lightMap[i];
  }
  for(int i=0;i<24;i++){//Активация апаратной части
    digitalWrite(pinID[i], lightMap[i]);
  }
}
void Radial::Stop(){
  for(int i=0;i<24;i++){//Активация апаратной части
    digitalWrite(pinID[i], LOW);
  }
}
//------------HORIZONT------------------------
class Horizont{
  public:
    Horizont(int pins[15],int pinsR[5],int pinsG[5],int pinsB[5]);
    void setColor(int color);
    void setMode(boolean mode);
    void Step();
    void Blink();
    void Dance();
    void Stop();
  private:
    int PColor;
    boolean PFill;
    boolean PDirection;
    int PPinID[24];
    int PPinRed[8];
    int PPinGreen[8];
    int PPinBlue[8];
    int stepVal;//max 8
    boolean lightMap[8];
};
Horizont::Horizont(int pins[24],int pinsR[8],int pinsG[8],int pinsB[8]){
  for(int i=0;i<24;i++){
    PPinID[i]=pins[i];
  }
  for(int i=0;i<8;i++){
    PPinRed[i]=pinsR[i];
  }
  for(int i=0;i<8;i++){
    PPinGreen[i]=pinsG[i];
  }
  for(int i=0;i<8;i++){
    PPinBlue[i]=pinsB[i];
  }
  PColor=1;
  PFill=false;
  PDirection=true;
  stepVal=1;
}
void Horizont::setColor(int color){
  PColor=color;//1,2,3
}
void Horizont::setMode(boolean mode){
  PFill=mode;//false=single true=solid fill
}
void Horizont::Step(){
  if(PDirection==true&&stepVal>8)stepVal=1;
  if(PDirection==false&&stepVal<1)stepVal=8;
  
  if(!PFill){//Без заполнения
    for(int i=0;i<8;i++){
      lightMap[i]=false;
    }    
    for(int i=0; i<8; i++){
      if(stepVal==i){
        lightMap[i]=true;
      }
      else;
    }
  }
  else{//С заполнением
    for(int i=0; i<8; i++){
      if(stepVal==i){
        lightMap[i]=!lightMap[i];
      }
      else;
    }
  }
  
  //Render
  Stop();
  
  switch(PColor){
    case 1:  
      for(int i=0;i<8;i++){//красные
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        }
      }
      break;
    case 2:    
      for(int i=0;i<8;i++){//зеленые
      if(lightMap[i]){
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 3:  
      for(int i=0;i<8;i++){//синие
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        }
      }  
      break;
    case 4:  
      for(int i=0;i<8;i++){//красные + зеленые
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 5: 
      for(int i=0;i<8;i++){//красные + синии
      if(lightMap[i]){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
        }
      }
      break;
    case 6:  
      for(int i=0;i<8;i++){//синии + зеленые
      if(lightMap[i]){
        digitalWrite(PPinBlue[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
        }
      }
      break;
    case 7:  
      for(int i=0;i<8;i++){//красные + зеленые + синии
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
      for(int i=0;i<8;i++){ 
        digitalWrite(PPinRed[i], HIGH);
      }
      break;
    case 2://All Green
      for(int i=0;i<8;i++){
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 3://All Blue
      for(int i=0;i<8;i++){ 
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 4://Red+Green
      for(int i=0;i<8;i++){ 
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinGreen[i], HIGH);
      }
      break;
    case 5://Green+Blue
      for(int i=0;i<8;i++){ 
        digitalWrite(PPinGreen[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 6://Red+Blue
      for(int i=0;i<8;i++){
        digitalWrite(PPinRed[i], HIGH);
        digitalWrite(PPinBlue[i], HIGH);
      }
      break;
    case 7://All
      for(int i=0;i<24;i++){
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
  for(int i=0;i<24;i++){//обнуляем все
    digitalWrite(PPinID[i], LOW);
  }
}
//--------------------------------------------------
