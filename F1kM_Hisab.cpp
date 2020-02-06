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

#include 	<F1kM_Hisab.h>
#define 	DEBUG 0

//===========================
//   Constructor
//===========================
F1kM_Hisab::F1kM_Hisab(float _latitude, float _longitude)
{
  setLocationOnEarth(_latitude, _longitude);
}

F1kM_Hisab::F1kM_Hisab()
{ }

//===========================
//Public Methode
//===========================
void  F1kM_Hisab::setHilalVisibilityFactor(float _HilalVisibilityFactor)
{
  HilalVisibilityFactor = (float)_HilalVisibilityFactor;
}

float F1kM_Hisab::MoonAltOnSunSet(unsigned int day, unsigned int month, unsigned int year) //Irtifa’ Hilāl
{
  int hours, minutes; FLOAT seconds;
  
  sun   = solarSystemObjectAtDateAndTime(Sun, day, month, year, 0, 0, 0);
  if ( sun.riseAndSetState == RiseAndSetOk )
  {
    floatingHoursToHoursMinutesSeconds(sun.set, &hours, &minutes, &seconds);
	seconds = round(seconds);
    moon = solarSystemObjectAtDateAndTime(EarthsMoon, day, month, year, hours, minutes, (unsigned int) seconds);
    return moon.horiCoordinates.alt;
  }
  else if ( sun.riseAndSetState == LocationOnEarthUnitialized )  {
    Serial.println("You must set your location on Earth first.");
  }
  else if ( sun.riseAndSetState == ObjectAlwaysInSky )           {
    Serial.println("Sun always in sky for your location.");
  }
  else if ( sun.riseAndSetState == ObjectNeverInSky )            {
    Serial.println("Sun never in sky for your location.");
  }
}

void F1kM_Hisab::Greg2HijrDate(int GDate,  int GMonth,  int GYear,  int& HDate,  int& HMonth,  int& HYear)
{
  const int     MidZulhijjah1438 			= 2458002; // Julian Date Mid Zulhijjah 1438H
  const float   lunarM 							= 29.5305902777778f;
  JulianDay     DateJD 						= julianDayForDateAndTime(GDate, GMonth, GYear, 0, 0, 0);
  JulianDay     HijrJD;

  float         delta_jd   						= float(DateJD.day - MidZulhijjah1438) / lunarM;
  int           LastMid     						= int(delta_jd);
  float         dayFromMid 					= delta_jd - float(LastMid);

  if(DEBUG)  {Serial.print(dayFromMid,3); Serial.print("\t");}

  if ( dayFromMid < 0.566 )
  { LastMid = LastMid - 1;
    dayFromMid = dayFromMid + 0.6f;
  }
  else
  {
    dayFromMid = dayFromMid - 0.4f;
  }

  HMonth = LastMid % 12;
  HYear = int(LastMid / 12) + 1439;
  HDate = 28;

  HijrJD.day  = DateJD.day - int(dayFromMid * lunarM);
  HijrJD.time = 0.5f;

  float         cday;
  int  cmonth, cyear;
  float         MoonAlt_YD, MoonAlt_TD;

  dateForJulianDay(HijrJD, &cday, &cmonth, &cyear);
  MoonAlt_YD  = MoonAltOnSunSet(int(cday), cmonth, cyear);
  HijrJD.day  = HijrJD.day + 1;
   
  int hitung =0;
  
  while (HijrJD.day < DateJD.day)
  {
	if(DEBUG)  hitung++;  
	
    dateForJulianDay(HijrJD, &cday, &cmonth, &cyear);
    MoonAlt_TD = MoonAltOnSunSet(int(cday), cmonth, cyear);

    if (MoonAlt_TD >= HilalVisibilityFactor and MoonAlt_YD < HilalVisibilityFactor)
    {
	HMonth = HMonth + 1;
	HDate = 1;

	if (HMonth > 12) {
		HMonth = 1;
		HYear =  HYear + 1;
	}
      	  
      if ((DateJD.day - HijrJD.day)< 30) {
		HDate = DateJD.day - HijrJD.day;
		break;}
      else  {
	 	HDate =27;
		HijrJD.day  = HijrJD.day + 27;
		}
    }
    else 
    {
	HDate = HDate + 1;
	HijrJD.day  = HijrJD.day + 1;
    }
    
	
    MoonAlt_YD = MoonAlt_TD;
	delay(0);
  }
  
   if(DEBUG) {Serial.print(hitung); Serial.print("\t");}
}

void F1kM_Hisab::Greg2HijrDate_String(int GDate,  int GMonth,  int GYear, char* HDateSting, int type)
{
  int HDate;
  int HMonth;
   int HYear;
  Greg2HijrDate(GDate, GMonth, GYear, HDate, HMonth, HYear );

  switch (type) {
    case 0:  sprintf(HDateSting, "%d %s %d H\0", HDate, MonthNameShort[HMonth - 1], HYear); 	break;
    case 1:  sprintf(HDateSting, "%d %s %d H\0", HDate, MonthNameLong[HMonth - 1], HYear);  	break;
    case 2:  sprintf(HDateSting, "%02d-%02d-%d H\0", HDate, HMonth, HYear);                 				break;
    default: sprintf(HDateSting, "%d %s %d H\0", HDate, MonthNameLong[HMonth - 1], HYear);  	break;
  }
}

void F1kM_Hisab::SholahTime(unsigned int day, unsigned int month, unsigned int year)
{
  sun   = solarSystemObjectAtDateAndTime(Sun, day, month, year, 0, 0, 0);
 /* if ( sun.riseAndSetState == RiseAndSetOk )
  {
    Serial.print("Shuruq / Rise :"); Serial.println(sun.rise, 5);
    Serial.print("Mhagrib / Set :"); Serial.println(sun.set, 5);
    Serial.print("Zhuhur        :"); Serial.println(sun.rise + (sun.set - sun.rise) / 2, 5);
    Serial.print("Ashar         :"); Serial.println(sun.rise + (sun.set - sun.rise) / 4 * 3, 5);
  }
  else
  {
    Serial.println("Sholah Time Can Not Calculate for this Coordinate");
  }*/
}

