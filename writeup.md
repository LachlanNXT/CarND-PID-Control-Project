# CarND-Controls-PID Writeup
Self-Driving Car Engineer Nanodegree Program

---

Things to note:
* Had to run the simulator under host windows, and code under linux VM, since simulator was unusably slow in VM.
* Used this to link VM to host: https://discussions.udacity.com/t/running-simulator-on-windows-and-code-on-ubuntu/255869

## P I D components
P - proportional. This parameter affects speed of convergence, overshoot and stability. Generally, quicker convergence = more overshoot, and trying to converge too quick is unstable.
I - inetegral. Accounts for systematic/contstant offset errors, of which there are none in a perfect simulation, so I = 0.
D - derivative. Counteracts the negative affects of P, i.e. overshoot and instability. When the error is changing rapidly this has more of an effect than if it is changing slowly.

## Hyperparameter tuning
There are several things to take into account when tuning:

* What is the output domain? [-1,1]
* What do the error values usually look like? Generally, |e| < 1 when car is in ok state.
* What do the d(error)/dt values usually look like? Generally, |e| < 0.01 when car is in ok state.
* Is the integral parameter useful here? Not in simulation without any systematic errors.

I started by manually tuning the P parameter. I wanted to map values [-1,1] -> [-1,1], where positive error means you should steer negatively and positive error means you should steer negatively. So a P of -1/1 = -1 should be close. I started with -1 and experimented with values until I was more or less happy with a value of -0.2.

The D parameter needed to map [-0.01,0.01] -> [-1,1] with negative correlation, so -1/0.01 = -100 is the starting point. But, the P parameter should be doing most of the work, and the contribution of D should be an order of magnitude less than P, so I started with -100/10 = -10. This turned out to be a good guess.

I also implemented an on-line twiddling function to try and optimise the parameters further. It takes the total error of a large sample of driving after changing a parameter to see if there was improvement, and keeps the change if it was good. This confirmed that the I parameter should be zero, and helped fine tune P and D to the final P = -0.21 and D = -9. The time required to run the optimizer is non-trivial, so I stopped when the performance was ok, used those parameters, and left the twiddling on for submission.

Here are examples of running the simulator with this code:

[//]: # (Image References)
[image1]: ./Capture.png

![alt text][image2]
