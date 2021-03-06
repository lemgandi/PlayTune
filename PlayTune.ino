/*
 * Play a Tune
 * Copyright(c) Charles Shapiro Nov 2017
 This file is part of PlayTune.

    PlayTune is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PlayTune is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PlayTune.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "PlayTune.h"
#include "tunes.h"

#include <MusicBox.h>

#include <LiquidCrystal.h>
#define PLAYPIN 15

LiquidCrystal Lcd(8,9,4,5,6,7);

MusicBox MusicPlayer;


/*
 * Read a button from the VMA203
 */
Button readButton()
{
   Button theButton=NullButton;
   int keyValue=analogRead(0);

   while(keyValue < 900)  // Do not read value on a button already pressed.
      keyValue=analogRead(0);
      
   while(theButton == NullButton) {
      keyValue=analogRead(0);
 
      if(keyValue < 64)
         theButton=Right;
      else if (keyValue < 128)
         theButton=Up;
      else if (keyValue < 300)
         theButton=Down;
      else if (keyValue < 500)
         theButton=Left;
      else if (keyValue < 900)
         theButton = Select;
   }
   
   return theButton;
}

/*
 * Wait for a button
 */
void waitForButton()
{
   int pressed=-1;
   int keyValue = analogRead(0);
   while(-1 == pressed)
   {
      keyValue=analogRead(0);
      if(keyValue < 900)
         pressed=0;
   }
}


/*
 * Main Line Setup
 */
void setup()
{
   Serial.begin(9600);
   Serial.println("Begin");
   Lcd.begin(1,2);
   MusicPlayer.begin(PLAYPIN);
   MusicPlayer.loadATune(StartSong,STARTSONG);
   MusicPlayer.loadATune(FailSong,FAILSONG);
   MusicPlayer.loadATune(SuccessSong,SUCCESSSONG);
   Lcd.write("Initialized");
}

void writeSong(char *songName)
{
  Lcd.clear();
  Lcd.write("Playing");
  Lcd.setCursor(0,1);
  Lcd.write(songName);
}

/*
 * Main Line Loop
 */
void loop()
{
  Button theButton = readButton();
  switch(theButton) {
     case Select:
        writeSong("Success");
        MusicPlayer.playATune(SUCCESSSONG);
	break;
     case Down:
        writeSong("Fail");
        MusicPlayer.playATune(FAILSONG);
        break;
     case Left:
        writeSong("Start");
        MusicPlayer.playATune(STARTSONG);
	break;
     case Right:
        writeSong("Oops 2");
	MusicPlayer.playATune(25);
	break;
     default:  // Right
        writeSong("Oops");
        MusicPlayer.playATune(10);
	break;
  }
  Lcd.clear();
  Lcd.write("Waiting");
  theButton=NullButton;
}

