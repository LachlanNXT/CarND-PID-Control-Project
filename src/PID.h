#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double old_cte;
  double total_error;
  double best_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  int N;
  double p[3];
  double dp[3];
  int tries[3];
  int index;
  bool test;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Calculate the total PID error.
  */
  double Calculate();

  void Twiddle();

};

#endif /* PID_H */
