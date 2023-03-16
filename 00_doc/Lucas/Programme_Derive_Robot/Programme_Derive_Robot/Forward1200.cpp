/*
Adept MobileRobots Robotics Interface for Applications (ARIA)
Copyright (C) 2004-2005 ActivMedia Robotics LLC
Copyright (C) 2006-2010 MobileRobots Inc.
Copyright (C) 2011-2015 Adept Technology, Inc.
Copyright (C) 2016-2018 Omron Adept Technologies, Inc.

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

If you wish to redistribute ARIA under different terms, contact 
Adept MobileRobots for information about a commercial version of ARIA at 
robots@mobilerobots.com or 
Adept MobileRobots, 10 Columbia Drive, Amherst, NH 03031; +1-603-881-7960
*/
#include <iostream>
#include "Aria.h"
using namespace std;


/** @example wander.cpp 
 * Example using actions and range devices to implement a random wander avoiding obstacles.
 *
 *  This program will just have the robot wander around. It uses some avoidance 
 *  actions if obstacles are detected with the sonar or laser (if robot has a
 *  laser), otherwise it just has a constant forward velocity.
 * 
 *  Press Control-C or Escape keys to exit.
 *  
 * This program will work either with the MobileSim simulator or on a real
 * robot's onboard computer.  (Or use -remoteHost to connect to a wireless
 * ethernet-serial bridge.)
*/

int main(int argc, char **argv)
{
  Aria::init();
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  ArRobot robot;
  ArRobotConnector robotConnector(&argParser, &robot);
  ArLaserConnector laserConnector(&argParser, &robot, &robotConnector);
  int Vmax=600;
  int Rx,Fx,P,Vr;
  if(!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Could not connect to the robot.");
    if(argParser.checkHelpAndWarnUnparsed())
    {
        // -help not given, just exit.
        Aria::logOptions();
        Aria::exit(1);
        return 1;
    }
  }


  // Trigger argument parsing
  if (!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
    return 1;
  }

  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);
  robot.attachKeyHandler(&keyHandler);

  puts("This program will make the robot wander around. It uses some avoidance\n"
  "actions if obstacles are detected, otherwise it just has a\n"
  "constant forward velocity.\n\nPress CTRL-C or Escape to exit.");
  
  ArSonarDevice sonar;
  robot.addRangeDevice(&sonar);

  robot.runAsync(true);

  
  // try to connect to laser. if fail, warn but continue, using sonar only
  if(!laserConnector.connectLasers())
  {
    ArLog::log(ArLog::Normal, "Warning: unable to connect to requested lasers, will wander using robot sonar only.");
  }


  // turn on the motors, turn off amigobot sounds
  robot.enableMotors();
  robot.comInt(ArCommands::SOUNDTOG, 0);


  /*for (int i=0; i<40; ++i){
  ArLog::log(ArLog::Normal, "phase 1");
  Rx=robot.getX();
  Fx=Rx+985;
  while(Rx<=Fx){
  P=Rx*100/Fx;
  Vr=Vmax*(100-P)/100+200;
  robot.lock();
  robot.setVel(Vr);
  robot.unlock();
  ArUtil::sleep(100);
  cout<<"dist: "<<robot.getX()<<endl<<"Vit: "<<Vr<<endl;
  Rx=robot.getX();
  }*/

    
  
  ArLog::log(ArLog::Normal, "phase 1");
  robot.lock();
  robot.setVel(1200);//800 | 400
  robot.unlock();
  ArUtil::sleep(1400);//15m: 20400 |38000
  cout<<robot.getX()<<endl;
    
  ArLog::log(ArLog::Normal, "phase 2");
  robot.lock();
  robot.stop();
  robot.unlock();
  ArUtil::sleep(3000);
  cout<<robot.getX()<<endl;
  
 

  
  // wait for robot task loop to end before exiting the program
  robot.waitForRunExit();
  
  Aria::exit(0);
  return 0;
}
