#include "DayOfYear.h"
#include <F1kM_Hisab.h>

void setup() {
  Serial.begin(9600);
  uint16_t tanggal, bulan, tahun;
  char S_Tanggal_H[50];

  int jumlah_hari_setahun;

  tahun = 2020; // Ganti jika ingin tahun yang lain (> 2018)

  if (is_leap(tahun))  {
    jumlah_hari_setahun = 366;
  }
  else                {
    jumlah_hari_setahun = 365;
  }

  //=============================
  // Construct Object
  //=============================
  F1kM_Hisab HisabTanggal;

  //=============================
  // Set Locations
  //=============================
  HisabTanggal.setLocationOnEarth(-6.175513, 106.827170); //Latitude Longitude JAKARTA ==> -6.175513, 106.827170

  //Set Imkan Rukyah ... Visibility Factor
  // Muhammadiah      ==> 0 derajat
  // Nahdatul Ulama   ==> 2 derajat
  HisabTanggal.setHilalVisibilityFactor(0);
  
  Serial.print("\n\n\nCalender Hijriah tahun "); Serial.println(tahun);
  Serial.println("Cara Muhammadiah (Imkan Rukyah = 0 derajat)");
  Serial.println("===========================================================");
  Serial.println("Tgl Masehi\tTinggi Hilal\tTgl Hijriah");
  Serial.println("===========================================================");
  for (int i = 1; i <= jumlah_hari_setahun; i++)
  {
    date_of_year(i, tanggal, bulan, tahun);
    Serial.print(tanggal); Serial.print("-");
    Serial.print(bulan); Serial.print("-");
    Serial.print(tahun); Serial.print("\t");

    Serial.print(HisabTanggal.MoonAltOnSunSet(tanggal, bulan, tahun)); Serial.print("\t\t");

    HisabTanggal.Greg2HijrDate_String(tanggal, bulan, tahun, S_Tanggal_H, 1);
    Serial.println(S_Tanggal_H);
  }
  Serial.println("===========================================================");



  //Set Imkan Rukyah ... Visibility Factor
  // Muhammadiah      ==> 0 derajat
  // Nahdatul Ulama   ==> 2 derajat
  HisabTanggal.setHilalVisibilityFactor(2);
  
  Serial.print("\n\n\nCalender Hijriah tahun "); Serial.println(tahun);
  Serial.println("Cara Nahdatul Ulama (Imkan Rukyah = 2 derajat)");
  Serial.println("===========================================================");
  Serial.println("Tgl Masehi\tTinggi Hilal\tTgl Hijriah");
  Serial.println("===========================================================");
  for (int i = 1; i <= jumlah_hari_setahun; i++)
  {
    date_of_year(i, tanggal, bulan, tahun);
    Serial.print(tanggal); Serial.print("-");
    Serial.print(bulan); Serial.print("-");
    Serial.print(tahun); Serial.print("\t");

    Serial.print(HisabTanggal.MoonAltOnSunSet(tanggal, bulan, tahun)); Serial.print("\t\t");

    HisabTanggal.Greg2HijrDate_String(tanggal, bulan, tahun, S_Tanggal_H, 1);
    Serial.println(S_Tanggal_H);
  }
  Serial.println("===========================================================");




}





void loop() {
  // put your main code here, to run repeatedly:
}
