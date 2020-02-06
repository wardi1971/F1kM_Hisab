#include <F1kM_Hisab.h>

void setup() {
  int Gre_Date  = 1;
  int Gre_Month = 1;
  int Gre_Year  = 2020;

  char S_Tanggal_H[35];
  int Hjr_Date, Hjr_Month, Hjr_Year;
  
  Serial.begin(9600);
  
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

  Serial.print("\n\nConvert Gregorian Date : ");
  Serial.print(Gre_Date);Serial.print("/");Serial.print(Gre_Month);Serial.print("/");Serial.println(Gre_Year);
  Serial.println();
  
  HisabTanggal.Greg2HijrDate(Gre_Date,Gre_Month,Gre_Year,Hjr_Date,Hjr_Month,Hjr_Year);
  Serial.println("Calculated Hijr Date (number) : ");
  Serial.print("Date  :");Serial.println(Hjr_Date);
  Serial.print("Month :");Serial.println(Hjr_Month);
  Serial.print("Year  :");Serial.println(Hjr_Year);
  Serial.println();

  HisabTanggal.Greg2HijrDate_String(Gre_Date,Gre_Month,Gre_Year,S_Tanggal_H,0);
  Serial.print("Calculated Hijr Date String Short Format : \t");
  Serial.println(S_Tanggal_H); 
  Serial.println();

  HisabTanggal.Greg2HijrDate_String(Gre_Date,Gre_Month,Gre_Year,S_Tanggal_H,1);
  Serial.print("Calculated Hijr Date String Long Format : \t");
  Serial.println(S_Tanggal_H); 
  Serial.println();

  HisabTanggal.Greg2HijrDate_String(Gre_Date,Gre_Month,Gre_Year,S_Tanggal_H,2);
  Serial.print("Calculated Hijr Date String Number Format : \t");
  Serial.println(S_Tanggal_H); 
  Serial.println();

  Serial.print("Hilal Altitude on Sun Set (tinggi hilal saat matahari terbenam) : ");
  Serial.println(HisabTanggal.MoonAltOnSunSet(Gre_Date,Gre_Month,Gre_Year));
}

void loop() {
  // put your main code here, to run repeatedly:

}
