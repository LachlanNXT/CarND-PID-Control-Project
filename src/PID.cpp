#include "PID.h"
#include <iostream>
#include <math.h> 

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  p_error = 0;
  i_error = 0;
  d_error = 0;
  old_cte = 0;
  total_error = 0;
  N=0;
  index = -1;
  best_error = 999;
  dp[0] = 0.01; dp[1] = 0.00001; dp[2] = 1;
  p[0] = Kp; p[1] = Ki; p[2] = Kd;
  tries[0] = 0; tries[1] = 0; tries[2] = 0;
  test = false;
}

void PID::UpdateError(double cte) {
  p_error = cte;
  i_error = i_error+cte;
  d_error = cte - old_cte;
  old_cte = cte;
  //std::cout << cte << " " << p_error << " " << i_error << " " << d_error << std::endl;
}

double PID::Calculate() {
  return Kp*p_error + Ki*i_error + Kd*d_error;
  N++;
}

void PID::Twiddle() {
  if (N%1000==0 && N>99)
  {
    if (test == false)
    {

      test = true;
      best_error = total_error;
      total_error = 0;
      N=0;
      index = (index+1)%3;
      p[index] += dp[index];
      Kp = p[0]; Ki = p[1]; Kd = p[2];
      
    }
    else
    {
      if (total_error<best_error)
      {
        best_error = total_error;
        dp[index] = dp[index]*1.1;
        cout << "increase" << endl;
      }
      else
      {
        cout << " no good " << endl;
        p[index] -= dp[index];
        dp[index] = -dp[index];
        tries[index] += 1;
      }
      for (int i=0;i<3;i++)
      {
        if (tries[i]>1)
        {
          cout << " tries " << endl;
          dp[i] = dp[i]*0.9;
          tries[i] = 0;
        }
      }

      if ((fabs(dp[0])+fabs(dp[1])+fabs(dp[2])) < 0.01)
      {
        cout << "dp " << dp[0] << " " << dp[1] << " " << dp[2] << endl;
        cout << Kp << " " << Ki << " " << Kd << endl;
        cin.get();
      }

      total_error = 0;
      N=0;
      index = (index+1)%3;
      p[index] += dp[index];
      Kp = p[0]; Ki = p[1]; Kd = p[2];
      cout << "p " << p[0] << " " << p[1] << " " << p[2] << endl;
      cout << "dp " << dp[0] << " " << dp[1] << " " << dp[2] << endl;

    }
  }
    

}

double PID::TotalError() {
  N++;
  total_error += (old_cte*old_cte)/(N);
  return total_error;
}

