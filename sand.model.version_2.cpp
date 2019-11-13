#include "bits/stdc++.h"
#include <iostream>
#include <ctime>
#include "cmath"
using namespace std;
//key_parametres
int a[60][60];
int n=50; //square n*n;
int amount_sand = 2000000;//2000000;
long double h[2000010];
//functions
void zero(){
    for (int i = 0; i<=n+1;i++){  //поля = 0!
        a[i][0] = 0;
        a[i][n+1] = 0;
        a[0][i] = 0;
        a[n+1][i] = 0;}
    return;
}

bool on_edge(int i,int j){
    if (i==0 or j==0 or i==n+1 or j==n+1){
        return true;
    }
    else{
        return false;
    }
} //on_edge - стоковая вершина
bool end_relaxation(){
    bool flag = true;  //true - relaxation is over; false - relaxation isn't over
    for (int i=1;i<=n; i++){
        if (flag == true){
            for (int j=1;j<=n;j++){
                if (a[i][j]>=4){
                    flag = false;
                }
            }
        }
        else{
            return flag;
        }
    }
    return flag;
}
int start_relaxation(int i, int j, int q){
    int result = 0;
    if (end_relaxation()==true){
        result = 0;
        return 0;
    }
    else {
            if (a[i][j]>=4){ //blowup if can do it
                result+=1;
                a[i][j]-=4;
                a[i+1][j]+=1;
                a[i-1][j]+=1;
                a[i][j+1]+=1;
                a[i][j-1]+=1;
                zero();
            }
            while (end_relaxation()==false) {
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        if (a[x][y]>=4) {
                            result+=1;
                            a[x][y]-=4;
                            if (on_edge(x+1, y)==false){
                                a[x+1][y]+=1;
                            }
                            if (on_edge(x-1, y)==false){
                                a[x-1][y]+=1;
                            }
                            if (on_edge(x, y+1)==false){
                                a[x][y+1]+=1;
                            }
                            if (on_edge(x, y-1)==false){
                                a[x][y-1]+=1;
                            }
                        }
                    }
                }
            }
        }
    return result;
}
int main(){
    for (int i = 1; i<=n ;i++){
        for (int j = 1; j<=n ;j++){
            a[i][j] = 3;
        }
    } // initaliasation of a[i][j]=3;
    zero();
    for (int i = 0; i<=amount_sand;i++){
        h[i]=0;
    }  // h[i]=0;
    // бросаем песчинки
    for (int q=1;q<=amount_sand;q++){ //q-ая песчинка
        srand(time(0)-q/3211*sqrt(time(0))+486217*q);
        int i = rand()%n+1; //[1;n]
        int j = rand()%n+1; //[1;n]
        a[i][j]+=1;
        if (end_relaxation()==false){
            long double p = start_relaxation(i,j,q);
            h[q]=log(p);
        }
        else {
            h[q]=0;
        }
        if (q%50000 ==0){
            cout<<q<<" "<<h[q]<<endl;
        }
    }
    //fout
    fstream fout;
    fout.open("data.csv", ios::out | ios::app);
    for (int q=1;q<=amount_sand;q++){
        if (h[q]>0){
            fout<<q<<","<<h[q]<<"\n";
        }
    }
    return 0;
}
