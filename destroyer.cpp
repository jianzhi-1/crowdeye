#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
int a, b;
int c;
int main(){
	freopen("matrix/mat_007.txt", "r", stdin);
	freopen("command.txt", "w", stdout);
	cin >> a >> b;
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			cin >> c;
			if (c != 0){
				cout << "tempArray[" << i << "][" << j << "] = " << c << ";\n";
			}
		}
	}
}
