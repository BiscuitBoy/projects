#include <iostream>
// Provides std::cout for printing to the terminal.

#include <iomanip>
// Allows formatting numerical output,
// such as displaying two decimal places.

#include "pid_controller.h"
// Imports our reusable PIDController class.


int main() {

    // =========================================
    // 1. CONFIGURE THE PID CONTROLLER
    // =========================================

    // Create a PID controller object.
    //
    // kp = 2.0: Proportional gain
    // ki = 0.1: Integral gain
    // kd = 0.5: Derivative gain
    PIDController pid(2.0, 0.1, 0.5);


    // =========================================
    // 2. DEFINE SIMULATION PARAMETERS
    // =========================================

    // Time step: Advance the simulation by 0.01 seconds
    // per iteration (100 simulation steps per second).
    const double dt = 0.01;

    // Desired final position of the moving object.
    const double target = 10.0;

    // Damping coefficient: Represents resistance
    // proportional to velocity.
    //
    // This example assumes unit mass, so acceleration
    // is numerically equal to control - damping*velocity.
    const double damping = 1.0;


    // =========================================
    // 3. INITIALIZE THE SYSTEM STATE
    // =========================================

    // The object starts at position zero.
    double position = 0.0;

    // The object starts at rest.
    double velocity = 0.0;


    // Print column headers.
    std::cout << "Time\tPosition\tVelocity\n";


    // =========================================
    // 4. RUN THE SIMULATION LOOP
    // =========================================

    // Execute 1001 discrete simulation updates.
    //
    // dt = 0.01 seconds
    // 1000 * 0.01 = 10 seconds
    //
    // Note: This loop performs an update even at
    // the displayed time of 0 seconds.
    for (int step = 0; step <= 1000; ++step) {

        // Compute the current simulation timestamp.
        double time = step * dt;


        // -----------------------------------------
        // A. CALCULATE CONTROLLER OUTPUT
        // -----------------------------------------

        // The PID compares the target against
        // the current simulated position.
        //
        // Its output is interpreted as a force.
        double control =
            pid.update(target, position, dt);


        // -----------------------------------------
        // B. CALCULATE SYSTEM DYNAMICS
        // -----------------------------------------

        // Newton's second law:
        //
        // F = m*a
        //
        // With mass = 1:
        //
        // acceleration = control - damping*velocity
        //
        // The damping term opposes motion.
        double acceleration =
            control - damping * velocity;


        // -----------------------------------------
        // C. UPDATE SYSTEM STATE
        // -----------------------------------------

        // Numerically integrate acceleration
        // to obtain a new velocity.
        //
        // v_next = v_current + acceleration*dt
        velocity += acceleration * dt;

        // Numerically integrate velocity
        // to obtain the new position.
        //
        // x_next = x_current + velocity_next*dt
        //
        // This is a semi-implicit Euler update,
        // because position uses the updated velocity.
        position += velocity * dt;


        // -----------------------------------------
        // D. PRINT SIMULATION DATA
        // -----------------------------------------

        // Only print every 100th iteration.
        //
        // 100 steps * 0.01 seconds = 1 second.
        //
        // This keeps terminal output manageable.
        if (step % 100 == 0) {

            // fixed: Display standard decimal notation.
            //
            // setprecision(2): Show two digits
            // after the decimal point.
            std::cout
                << std::fixed
                << std::setprecision(2)
                << time << "\t"
                << position << "\t\t"
                << velocity << "\n";
        }
    }


    // Return zero to indicate successful execution.
    return 0;
}
