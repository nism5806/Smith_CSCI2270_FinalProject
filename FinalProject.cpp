#include <iostream>
#include <string>
#include "Graph.h"
#include <stdlib.h>
using namespace std;
int main(){
    string input="0";
    cout<<"WELCOME TO THE GAME"<<endl;
    cout<<"Your goal is to reach the target city"<<endl;
    while(16<atoi(input.c_str())||9>atoi(input.c_str())){
        cout<<"Please enter a difficulty between 9-16:"<<endl;
        getline(cin,input);
    }
    Graph game=Graph(atoi(input.c_str()));
    game.findDistricts();
    game.turn();

    //game.displayEdges();


    return 0;
}
