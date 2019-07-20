/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 6 - LCD and Serial I/O
 * 
 * Description: Simple arduino program using an LCD, Serial I/O, and the time library.
 *              The program initially interacts with the user via the Serial monitor
 *              to get the custom set time and date. The user must input everything in
 *              the correct format and with only numerical digits
 *              
 *              Month   -> 'MM'   2 digits 
 *              Day     -> 'DD'   2 digits  
 *              Year    -> 'YYY'  4 digits  
 *              Hour    -> 'HH'   2 digits
 *              Minutes -> 'MM'   2 digits
 *              Seconds -> 'SS'   2 digits
 *              
 *              Once the user correctly inputs all the data, the Time library will set the
 *              time to these values and the program then outputs the date and time onto
 *              the LCD with every second updating itself for the most current time.
 *              
 * References: https://playground.arduino.cc/code/time
 * 
 */

#include <LiquidCrystal.h>
#include <TimeLib.h>

// Initialize all the pins connected from the LCD to the arduino
const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Initialize the LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declare all the variables used for retreiving and storing the time
int inputCount, digitValue;
String sMonth, sDay, sYear, sHour, sMin, sSec; // String time values
int nMonth, nDay, nYear, nHour, nMin, nSec; // Integer time values


void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  inputCount = 0;
  Serial.begin(9600);
  Serial.println("Please enter a month in 'MM' format:");
}


// Helper function that returns the Serial input String
// through pass by reference parameter
int inputParser(String& input){ 
    if (Serial.available() > 0) {
      input = Serial.readString();
      return 1;
    }
    return -999;
}

// Helpfer function that prints a given date or time
// with any additional 0 that may be needed
void printTime(int num){
  if(num >= 0 && num < 10)
    lcd.print("0");
  lcd.print(num);
}

void loop() {
  

  // Conditionals to process check which stage the user input is currently in and process it
  if(inputCount == 0){// Month
    
    digitValue = inputParser(sMonth);// Get the month
    if(digitValue == 1){
      lcd.clear();
      nMonth = sMonth.toInt();// Convert to integer
      if(nMonth < 1 || nMonth > 12) // Check if the month is valid
        lcd.print("Invalid month");
      else{
        digitValue = -999;
        inputCount = 1;
        Serial.println("Please enter a day in 'DD' format:");
      }
    }
    
  }else if(inputCount == 1){// Day
    
    digitValue = inputParser(sDay);// Get the day
    if(digitValue == 1){
      lcd.clear();
      nDay = sDay.toInt();// Convert to integer
      if(nDay < 1 || nDay > 31)// Check if the day is valid
        lcd.print("Invalid day");
      else if(nDay == 31){
        if( nMonth==2 || nMonth==4 || nMonth==6 || nMonth==9 || nMonth==11){
          lcd.print("Invalid day");
        }else{
          digitValue = -999;
          inputCount = 2;
          Serial.println("Please enter a year in 'YYYY' format:");
        }
      }else if(nMonth == 2 && nDay > 28)// Special Feb conditon check
        lcd.print("Invalid day");
      else{
        digitValue = -999;
        inputCount = 2;
        Serial.println("Please enter a year in 'YYYY' format:");
      }
    }
    
  }else if(inputCount == 2){// Year
    
    digitValue = inputParser(sYear);// Get the year
    if(digitValue == 1){
      lcd.clear();
      nYear = sYear.toInt();// Convert to integer
      if(nYear < 0)// Check if the year is valid
        lcd.print("That year is too old, try again...");
      else{
        digitValue = -999;
        inputCount ++;
        Serial.println("Please enter an hour in 'HH' format for a 24 hour day:");
      }
    }
    
  }else if(inputCount == 3){// Hour
    
    digitValue = inputParser(sHour);// Get the hour
    if(digitValue == 1){
      lcd.clear();
      nHour = sHour.toInt();// Convert to integer
      if(nHour < 0 || nHour > 23)// Check if the hour is valid
        lcd.print("Invalid hour");
      else{
        digitValue = -999;
        inputCount ++;
        Serial.println("Please enter a minute in 'MM' format:");
      }
    }
    
  }else if(inputCount == 4){// Minutes
    
    digitValue = inputParser(sMin);// Get the minutes
    if(digitValue == 1){
      lcd.clear();
      nMin = sMin.toInt();// Convert to integer
      if(nMin < 0 || nMin > 59)//Check if the minutes are valid
        lcd.print("Invalid minute");
      else{
        digitValue = -999;
        inputCount ++;
        Serial.println("Please enter a second in 'SS' format:");
      }
    }
    
  }else if(inputCount == 5){// Seconds
    
    digitValue = inputParser(sSec);// Get the seconds
    if(digitValue == 1){
      lcd.clear();
      nSec = sSec.toInt();// Convert to integer
      if(nSec < 0 || nSec > 60)// Check if the seconds are valid
        lcd.print("Invalid second");
      else{
        digitValue = -999;
        inputCount ++;
        setTime(nHour, nMin, nSec, nDay, nMonth, nYear); // Set the time
      }
    }
    
  }else if(inputCount == 6){// Output to LCD
    lcd.clear();
    
    printTime(month());
    lcd.print("/");
    printTime(day());
    lcd.print("/");
    printTime(year());

    lcd.setCursor(0,1);

    printTime(hour());
    lcd.print(":");
    printTime(minute());
    lcd.print(":");
    printTime(second());
    lcd.setCursor(0,0);
    delay(1000);
  }
  

}
