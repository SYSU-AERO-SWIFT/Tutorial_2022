/*
 * PID Controller Implementation in C
 * 
 * Created by Joshua Saxby (aka @saxbophone) on 1 Jan, 2016
 * 
 * My own attempt at implementing the PID algorithm in some (hopefully) clean, understandable C.
 *
 * See LICENSE for licensing details.
 */

#include "pid.h"


pid_state PidElement(PID_Parm parm, pid_state state) {
    // calculate difference between desired and actual values (the error)
    double error = state.target - state.actual;
    // calculate and update integral
    state.integral += (error * state.time_delta);
    // calculate derivative
    double derivative = (error - state.previous_error) / state.time_delta;
    // calculate output value according to algorithm
    state.output = ( (parm.kp * error) + (parm.ki * state.integral) + (parm.kd * derivative) );
    // update state.previous_error to the error value calculated on this iteration
    state.previous_error = error;
    // return the state struct reflecting the calculations
    return state;
}

pid_compensate PidVector(pid_state x,pid_state y){
      pid_compensate a;
      a.x=x.output,a.y=y.output,a;
      return a;
}
