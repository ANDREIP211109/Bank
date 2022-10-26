#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <unordered_map>
#include <thread>
#include <chrono>

#define Color_Red "\33[0:31m\\]" // Color Start
#define Color_end "\33[0m\\]" // To flush out prev settings
#define LOG_RED(X) printf("%s %s %s",Color_Red,X,Color_end)


using namespace std;

struct Bank{
private:
  vector<string> v;
  unordered_map<string, int> money;

  void add_pos(string element){
    v.push_back(element);
    money[element] = 100;
  }

  void del_pos(string element){
    int i;

    i=0;
    while(i<(int)v.size()&&v[i]!=element){
      i++;
    }

    if (i<(int)v.size()) {
      swap(v[i], v.back());
      v.pop_back();
    }
  }

  string get(string type){

    if(type=="name"){
      return v.back();
    }else if(type=="money"){
      return to_string(money[v.back()]);
    }

    return "error";
  }

public:
  string username;

  void registerAccount(){
    printf("Please enter Username: ");
    cin >> username;

    add_pos(username);
  }

  void remAccount(){
    printf("Please enter Username: ");
    cin >> username;

    del_pos(username);
  }

  void infoAccount(){
    if(v.size()>0){
      cout << "\nName: ";
      cout << get("name");
      cout << "\nBalance: ";
      cout << ((get("money")=="error")?"Error: No money var found!":get("money"));
      cout << "\n";
    }else{
      system("color 4");
      cout << "Error: no account created.";
      while(!(GetKeyState(VK_SPACE) & 0x8000));
      system("cls");
      system("color 7");
    }
  }

  void deposite(){
    int amount;

    printf("Pleas Enter amount: ");
    cin >> amount;
    money[v.back()]+=amount;
  }

  void withdraw(){
    int amount;

    printf("Pleas Enter amount: ");
    cin >> amount;
    if(money[v.back()]<amount){
      system("cls");
      system("color 4");
      cout << "Error: not enough money.";
      while(!(GetKeyState(VK_SPACE) & 0x8000));
      system("cls");
      system("color 7");
    }
    money[v.back()]-=amount;
  }

  void printAccount() {
    for(auto i : v){
      cout << (i+=" ");
    }
    cout << "\n";
  }
};

int main() {
  int command;
  Bank bank;

  do {

    printf("Insert command: ");
    scanf("%d", &command);

    if (command == 1){
      bank.registerAccount();
    }else if (command == 2){
      bank.remAccount();
    }else if(command == 3){
      bank.infoAccount();
      printf("\nPress \"Space\" to continue.");
      while(!(GetKeyState(VK_SPACE) & 0x8000));
    }else if(command == 4){
      bank.deposite();
    }else if(command == 5){
      bank.withdraw();
    }

    system("cls");

    //bank.printAccount();
  } while (command != 6);


  return 0;
}
