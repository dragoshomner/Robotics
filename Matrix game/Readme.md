# MemMove 
**The game that makes you smarter and more fit.**

## Table of content
- [Description](#description)
- [Technical Requirements](#technical-requirements)
- [How to play](#how-to-play)
  - [General descriptions](#general-descriptions)
  - [Setup](#setup)
  - [Display controls](#display-controls)
  - [Settings](#settings)
  - [Start game](#start-game)
  - [Highscore](#highscore)
  - [Info](#info)
- [Links](#links)
- [Meeting requirements](#meeting-requirements)
  - [Game specifications](#game-specifications)
  - [LCD](#lcd)

## Description

<a name="desription" />

With 86 billion neurons, 400 miles of capillaries, 100 thousand miles of axons (enough to circle the earth 4 times), more than 10 trillion synapses, the human brain is estimated to store equivalent to up to 2.5 million gigabytes of storage. That's amazing! Despite this fact,  most adults have an attention span of 20 minutes and short-term memory can hold up to 7 pieces of information at the same time... but only for around 20 seconds. That's sad! The good news are that this statistics can be improved :)

If all 600 muscles in your body pulled in one direction, you could lift 25 tons. Again, that's amazing! Despite this fact, more than 80% of adults do not meet the guidelines for both aerobic and muscle-strengthening activities, and more than 80% of adolescents do not do enough aerobic physical activity to meet the guidelines for youth. Again, that's sad! The good news are that this statistics can be improved :)

MemMove helps you to improve your attention, memory, physical condition and reaction speed. The rules are simple: you will see on the matrix a sequence of instructions which you will have to execute. Sounds easy? Let's start!


## Technical requirements

<a name="technical-requirements" />

- Arduino UNO
- 8x8 LED Matrix
- LCD
- Joystick
- MAX7219 Driver
- 2 Ultrasonic Sensors US-100
- Breadboards
- Wires

## How to play
<a name="how-to-play" /> 

<h3>General descriptions</h3>
<a name="general-descriptions" />
The goal of the game is to test both the physical and memory skills, added up to the ability to coordonate brain and body. It can be played single or up to 9 players. The matrix led will show a sequence of directions, which the player have to keep in mind and reproduce after the blink of the square. Time is your principal enemy! After every good sequence finished, you will receive a bonus time, depending on the number of moves. At the end, a ranking table will be automatically generated with the order of players score and the king will be crowned! Try to push your limits and exceed the highscore! Good luck!  

<h3>Setup</h3>
<a name="setup" />

Unpack the playing zone and position it as a plus shape. Try as much as you can to have perpendicular corners. Pull out the two ultrasonic sensors from the pockets and place it with the small support under the wall. These must be parallel with the back wall (imagine that each of them have lasers and the lines have to hit the opposite wall and be perpendicular in the middle).

<strong>Pay attention!</strong> The sensor with the longer wires is the one which indicates if the player is up or down, and the other one if the player is left or right.

Pull out the wire of the battery from the hole created by the zip, placed in front of the joystick, and plug in the arduino board. Now, the display will light up and the menu will be showed. If it does not happen, check the battery.

<h3>Display controls</h3>
<a name="display-controls" />

Using the joystick, by moving it up and down you change the next link page. If you move it right, you go to the next page, and left, go to previous page. 

During the game, you cannot change the page!

<h3>Settings</h3>
<a name="settings" />

Fistly, is a good plactice to check the settings. You can change the starting level, which means how faster more moves will pe displayed on the matrix, and the difficulty. Difficulty have three options: easy, medium and hard. These change the bonus time which the player receives after a solved sequence of movements.

The default values are one for starting level and medium for diffculty. Use the at first, and after some practice, customize your settings.

<h3>Start game</h3>
<a name="start-game" />

Firstly, choose the number of players, and go to the next page. Now, the sensors are calibrating and the game zone must be clear. After that, the current player go inside the area, and the timer starts to count down. Now, the game starts. Follow the instructions (the timer is off), and after the square blinks (timers is on), is your turn to move. 

If the movement is correct, a tick will be displayed, else a X. <strong>Pay attention!</strong> After every move, you have to go back to center. Both of your legs have to be in the same position.

Your current position will be always displayed on the matrix. Try to understand the game and how the sensors calculate your distance. If you think that you are in a direction and the sensor does not detect you, wait a little or go closer to the willing point, until the game gets your position. Is your responsability to check if the sensors are placed correctly and the game zone is adequate.

When time finishes, all rows will be displayed concurrently. If you selected more than one player, current one have to get out of the game zone, and the next to go inside. The system will detect automatically when he is on the center, and will start the counter down. This will repeat for every player.

When the game finishes, the winner will be showed on the LCD display. Go to the next page to view the  leaderboard with the order of the players, attached with the score. If the leader exceeded the highscore, an intermediate screen will appear.

Go to the next page, and here you have two options. Turn joystick left to restart or turn it right to go to main menu. Have fun!

<h3>Highscore</h3>
<a name="highscore" />

In this screen you can view your highscores. They are divided in three categories, depending on the difficulty of the game in which it was made: easy, medium or hard. Scroll to view everyone.

<h3>Info</h3>
<a name="info" />

In this screen you can view some informations about the game, for instance: game name, creator and git. Do not wait to follow @UnibucRobotics on Facebook! ;) 

## Links
<a name="links" />

Product video: https://www.youtube.com/watch?v=5owO_XoB7Ws&feature=share&fbclid=IwAR0uS0Symy4o3_kpNaL7T0XnYtAGVlsq3yQAFhSUTi0Xscvq3sj1_aPzH_8

## Meeting requiremets
<a name="meeting-requirements" />

<h3>Game specifications</h3>
<a name="game-specifications" />

a. Score - done

b. Progress in difficulty - complexity - done

c. i. 2 players ii. levels iii.time pressure iv. more lives (extra time)

d. Save-able highscore in EEPROM - done (even three highscores, depending on the difficulty)

<h3>LCD</h3>
<a name="lcd" />

a. Starting game - done

b. Highscore - done

c. Settings - change starting level and change difficulty

d. Info - creator name, github, game name, @UnibucRobotics
