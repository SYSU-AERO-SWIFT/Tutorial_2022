/*
 * PID Controller Implementation in C
 * 
 * Created by Joshua Saxby (aka @saxbophone) on 1 Jan, 2016
 * 
 * My own attempt at implementing the PID algorithm in some (hopefully) clean, understandable C.
 *
 * See LICENSE for licensing details.
 */

// protection against multiple includes
#ifndef SAXBOPHONE_PID_H
#define SAXBOPHONE_PID_H



    typedef struct pid_parm {
        /*
         * struct PID_Calibration
         * 
         * Struct storing calibrated PID constants for a PID Controller
         * These are used for tuning the algorithm and the values they take are
         * dependent upon the application - (in other words, YMMV...)
         */
        double kp; // Proportional gain
        double ki; // Integral gain
        double kd; // Derivative gain
    } PID_Parm;


    typedef struct pid_state {
        /*
         * struct PID_State
         * 
         * Struct storing the current state of a PID Controller.
         * This is used as the input value to the PID algorithm function, which also
         * returns a PID_State struct reflecting the adjustments suggested by the algorithm.
         * 
         * NOTE: The output field in this struct is set by the PID algorithm function, and
         * is ignored in the actual calculations.
         */
        double actual; // The actual reading as measured
        double target; // The desired reading
        double time_delta; // Time since last sample/calculation - should be set when updating state
        // The previously calculated error between actual and target (zero initially)
        double previous_error;
        double integral; // Sum of integral error over time
        double output; // the modified output value calculated by the algorithm, to compensate for error
    } PID_State;


 struct pid_compensate{
        double x;
	double y;
};

    pid_compensate PidVector(pid_state x,pid_state y);  

    pid_state PidElement(PID_Parm calibration, PID_State state);

#endif
