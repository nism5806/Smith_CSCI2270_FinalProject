#include <iostream>
#include <string>
#include "Graph.h"
#include <stdlib.h>
using namespace std;
int main(){
    for(int i=0;i<100;i++){
    //    Graph g=Graph(16);
    }
    string input="0";
    cout<<"WELCOME TO THE GAME"<<endl;
    cout<<"Your goal is to reach the target city"<<endl;
    while(26<atoi(input.c_str())||9>atoi(input.c_str())){
        cout<<"Please enter a difficulty between 9-26:"<<endl;
        getline(cin,input);
    }
    Graph game=Graph(atoi(input.c_str()));
    game.findDistricts();
    game.play();


    return 0;
}
