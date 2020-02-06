/*
 * F1kM_Hisab is extend class of Ephemeris class from https://github.com/MarScaper/ephemeris
 * Calculater Hijr Date using Ephemeris Hisab Methode
 *
 * by Fk1M (For 1000 Masjid) https://www.facebook.com/groups/761058907424496/
 */

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef F1kM_Hisab_h
#define F1kM_Hisab_h
#include <Arduino.h>
#include <Ephemeris.h>

/*#include <pgmspace.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>*/

class F1kM_Hisab : public Ephemeris,public Calendar{
  public :
	SolarSystemObject  sun, moon;   
	F1kM_Hisab(float _latitude, float _longitude);
    F1kM_Hisab();


    void               setHilalVisibilityFactor(float _HilalVisibilityFactor);   																// Set Imkan Rukyah (degree)
    float               MoonAltOnSunSet(unsigned int day, unsigned int month, unsigned int year);   							// calculate Irtifa’ Hilāl
    void               Greg2HijrDate( int GDate,  int GMonth,  int GYear,  int& HDate,  int& HMonth,  int& HYear);   	// Calcualte Hijr Date 
    void               Greg2HijrDate_String( int GDate,  int GMonth,  int GYear, char* HDateSting, int type); 				// Print formated Hijr, Type 0->short, 1->long, 2->number
    void               SholahTime(unsigned int day, unsigned int month, unsigned int year);										// Calculate Sholah Time (under Construction)

  protected :
    // Hijr Month Name Long & Short
    char               MonthNameLong  [13][20]  = {"Muharram", "Safar", "Rabiul-Awwal", "Rabi-uthani", "Jumadi-ul-Awwal", "Jumadi-uthani", "Rajab", "Sha’ban", "Ramadhan", "Shawwal", "Zhul-Q’ada", "Zhul-Hijja"};
    char               MonthNameShort [13][8]    = {"Muhar", "Safar", "RabAw", "RabTh", "JumAw", "JumTh", "Rajab", "Sha’b", "Ramad", "Shaww", "ZhuQa", "ZhuHi"};

	// Default Imkan Rukyah (0 degree)
    float               HilalVisibilityFactor = 0.0f; 				
};
#endif  
