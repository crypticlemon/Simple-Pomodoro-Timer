#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

void timerDisplay();
void pomoTimer(int pomoAmnt);

int minutes, seconds;
int inputTime;

int main() {
  //Static variables for printing statistics
  static int workCount, breakCount, workCalculator, breakCalculator;
  char breakOrWork, failbit;
  //breakOrWork checks if you're on break or working
  //failbit is for input validation later on

  //Main Title
  cout << "Pomodoro Timer!" << endl;
  cout << 
    "========================================================"
    << endl;
  
  //Statistics
  cout << "Amount of work timers: "<< workCount << right <<
    setw(30) << "Amount of break timers: " << breakCount << " Min." << endl;
  cout << "Total minutes worked: "<< workCalculator << right <<
    setw(28) << "Total break minutes: " << breakCalculator << " Min." << endl;
  
  cout << 
    "========================================================"
    << endl;
  cout << endl;

  //Loop - asks whether you want to work or take a break
  do {
    cout << "Would you like to work or take a break?\nType 'w' for work, or 'b' for break: " << endl;
    cin >> breakOrWork;
    breakOrWork = tolower(breakOrWork);

    if (breakOrWork != 'w' && breakOrWork != 'b') {
      if (isdigit(breakOrWork))
        cout << "You need to type a letter here." << endl;
      cout << "Please type the correct value\n" << endl;
    }
  } while ((breakOrWork != 'w' && breakOrWork != 'b') || isdigit(breakOrWork));
  
  //Loop - asks how many minutes should the timer be
  do {
    cout << "Enter one of the following, or type a custom timer:\n- 15 Minutes\n- 25 Minutes\n- 55 Minutes" << endl;
    cin >> inputTime;

    if (cin.fail() || inputTime <= 0) {
      if (cin.fail()) {
        cin.clear();
        cin >> failbit;
        cout << "Invalid value." << endl;
      }
      cout << "Please enter an integer bigger than 0." << endl;
    }
  } while (cin.fail() || inputTime <= 0);
  
  //Adds to statistics variables depending on input
  if (breakOrWork == 'w') {
    workCount++;
    workCalculator += inputTime;
  } else if (breakOrWork == 'b') {
    breakCount++;
    breakCalculator += inputTime;
  }
  
  pomoTimer(inputTime);
  
  return 0;
}

//Function that shows the timer
void timerDisplay () {
  //Variables for setw()
  int widthOfTitle, widthOfUnderscore, widthOfLine1, widthOfLine2;
  widthOfTitle = 27;
  widthOfUnderscore = 37;
  widthOfLine1 = 20;
  widthOfLine2 = 5;

  system("clear");
  
  // Title
  cout << right << setw(widthOfTitle) << "TIMER - " <<
    inputTime << " MINUTE";
  if (inputTime != 1) cout << "S";
  cout << endl;
  cout << 
    "========================================================"
    << endl;
  cout << endl;

  //Timer
  cout << right << setw(widthOfUnderscore) << "_________________\n" << endl;
  cout << setw(widthOfLine1) << "|";
  cout << setw(widthOfLine2);
  //Show double digits if number is 0 - 9
  if (minutes < 10) cout << "0";
  cout << minutes << " : ";
  if (seconds < 10) cout << "0";
  cout << seconds;
  cout << setw(widthOfLine2) <<  "|" << endl;
  cout << setw(widthOfUnderscore) << "_________________\n" << endl;
}

//Function that deals with timer countdown
void pomoTimer(int pomoAmnt) {
  minutes = pomoAmnt;
  seconds = 0;

  //Loop until timer is done
  while (minutes >= 0 && seconds >= 0) {
    timerDisplay();
    //Since system("clear") is in timerDisplay(), it will clear the
    //console every second as not to make a mess
    sleep(1);

    seconds--;

    //What happens when seconds reach 0
    if (seconds < 0) {
      minutes--;
      seconds = 59;
    }
  }
  //Clears the console again before returning back to main()
  system("clear");
  main();
}
