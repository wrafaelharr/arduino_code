// example data
int data[64]={14, 30, 35, 34, 34, 40, 46, 45,  30, 4,  -26,  -48,  -55,  -49,  -37,
  -28,  -24,  -22,  -13,  6,  32, 55, 65,  57, 38, 17, 1,  -6, -11,  -19,  -34, 
  -51,  -61,  -56,  -35,  -7, 18, 32, 35,  34, 35, 41, 46, 43, 26, -2, -31,  -50,
  -55,  -47,  -35,  -27,  -24,  -21,  -10,  11, 37, 58, 64, 55, 34, 13, -1, -7};

// fft data
byte  sine_data [91]= { 0,  
  4,    9,    13,   18,   22,   27,   31,   35,   40,   44, 
  49,   53,   57,   62,   66,   70,   75,   79,   83,   87, 
  91,   96,   100,  104,  108,  112,  116,  120,  124,  127,  
  131,  135,  139,  143,  146,  150,  153,  157,  160,  164,  
  167,  171,  174,  177,  180,  183,  186,  189,  192,  195,       //Paste this at top of program
  198,  201,  204,  206,  209,  211,  214,  216,  219,  221,  
  223,  225,  227,  229,  231,  233,  235,  236,  238,  240,  
  241,  243,  244,  245,  246,  247,  248,  249,  250,  251,  
  252,  253,  253,  254,  254,  254,  255,  255,  255,  255 };
float f_peaks[5];  // top 5 frequencies peaks in descending order

// pins
int sensorPin = A0; 

// values
int sensorValue = 0;
int prevSenseVal = 0;
int deltaSense = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
}
        
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  deltaSense = sensorValue - prevSenseVal;
  prevSenseVal = sensorValue;

  // add new and remove old value
  for (int i=0; i<63; i++) {data[i] = data[i+1];}
  data[63] = deltaSense;

  // preform fft
  FFT(data,64,100); 

  // print
  Serial.println(deltaSense);
  //Serial.println(f_peaks[1]);

  // delay
  delay(1);
}

// FFT function
float  FFT(int in[],int N,float Frequency) {
  unsigned  int data[13]={1,2,4,8,16,32,64,128,256,512,1024,2048};
  int a,c1,f,o,x;
  a=N;  

  //calculating  the levels                          
  for(int i=0;i<12;i++) {if(data[i]<=a) {o=i;}}
      
  int in_ps[data[o]]={};     //input for sequencing
  float out_r[data[o]]={};   //real part of transform
  float  out_im[data[o]]={};  //imaginory part of transform
           
  x=0;  

  // bit reversal
  for(int b=0;b<o;b++) {
    c1=data[b];
    f=data[o]/(c1+c1);

    for(int  j=0;j<c1;j++) { 
      x=x+1;
      in_ps[x]=in_ps[j]+f;
    }
  }

  // update input array as per bit reverse order
  for(int i=0;i<data[o];i++) {
    if(in_ps[i]<a) {out_r[i]=in[in_ps[i]];}
    if(in_ps[i]>a) {out_r[i]=in[in_ps[i]-a];}      
  }


  int i10,i11,n1;
  float e,c,s,tr,ti;

  for(int  i=0;i<o;i++) {
    i10=data[i];              // overall values of sine/cosine  :
    i11=data[o]/data[i+1];    // loop with similar sine cosine:
    e=360/data[i+1];
    e=0-e;
    n1=0;

    for(int j=0;j<i10;j++) {
      c=cosine(e*j);
      s=sine(e*j);    
      n1=j;
          
      for(int  k=0;k<i11;k++) {
        tr=c*out_r[i10+n1]-s*out_im[i10+n1];
        ti=s*out_r[i10+n1]+c*out_im[i10+n1];
          
        out_r[n1+i10]=out_r[n1]-tr;
        out_r[n1]=out_r[n1]+tr;
          
        out_im[n1+i10]=out_im[n1]-ti;
        out_im[n1]=out_im[n1]+ti;          
          
        n1=n1+i10+i10;
      }       
    }
  }

  //---> here onward out_r contains  amplitude and our_in conntains frequency (Hz)
  
  // getting amplitude from compex number
  for(int i=0;i<data[o-1];i++) {
    out_r[i]=sqrt(out_r[i]*out_r[i]+out_im[i]*out_im[i]);  // to  increase the speed delete sqrt
    out_im[i]=i*Frequency/N; 
  }

  // peak detection
  x=0;       
  for(int i=1;i<data[o-1]-1;i++) { 
    if(out_r[i]>out_r[i-1] &&  out_r[i]>out_r[i+1]) {
      //in_ps array used for storage of  peak number
      in_ps[x]=i;    

      x=x+1;
    }    
  }

  s=0;
  c=0;

  // re arraange as per magnitude
  for(int  i=0;i<x;i++) {            
    for(int  j=c;j<x;j++) {
      if(out_r[in_ps[i]]<out_r[in_ps[j]]) {
        s=in_ps[i];
        in_ps[i]=in_ps[j];
        in_ps[j]=s;
      }
    }

    c=c+1;
  }


  //  updating f_peak array (global variable)with descending order
  for(int i=0;i<5;i++) {f_peaks[i]=out_im[in_ps[i]];}
}

// trig functions
float sine(int i) {
  int j=i;
  float  out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out=  sine_data[j];}
  else if(j>90  && j<181){out= sine_data[180-j];}
  else if(j>180  && j<271){out= -sine_data[j-180];}
  else if(j>270 && j<361){out= -sine_data[360-j];}
  return (out/255);
}
float cosine(int i){
  int j=i;
  float  out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out=  sine_data[90-j];}
  else if(j>90  && j<181){out= -sine_data[j-90];}
  else  if(j>180 && j<271){out= -sine_data[270-j];}
  else if(j>270 && j<361){out= sine_data[j-270];}
  return (out/255);
}