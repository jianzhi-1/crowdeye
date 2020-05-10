#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <math.h>
#include <sstream>
#include <string>
using namespace std;

long double westmost = 103.632346;
long double eastmost = 104.034491;
long double northmost = 1.471281;
long double southmost = 1.237650;
//lat times scale gives reading in metres.
long double scale = 11100.0/0.1;

int stoii(string x){
	int multi = 1;
	int answer = 0;
	for (int i = x.length() - 1; i >= 0; i--){
		answer += ((int)x[i] - 48)*multi;
		multi*=10;
	}
	return answer;
}

bool weekend(int d, int m, int y) {  
    static int t[] = { 0, 3, 2, 5, 0, 3, 
                       5, 1, 4, 6, 2, 4 };  
    y -= m < 3; 
	if ((( y + y / 4 - y / 100 +  y / 400 + t[m - 1] + d) % 7 >= 1) && (( y + y / 4 - y / 100 +  y / 400 + t[m - 1] + d) % 7 <= 5)) return 0;
	return 1;
    //return ( y + y / 4 - y / 100 +  y / 400 + t[m - 1] + d) % 7;  
}  

int main(){
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("runs")) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	  	string dir = "runs/";
	  	char * dirr = new char[10];
	  	strcpy(dirr, dir.c_str());
	  	std::ifstream infile(strcat(dirr, ent->d_name));
	  	if (strlen(ent->d_name) < 3) continue;
	  	string line;
	  	getline(infile, line);
	  	cout << line << endl;
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
	  	long double a, b;
	  	while (infile >> a >> b){
	  		myfile << (int)floor((a - southmost)*scale/10.00) << " " << (int)floor((b - westmost)*scale/10.00) << endl;
	  	}
	  	myfile.close();
	  	//line[0] to line[3] is YYYY
	  	//line[5] to line[6] is MM
	  	//line[8] to line[9] is DD
	  	//line[11] to line[12] is HH
	  	//line[14] to line[15] is MM
	  	//line[17] to line[18] is SS
	  	//getline(infile, line);
	  	//getline(infile, line);
	  	//cout << line << endl;
	  	//while (infile >> a >> b)
	    printf ("%s\n", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
}
