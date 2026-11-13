
#include "pid_controller.h"
// Import our class definition from the header file.

#include <stdexcept>
// Provides standard exception types, allowing us
// to report invalid inputs.

// Constructor: Assign the gains passed by the caller.
//
// The colon introduces a member initializer list.
// This initializes each member directly.
PIDController::PIDController(double kp,
                             double ki,
                             double kd)
    : kp_(kp), ki_(ki), kd_(kd) {}


// Implement the update() function declared in the header.
//
// PIDController:: specifies that this function
// belongs to the PIDController class.
double PIDController::update(double setpoint,
                             double measurement,
                             double dt) {

    // Validate the time step.
    // Division by zero or a negative time step would
    // make the derivative calculation invalid.
    if (dt <= 0.0) {
        throw std::invalid_argument("dt must be positive");
    }

    // STEP 1: Calculate the control error.
    //
    // error = desired value - measured value
    //
    // Positive error means we're below our target.
    double error = setpoint - measurement;


    // STEP 2: Update the integral term.
    //
    // Approximate the accumulated error using
    // a rectangular numerical integration step.
    //
    // Integral ≈ sum(error * dt)
    integral_ += error * dt;


    // STEP 3: Calculate the derivative term.
    //
    // The derivative estimates how quickly the error
    // is changing.
    double derivative = 0.0;

    // On the first update, there is no previous error
    // available for calculating a difference.
    if (!first_update_) {

        // Backward finite-difference approximation:
        //
        // derivative ≈ (current error - previous error) / dt
        derivative =
            (error - previous_error_) / dt;
    }

    // Future iterations can now calculate the derivative.
    first_update_ = false;

    // Save this iteration's error for the next update.
    previous_error_ = error;


    // STEP 4: Calculate the complete PID command.
    //
    // P = kp * current error
    // I = ki * accumulated error
    // D = kd * rate of change of error
    //
    // u = P + I + D
    double proportional = kp_ * error;
    double integral = ki_ * integral_;
    double derivative_term = kd_ * derivative;

    return proportional + integral + derivative_term;
}


// Reset the internal controller state.
void PIDController::reset() {

    // Forget any previously accumulated error.
    integral_ = 0.0;

    // Clear the error history.
    previous_error_ = 0.0;

    // Treat the next update as the first update.
    first_update_ = true;
}
