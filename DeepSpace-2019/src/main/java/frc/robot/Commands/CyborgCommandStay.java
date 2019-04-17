/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.Commands;

import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;
import frc.robot.Util.Util;

public class CyborgCommandStay extends Command {
  public CyborgCommandStay() {
    requires(Robot.SUB_DRIVE);
  }

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
    Robot.SUB_DRIVE.resetEncoders();
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    Robot.SUB_DRIVE.setPIDF(Util.getAndSetDouble("Stay kP", 0), 0, 0, 0);
    Robot.SUB_DRIVE.driveByPositions(0, 0, Util.getAndSetDouble("Stay Max Value", 1));
  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    return false;
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
  }
}
