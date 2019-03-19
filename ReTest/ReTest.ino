
//Password Cracking Using Dictionary Attack

#include <ArduinoSTL.h>
#include <md5.h>
#include <SPI.h>
#include <SD.h>

//Initializes the hash algorithm
MD5 md5;

using namespace std;

//User Inputs password here to check if it can be cracked
string StolenHash = "68adbbc27c1574eff960f348b4f5f515";

//Used to initialize the dictionary in the SD card
File myFile;

//String and Character variables used
string buffer = "";
char Inputchar;
string input;

bool isThere = false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(53,OUTPUT);
  cout<<("cracking started.....")<< endl;
  cout<<("Hashed Password to be cracked: ")<< StolenHash<<endl;

  //Checks if Sd card is initialized successfully
   if(!SD.begin(53)){
    cout<<("Init failed");
    while(1);
    }
    myFile = SD.open("password.txt");
    if(!myFile){
      cout<<("File cant be opened");
      }
     while(myFile.available()){
      input = readLine();
      if(md5(input) == StolenHash){ //Converts input to md5 and compares with the stolen hash
        cout<<("Password Found")<<endl;
        cout<<"The password is: "<< input <<endl;
        cout<<("Done Cracking")<<endl;
        isThere = true;
        while(true){}
        
        }
      }
      if(!isThere){
        cout<<"Password not cracked or not in dictionary";
        }
      myFile.close();

}

//Method for reading the dictionary line by line
string readLine(){
   string buffer = ""; //Buffer that stores the characters of a line
   char Inputchar; // stores each character read
   while(myFile.available()){
      Inputchar = myFile.read(); //Reads the character of a particular line
      if(Inputchar == '\n' || Inputchar == '\r'){ //
        return string(buffer);
        }
       else{
        buffer+=Inputchar;
        } 
  
  }
  return "";
}

void loop() {
  // put your main code here, to run repeatedly:

}
