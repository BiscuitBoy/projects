// class defines a type that bundles data and functionality. 
// public exposes the interface, while private hides internal implementation details. 
// This is called encapsulation.

#pragma once
// Prevents this header from being included multiple times
// in the same compilation unit.


// Define a reusable Proportional-Integral-Derivative
// (PID) controller.
class PIDController {

public:
    // PUBLIC: Other parts of the program can access these.

    // Constructor: Creates a PID controller with three gains.
    //
    // kp: Proportional gain
    // ki: Integral gain
    // kd: Derivative gain
    PIDController(double kp, double ki, double kd);

    // Calculates the next controller output.
    //
    // setpoint: Desired value (e.g., target position)
    // measurement: Current measured value
    // dt: Time elapsed since the previous update (seconds)
    //
    // Returns the calculated control command.
    double update(double setpoint,
                  double measurement,
                  double dt);

    // Clears accumulated controller state.
    // Useful when restarting a simulation or control loop.
    void reset();

private:
    // PRIVATE: These variables can only be accessed
    // by the PIDController's own member functions.

    // Controller tuning gains.
    double kp_;
    double ki_;
    double kd_;

    // Accumulates error over time for integral control.
    double integral_ = 0.0;

    // Stores the last error for derivative control.
    double previous_error_ = 0.0;

    // Tracks whether update() has been called before.
    // Prevents a derivative calculation on the first step.
    bool first_update_ = true;
};
