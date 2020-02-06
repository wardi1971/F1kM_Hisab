static const unsigned int days_to_month[2][13] =
      {
         // non-leap year
         { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,365 },
         // leap year
         { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,366 },
      };

bool is_leap(int const year) noexcept
   {
      return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
   }
 
unsigned int day_of_year(int const year, unsigned int const month, unsigned int const day)
   {
 
      if (month == 0 || month > 12) Serial.println("invalid month");
      if (day == 0 || day > 31) Serial.println("invalid day");
 
      return days_to_month[is_leap(year)][month - 1] + day;
   }

void date_of_year(unsigned int days, uint16_t& _tanggal,uint16_t& _bulan,uint16_t& _tahun)
  {
      if (is_leap(_tahun))
        { 
          if (days > 366)
            {
              Serial.println("days infalid (>366)");
              return; 
            }
        }
      else
        {
          if(days>365) 
            {
              Serial.println("days infalid (>365)");
              return; 
            }
        }

      for(int i=0;i <= 12; i++)
        {
          if (days <= days_to_month[is_leap(_tahun)][i])
            {
              _bulan = i;
              _tanggal = days - days_to_month[is_leap(_tahun)][i-1];
              break;
            }
        }
  }
