// WFLC filter
// An implementation of an adaptive filter called 
// Weighted-frequency Fourier Linear Combiner
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 15
//--------------------------------------------------------
//Constants
//#define PI 3.141592654   // π (predefined)
#define N 2            // number of harmonics
#define MU0 0.000001   // μ0: adaptive gain for fundamental frequency
#define MU1 0.01       // μ1: adaptive gain for reference input vector
//--------------------------------------------------------
//External variables
float v0=(2*PI);//ω0: fundamental angular frequency
float v[N];//array of angular frequencies
float x[2][N];//reference input vector, 1st row for sin and 2nd row for cos
float w[2][N];//weight vector, 1st row for sin and 2nd row for cos
//--------------------------------------------------------
//initialize WFLC filter
//Initialize weights
void InitWFLC()
{
  int i;
  for (i=0;i<N; i++) {w[0][i]=0; w[1][i]=0;} //init weights
}
//--------------------------------------------------------
//WFLC filter
//input (k: time instant, s: reference signal)
//output (y: estimated signal)
float WFLC(float k,float s)
{
  int i; float err,y,z;
  //-----------------------------------------------------------------
  //Get angular velocities depending on adjusted fundamental angular frequency
  for (i=0;i<N; i++) v[i]=(i+1)*v0;//assign v0 and its harmonics
  //-----------------------------------------------------------------
  //find reference input vector
  for(i=0;i<N; i++){ 
    x[0][i]=sin(v[i]*k);
    x[1][i]=cos(v[i]*k);
  }
  //-----------------------------------------------------------------
  //find estimated signal, y
  for(i=0,y=0;i<N;i++){y+=w[0][i]*x[0][i]+ w[1][i]*x[1][i];}
  //-----------------------------------------------------------------
  //adapt the weights 
  err=s-y;
  for(i=0,z=0;i<N;i++){z+=(i+1)*(w[0][i]*x[1][i]- w[1][i]*x[0][i]);}
  v0=v0+2*MU0*err*z;
  for(i=0;i<N;i++){
    w[0][i]+=2*MU1*x[0][i]*err;
    w[1][i]+=2*MU1*x[1][i]*err;
  }
  return y;
}
//--------------------------------------------------------
