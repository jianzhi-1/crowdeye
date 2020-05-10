#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

short arr[2][24][2700][4400];
bool weekend;
short hhour;
short a, b;
vector<int> v;

short dx[] = {1, 1, 1, -1, -1, -1, 0, 0};
short dy[] = {-1, 0, 1, -1, 0, 1, 1, -1};

int average(){
	int total = 0;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		total += *it;
	}
	total = v[0] + (int)ceil(total/(int)v.size());
	return total;
}

int main(){
	srand (time(NULL));
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("processed_run")) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	  	string dir = "processed_run/";
	  	char * dirr = new char[30];
	  	strcpy(dirr, dir.c_str());
	  	std::ifstream infile(strcat(dirr, ent->d_name));
	  	if (strlen(ent->d_name) < 3) continue;
	  	
	  	/*
	  	string line;
	  	getline(infile, line);
	  	cout << line << endl;
	  	*/
	  	/*
	  	ofstream myfile;
	  	dir = "processed_run/p_";
	  	dirr = new char[10];
	  	strcpy(dirr, dir.c_str());
	  	myfile.open(strcat(dirr, ent->d_name));
	  	string aa = "";
		aa = aa + line[8];
		aa = aa + line[9];
	  	string bb = "";
		bb = bb + line[5];
		bb = bb + line[6];
	  	string cc = "";
		cc = cc + line[0];
		cc = cc + line[1];
		cc = cc + line[2];
		cc = cc + line[3];
		string dd = "";
		dd = dd + line[11];
		dd = dd + line[12];
	  	myfile << weekend(stoii(aa), stoii(bb), stoii(cc)) << "\n";
	  	myfile << stoii(dd) << "\n";
	  	*/
	  	bool weekend;
	  	infile >> weekend;
	  	int hhour;
	  	infile >> hhour;
	  	int a, b;
	  	//cout << "hhour" << endl;
	  	//cout << "hi" << endl;
	  	while (infile >> a >> b){
	  		//cout << a << " " << b << endl;
	  		arr[weekend][hhour][a][b]++;
	  		//cout << arr[weekend][hhour][a][b] << endl;
	  	}
	  	//myfile.close();
	    printf ("%s\n", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  perror ("");
	  return EXIT_FAILURE;
	}
	
	//interpolation
	for (int i = 0; i <= 1; i++){
		for (int j = 0; j <= 23; j++){
			cout << i << " " << j << endl;;
			for (int k = 0; k < 2700; k++){
				for (int l = 0; l < 4400; l++){
					v.clear();
					v.push_back(arr[i][j][k][l]);
					for (int m = 0; m < 8; m++){
						if (k + dx[m] < 0 || k + dx[m] >= 2700) continue;
						if (l + dy[m] < 0 || l + dy[m] >= 4400) continue;
						v.push_back(arr[i][j][k + dx[m]][l + dy[m]]);
					}
					arr[i][j][k][l] = rand()%3 + average();
				}
			}
		}
	}
	cout << "hi" << endl;
	
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 24; j++){
			cout << i << " " << j << endl;
			//cout << "wer1" << endl;
			ofstream myfile;
		  	string dir = "matrix/mat_";
		  	char * dirr = new char[30];
		  	strcpy(dirr, dir.c_str());
		  	//cout << "wer2" << endl;
		  	dirr[11] = (char)(i + 48);
		  	dirr[12] = (char)((j - j%10)/10 + 48);
		  	dirr[13] = (char)(j%10 + 48);
		  	dirr[14] = '.';
		  	dirr[15] = 't';
		  	dirr[16] = 'x';
		  	dirr[17] = 't';
		  	//cout << "wer3" << endl;
		  	
		  	myfile.open(dirr);	
		  	myfile << "2700 4400\n";
		  	//cout << "wer" << endl;
		  	for (int k = 0; k < 2700; k++){
		  		for (int l = 0; l < 4400; l++){
		  			myfile << arr[i][j][k][l] << " ";
		  		}
		  		myfile << "\n";
		  	}
			//myfile << weekend(stoii(aa), stoii(bb), stoii(cc)) << "\n";
			  
			myfile.close();		
		}
	}

	
}
