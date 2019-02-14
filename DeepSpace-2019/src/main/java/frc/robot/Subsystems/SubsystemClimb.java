/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.Subsystems;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.command.Subsystem;
import frc.robot.Constants;
import frc.robot.Util.Xbox;

/**
 * Screw-based climbing mechanism in the bottom rear
 */
public class SubsystemClimb extends Subsystem {

  private static TalonSRX climber;

  private boolean safetyMode;

  @Override
  public void initDefaultCommand() {
  }

  public SubsystemClimb() {
    safetyMode = true;
    climber = new TalonSRX(Constants.CLIMBER_ID);
    setAmpLimit(60);
  }

  /**
   * Controls the percent output of the climb screw based
   * on the triggers of the given joystick
   * @param joy the joystick to be used
   * @return    the motor amperage
   */
  public double ascendByJoystick(Joystick joy) {
    double percentOutput = Xbox.RT(joy) - Xbox.LT(joy);
    climber.set(ControlMode.PercentOutput, percentOutput);
    DriverStation.reportWarning(percentOutput + "", false);
    return climber.getOutputCurrent();
  }

  /**
   * Sets the maximum allowable amperage of the climb motor
   */
  public void setAmpLimit(int amps) {
    climber.configPeakCurrentLimit(amps);
  }

  /**
   * Sets the state of the 'safety', which only allows
   * control after RB is pressed so the operator doesn't do the dumb
   */
  public void setSafetyMode(boolean active) {
    safetyMode = active;
  }

  /**
   * Retrieves whether or not the safety is on
   * @return true if controls are locked, false if they are unlocked
   */
  public Boolean getSafetyMode() {
    return safetyMode;
  }
}
