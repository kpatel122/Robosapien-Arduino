#ifndef COMMANDS_H
#define COMMANDS_H

#define RSRandom 		  0x01
#define RSTurnRight       0x80
#define RSRightArmUp      0x81
#define RSRightArmOut     0x82
#define RSTiltBodyRight   0x83
#define RSRightArmDown    0x84
#define RSRightArmIn      0x85
#define RSWalkForward     0x86
#define RSWalkBackward    0x87
#define RSTurnLeft        0x88
#define RSLeftArmUp       0x89
#define RSLeftArmOut      0x8A
#define RSTiltBodyLeft    0x8B
#define RSLeftArmDown     0x8C
#define RSLeftArmIn       0x8D
#define RSStop            0x8E
#define RSWakeUp          0xB1
#define RSBurp            0xC2
#define RSNoOp            0xEF


/* random list */
#define RSRightHandStrike1 0xC0  
#define RSRightHandSweep  0xC1 
#define RSBurp 0xC2 
#define RSRightHandStrike2 0xC3
#define RSHigh5  0xC4
#define RSBulldozer 0xC6
#define RSFart 0xC7
#define RSWhistle 0xCA
#define RSTalkback 0xCC
#define RSRoar 0xCE
#define RSAllDemo 0xD0 
#define RSDemo1 0xD2 
#define RSDemo2 0xD3
#define RSDance 0xD4



/* Commands reference- source https://www.markcra.com/robot/ir_codes.php
$80 - turn right (on left side of remote)
$81 - right arm up (upper left button on remote)
$82 - right arm out
$83 - tilt body right
$84 - right arm down
$85 - right arm in
$86 - walk forward
$87 - walk backward
$88 - turn left (on right side of remote)
$89 - left arm up (upper right button on remote)
$8A - left arm out
$8B - tilt body left
$8C - left arm down
$8D - left arm in
$8E - stop

Programming Commands (no shift)
$90 - P (Master Command Program)
$91 - P>> (Program Play, the one on the bottom)
$92 - R>> (Right sensor program)
$93 - L>> (Left sensor program)
$94 - S>> (Sonic sensor program)

GREEN shift commands
$A0 - right turn step
$A1 - right hand thump
$A2 - right hand throw
$A3 - sleep
$A4 - right hand pickup
$A5 - lean backward
$A6 - forward step
$A7 - backward step
$A8 - left turn step
$A9 - left hand thump
$AA - left hand throw
$AB - listen
$AC - left hand pickup
$AD - lean forward
$AE - reset
$B0 - Execute (master command program execute)
$B1 - Wakeup
$B2 - Right (right sensor program execute)
$B3 - Left (left sensor program execute)
$B4 - Sonic (sonic sensor program execute)

ORANGE shift commands
$C0 - right hand strike 3
$C1 - right hand sweep
$C2 - burp
$C3 - right hand strike 2
$C4 - high 5
$C5 - right hand strike 1
$C6 - bulldozer
$C7 - oops (fart)
$C8 - left hand strike 3
$C9 - left hand sweep
$CA - whistle
$CB - left hand strike 2
$CC - talkback
$CD - left hand strike 1
$CE - roar
$D0 - All Demo
$D1 - Power Off (drop snow-globe and say "Rosebud")
$D2 - Demo 1 (Karate skits)
$D3 - Demo 2 (Rude skits)
$D4 - Dance
NOTES:
add $08 to go from right-side commands to left-side commands.
add $20 to command bytes for the GREEN shift (ie. $Ax and $Bx range)
add $40 to command bytes for the ORANGE shift (ie. $Cx and $Dx range)
SECRET UNDOCUMENTED CODES
Several different launch codes (Executing the main program)

$B0 - standard "EXECUTE" on remote

Robot says "uh-huh" before starting Main program
No subroutines called [Execute sensor commands (Green Shift) cause error sounds to be played instead of what they should do -- bug or feature you decide]
$97 - appears to be same as $B0
$98 - Quiet execute main program

Robot does not say "uh-huh"
No subroutines called
$9A - Quiet execute main program with subroutines !!

Robot does not say "uh-huh"
Subroutines are called (as documented in the manual). This is the one to use.
Execute feature appears to be same as $91 (regular remote Program Play). $91 button also does other things like end the current recording. $9A code doesn't.
Useful? secret codes

$F6 - feet shuffle
$FB - nothing (useful as NO-OP)
$FC - raise arm throw
$D6 - karate chop

not useful [or at least no significant difference detected]
$95,$96 - Program main again (like $90)
$99 - like $98
$9B - like $90 ?
$9C - do nothing
$9D,9E,9F - like $90 ?
$B5 - like $97 ?
$B6 - like $90 ?

others - looks like these repeat as well (eg: record/execute one of the program areas) or do nothing
$E0 - $EE (looks like the $A0 range)
$EF - nothing
$F0 - like $97
$F1 - like $98
$F2 - Execute right program
$F3 - Execute left program
$F4 - Execute sonic program
$F5 - like $F0/97 ?
$F7 - like $F0/97 ?
$F8,F9,FA - like $F1/98 ?
$FD,FE,FF - program main again (like $90)
*/

#endif