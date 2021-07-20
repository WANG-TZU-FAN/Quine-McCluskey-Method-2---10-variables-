
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<math.h>

using namespace std;

/* Split the string */
vector<string> split(const string& strs, const string& delim) {
	// Store the Data in that line
	vector<string> res;
	if (strs == "") return res;
	char* str = new char[strs.size() + 1];
	strcpy(str, strs.c_str());
	char* d = new char[delim.size() + 1];
	strcpy(d, delim.c_str());
	char* p = strtok(str, d);
	while (p) {
		string temp = p;
		res.push_back(temp);
		p = strtok(NULL, d);
	}
	delete[]str;
	delete[]d;
	return res;
}

/* Change minterms and don't cares to binary */
vector<vector<int>> getBinary(int variables, vector<int> minterms, vector<int> dcs){

	vector<vector<int>> toBinary;
	int temp_number = 0;
	int temp_Binary = 0;
	int count = 0;

	for (int i = 0; i < minterms.size(); i++){
		vector<int> toBinary_1D;
		count = 0;
		temp_number = minterms[i];
		for (int j = 0; j < variables + 2; j++){
			if (j == 0){
				toBinary_1D.push_back(minterms[i]);
			}
			else{
				if (temp_number % 2 == 1){
					count++;
				}
				toBinary_1D.push_back(temp_number % 2);
				temp_number = temp_number / 2;
			}
		}
		reverse(toBinary_1D.begin(), toBinary_1D.end());
		toBinary_1D.push_back(count);
		toBinary.push_back(toBinary_1D);
	}

	for (int i = 0; i < dcs.size(); i++){
		vector<int> toBinary_1D;
		count = 0;
		temp_number = dcs[i];
		for (int j = 0; j < variables + 2; j++){
			if (j == 0){
				toBinary_1D.push_back(dcs[i]);
			}
			else{
				if (temp_number % 2 == 1){
					count++;
				}
				toBinary_1D.push_back(temp_number % 2);
				temp_number = temp_number / 2;
			}
		}
		reverse(toBinary_1D.begin(), toBinary_1D.end());
		toBinary_1D.push_back(count);
		toBinary.push_back(toBinary_1D);
	}

	return toBinary;
}

/* Get the input data*/
vector<vector<vector<int>>> getData(int variables, vector<vector<int>> Binary_data){

	// Group the data by different bits
	vector<vector<int>> bit_0;
	vector<vector<int>> bit_1;
	vector<vector<int>> bit_2;
	vector<vector<int>> bit_3;
	vector<vector<int>> bit_4;
	vector<vector<int>> bit_5;
	vector<vector<int>> bit_6;
	vector<vector<int>> bit_7;
	vector<vector<int>> bit_8;
	vector<vector<int>> bit_9;
	vector<vector<int>> bit_10;

	// Return Data
	vector<vector<vector<int>>> Data;

	for (int i = 0; i < Binary_data.size(); i++){
		vector<int> temp;


		for (int j = 1; j < variables + 1; j++){
			temp.push_back(Binary_data[i][j]);
		}
		if (Binary_data[i][variables + 2] == 0){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_0.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 1){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_1.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 2){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_2.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 3){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_3.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 4){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_4.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 5){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_5.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 6){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_6.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 7){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_7.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 8){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_8.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 9){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_9.push_back(temp);
		}
		if (Binary_data[i][variables + 2] == 10){
			temp.push_back(Binary_data[i][variables + 1]);
			bit_10.push_back(temp);
		}
	}

	/* Check if Correct Input *//*
								for (int i = 0; i < bit_1.size(); i++){
								for (int j = 0; j < bit_1[i].size(); j++){
								cout << bit_1[i][j];
								}
								cout << endl;
								}*/

	Data.push_back(bit_0);
	Data.push_back(bit_1);
	Data.push_back(bit_2);
	Data.push_back(bit_3);
	Data.push_back(bit_4);
	Data.push_back(bit_5);
	Data.push_back(bit_6);
	Data.push_back(bit_7);
	Data.push_back(bit_8);
	Data.push_back(bit_9);
	Data.push_back(bit_10);

	return Data;

}

/* group by Quine-Mccluskey function*/
vector<vector<string>> group(int number, vector<vector<string>>& first, vector<vector<string>>& second){

	int count = 0;
	vector<vector<string>> group_2D;

	for (int i = 0; i < first.size(); i++){
		for (int j = 0; j < second.size(); j++){
			count = 0;
			for (int k = 0; k < second[j].size() - number; k++){
				if (first[i][k] != second[j][k]){
					count++;
				}
			}
			if (count == 1){
				vector<string> group_1D;
				for (int k = 0; k < first[i].size() - number; k++){
					if (first[i][k] == second[j][k] && first[i][k] == "0"){
						group_1D.push_back("0");
					}
					else if (first[i][k] == second[j][k] && first[i][k] == "1"){
						group_1D.push_back("1");
					}
					else if (first[i][k] == second[j][k] && first[i][k] == "-"){
						group_1D.push_back("-");
					}
					else if (first[i][k] != second[j][k]){
						group_1D.push_back("-");
					}
				}
				for (int m = 0; m < number; m++){
					group_1D.push_back(first[i][first[i].size() - m - 1]);
					group_1D.push_back(second[j][second[j].size() - m - 1]);
				}
				group_2D.push_back(group_1D);
			}
			/* Check if correct input */
			//cout << count;
		}
	}
	return group_2D;
}

/* Get the member of chart */
vector<vector<vector<vector<string>>>> getChart(int vint, vector<vector<vector<string>>> bit_0_order){

	vector<vector<vector<vector<string>>>> Chart;

	// Group the data by different bits and orders
	vector<vector<vector<string>>> bit_1_order;
	vector<vector<vector<string>>> bit_2_order;
	vector<vector<vector<string>>> bit_3_order;
	vector<vector<vector<string>>> bit_4_order;
	vector<vector<vector<string>>> bit_5_order;
	vector<vector<vector<string>>> bit_6_order;
	vector<vector<vector<string>>> bit_7_order;
	vector<vector<vector<string>>> bit_8_order;
	vector<vector<vector<string>>> bit_9_order;
	vector<vector<vector<string>>> bit_10_order;

	Chart.push_back(bit_0_order);
	for (int i = 0; i < vint; i++){
		bit_1_order.push_back(group(1, bit_0_order[i], bit_0_order[i + 1]));
	}
	Chart.push_back(bit_1_order);
	if (vint > 1){
		for (int i = 0; i < vint - 1; i++){
			bit_2_order.push_back(group(2, bit_1_order[i], bit_1_order[i + 1]));
		}
	}
	Chart.push_back(bit_2_order);
	if (vint > 2){
		for (int i = 0; i < vint - 2; i++){
			bit_3_order.push_back(group(4, bit_2_order[i], bit_2_order[i + 1]));
		}
	}
	Chart.push_back(bit_3_order);
	if (vint > 3){
		for (int i = 0; i < vint - 3; i++){
			bit_4_order.push_back(group(8, bit_3_order[i], bit_3_order[i + 1]));
		}
	}
	Chart.push_back(bit_4_order);
	if (vint > 4){
		for (int i = 0; i < vint - 4; i++){
			bit_5_order.push_back(group(16, bit_4_order[i], bit_4_order[i + 1]));
		}
		Chart.push_back(bit_5_order);
	}
	if (vint > 5){
		for (int i = 0; i < vint - 5; i++){
			bit_6_order.push_back(group(32, bit_5_order[i], bit_5_order[i + 1]));
		}
		Chart.push_back(bit_6_order);
	}
	if (vint > 6){
		for (int i = 0; i < vint - 6; i++){
			bit_7_order.push_back(group(64, bit_6_order[i], bit_6_order[i + 1]));
		}
		Chart.push_back(bit_7_order);
	}
	if (vint > 7){
		for (int i = 0; i < vint - 7; i++){
			bit_8_order.push_back(group(128, bit_7_order[i], bit_7_order[i + 1]));
		}
		Chart.push_back(bit_8_order);
	}
	if (vint > 8){
		for (int i = 0; i < vint - 8; i++){
			bit_9_order.push_back(group(256, bit_8_order[i], bit_8_order[i + 1]));
		}
		Chart.push_back(bit_9_order);
	}
	if (vint > 9){
		for (int i = 0; i < vint - 9; i++){
			bit_10_order.push_back(group(512, bit_9_order[i], bit_9_order[i + 1]));
		}
		Chart.push_back(bit_10_order);
	}

	/* Check if Correct Input *//*
								for (int h = 0; h < bit_1_order.size(); h++){
								for (int i = 0; i < bit_1_order[h].size(); i++){
								for (int j = 0; j < bit_1_order[h][i].size(); j++){
								cout << bit_1_order[h][i][j];
								}
								cout << endl;
								}
								}

								for (int i = 0; i < bit_2_order[0].size(); i++){
								for (int j = 0; j < bit_2_order[0][i].size(); j++){
								cout << bit_2_order[0][i][j];
								}
								cout << endl;
								}*/

	return Chart;
}

/* Check if don't cares */
void IfDontCares(int vint, vector<string> reg_d, vector<vector<vector<vector<string>>>>& Chart){
	for (int b = 0; b < Chart[0].size(); b++){
		for (int c = 0; c < Chart[0][b].size(); c++){
			for (int d = vint; d < Chart[0][b][c].size(); d++){
				for (int j = 0; j < reg_d.size(); j++){
					if (Chart[0][b][c][d] == reg_d[j]){
						Chart[0][b][c].push_back("d");
						break;
					}
				}
			}
		}
	}
}

/* Check if being paired */
/* In my opinion, Don't care terms should be checked if it is used in the chart */
void IfPaired(int vint, vector<vector<string>> BeUsed, vector<vector<vector<vector<string>>>>& Chart){
	for (int a = 0; a < Chart.size() - 1; a++){
		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				int count = 0;
				for (int d = vint; d < Chart[a][b][c].size(); d++){
					for (int j = 0; j < BeUsed[a + 1].size(); j++){
						if (Chart[a][b][c][d] == BeUsed[a + 1][j]){
							count++;
							break;
						}
					}
				}
				if (count == pow(2, a)){
					Chart[a][b][c].push_back("v");
				}
			}
		}
	}
}

void IfTheSame(int vint, vector<vector<vector<vector<string>>>>& Chart){
	// Find the maximum size of group sizes
	int max = 0;
	for (int a = 0; a < Chart.size(); a++){
		for (int b = 0; b < Chart[a].size(); b++){
			if (Chart[a][b].size() > max){
				max = Chart[a][b].size();
			}
		}
	}

	/* Check if the same */
	int count_if_the_same = 0;
	for (int n = 0; n < max; n++){
		for (int a = 0; a < Chart.size() - 1; a++){
			for (int b = 0; b < Chart[a].size(); b++){
				for (int c = 0; c < Chart[a][b].size(); c++){
					count_if_the_same = 0;
					for (int d = vint; d < vint + pow(2, a); d++){
						if (c > n){
							if (Chart[a][b][c][d] == Chart[a][b][c - n - 1][d]){
								count_if_the_same++;
							}
							if (count_if_the_same == pow(2, a)){
								Chart[a][b][c - n - 1].push_back("x");
								break;
							}
						}
					}
				}
			}
		}
	}
}

/* Print the QM Chart */
void setChart(fstream& File,int vint, vector<vector<vector<vector<string>>>> Chart){
	int count_after = 0;
	for (int a = 0; a < Chart.size(); a++){
		if (Chart[a][0].size() != 0){
			for (int i = 0; i < vint + 4 + 5 * pow(2, a); i++){
				File << "=";
				cout << "=";
			}
			File << endl;
			cout << endl;
			File << "Column " << a + 1 << endl;
			cout << "Column " << a + 1 << endl;
			for (int i = 0; i < vint + 4 + 5 * pow(2, a); i++){
				File << "=";
				cout << "=";
			}
			File << endl;
			cout << endl;
		}

		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				if (Chart[a][b][c][Chart[a][b][c].size() - 1] == "v" ||
					Chart[a][b][c][Chart[a][b][c].size() - 1] == "d" ||
					Chart[a][b][c][Chart[a][b][c].size() - 1] == "x"){
					File << Chart[a][b][c][Chart[a][b][c].size() - 1] << " ";
					cout << Chart[a][b][c][Chart[a][b][c].size() - 1] << " ";
				}
				else{
					File << "  ";
					cout << "  ";
				}
				for (int d = 0; d < vint; d++){
					File << Chart[a][b][c][d];
					cout << Chart[a][b][c][d];
				}
				File << " : ";
				cout << " : ";
				for (int d = vint; d < vint + pow(2, a); d++){
					File << setw(4) << Chart[a][b][c][d];
					cout << setw(4) << Chart[a][b][c][d];
					if (d != vint + pow(2, a) - 1){
						File << ",";
						cout << ",";
					}
				}
				File << endl;
				cout << endl;
			}

			count_after = 0;

			for (int i = b + 1; i < Chart[a].size(); i++){
				if (Chart[a][i].size() != 0){
					count_after++;
				}
			}

			if (Chart[a][b].size() != 0){
				if (count_after == 0){
					File << endl;
					cout << endl;
				}
				else{
					for (int i = 0; i < vint + 4 + 5 * pow(2, a); i++){
						File << "-";
						cout << "-";
					}
					File << endl;
					cout << endl;
				}
			}
		}
	}
}

/* Get Prime Chart Elements */
vector<vector<string>> getPrimeChartElements(int vint, vector<vector<vector<vector<string>>>> Chart){
	vector<vector<string>> Prime;
	for (int a = 0; a < Chart.size(); a++){
		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				if (Chart[a][b][c][Chart[a][b][c].size() - 1] != "v" &&
					Chart[a][b][c][Chart[a][b][c].size() - 1] != "d" &&
					Chart[a][b][c][Chart[a][b][c].size() - 1] != "x"){
					vector<string> temp;
					for (int d = 0; d < vint; d++){
						temp.push_back(Chart[a][b][c][d]);
					}
					for (int d = vint; d < vint + pow(2, a); d++){
						temp.push_back(Chart[a][b][c][d]);
					}
					Prime.push_back(temp);
				}
			}
		}
	}
	return Prime;
}

/* Change Chart Elements into character form */
vector<vector<string>> getCharacters(int vint, vector<vector<string>> Prime){

	vector<vector<string>> Characters;

	for (int i = 0; i < Prime.size(); i++){
		vector<string> temp;
		for (int j = 0; j < vint; j++){
			if (j == 0 && Prime[i][j] == "0"){
				temp.push_back("a'");
			}
			if (j == 0 && Prime[i][j] == "1"){
				temp.push_back("a ");
			}
			if (j == 1 && Prime[i][j] == "0"){
				temp.push_back("b'");
			}
			if (j == 1 && Prime[i][j] == "1"){
				temp.push_back("b ");
			}
			if (j == 2 && Prime[i][j] == "0"){
				temp.push_back("c'");
			}
			if (j == 2 && Prime[i][j] == "1"){
				temp.push_back("c ");
			}
			if (j == 3 && Prime[i][j] == "0"){
				temp.push_back("d'");
			}
			if (j == 3 && Prime[i][j] == "1"){
				temp.push_back("d ");
			}
			if (j == 4 && Prime[i][j] == "0"){
				temp.push_back("e'");
			}
			if (j == 4 && Prime[i][j] == "1"){
				temp.push_back("e ");
			}
			if (j == 5 && Prime[i][j] == "0"){
				temp.push_back("f'");
			}
			if (j == 5 && Prime[i][j] == "1"){
				temp.push_back("f ");
			}
			if (j == 6 && Prime[i][j] == "0"){
				temp.push_back("g'");
			}
			if (j == 6 && Prime[i][j] == "1"){
				temp.push_back("g ");
			}
			if (j == 7 && Prime[i][j] == "0"){
				temp.push_back("h'");
			}
			if (j == 7 && Prime[i][j] == "1"){
				temp.push_back("h ");
			}
			if (j == 8 && Prime[i][j] == "0"){
				temp.push_back("i'");
			}
			if (j == 8 && Prime[i][j] == "1"){
				temp.push_back("i ");
			}
			if (j == 9 && Prime[i][j] == "0"){
				temp.push_back("j'");
			}
			if (j == 9 && Prime[i][j] == "1"){
				temp.push_back("j ");
			}
		}
		Characters.push_back(temp);
	}
	return Characters;
}

/* Seting Stars */
vector<vector<string>> getStars(int vint, vector<string> reg_m, vector<vector<string>> Prime){

	vector<vector<string>> Stars_or_Blanks;

	vector<int> count;

	for (int i = 0; i < reg_m.size(); i++){
		count.push_back(0);
	}

	for (int i = 0; i < Prime.size(); i++){
		vector<string> temp;
		for (int i = 0; i < count.size(); i++){
			count[i] = 0;
		}
		for (int j = vint; j < Prime[i].size(); j++){
			for (int k = 0; k < reg_m.size(); k++){
				if (reg_m[k] == Prime[i][j]){
					count[k]++;
				}
			}
		}
		for (int k = 0; k < reg_m.size(); k++){
			if (count[k] != 0){ temp.push_back("* "); }
			else{ temp.push_back("  "); }
		}
		Stars_or_Blanks.push_back(temp);
	}
	return Stars_or_Blanks;
}

/* Print The Prime Chart */
void setPrimeChart(fstream &File, vector<string> reg_m, vector<vector<string>> Characters, vector<vector<string>> Stars){
	for (int i = 0; i < 24 + 6 * reg_m.size(); i++){
		File << "=";
		cout << "=";
	}
	File << endl;
	cout << endl;
	File << "Result" << endl;
	cout << "Result" << endl;
	for (int i = 0; i < 24 + 6 * reg_m.size(); i++){
		File << "=";
		cout << "=";
	}
	File << endl;
	cout << endl;
	File << right << setw(25) << fixed << "|";
	cout << right << setw(25) << fixed << "|";

	for (int i = 0; i < reg_m.size(); i++){
		File << right << setw(5) << fixed << reg_m[i];
		cout << right << setw(5) << fixed << reg_m[i];
		if (i < reg_m.size() - 1){
			File << ",";
			cout << ",";
		}
	}
	File << endl;
	cout << endl;
	File << "------------------------+";
	cout << "------------------------+";
	for (int i = 0; i < 6 * reg_m.size() - 1; i++){
		File << "-";
		cout << "-";
	}
	File << endl;
	cout << endl;
	for (int i = 0; i < Characters.size(); i++){
		for (int j = 0; j < Characters[i].size(); j++){
			File << Characters[i][j];
			cout << Characters[i][j];
		}
		File << setw(25 - 2 * Characters[i].size()) << "|";
		cout << setw(25 - 2 * Characters[i].size()) << "|";
		for (int j = 0; j < Stars[i].size(); j++){
			File << right << setw(6) << fixed << Stars[i][j];
			cout << right << setw(6) << fixed << Stars[i][j];
		}
		File << endl;
		cout << endl;
	}
	File << "------------------------+";
	cout << "------------------------+";
	for (int i = 0; i < 6 * reg_m.size() - 1; i++){
		File << "-";
		cout << "-";
	}
	File << endl;
	cout << endl;
}

/* Print The Output*/
void setSentence(fstream &File, int vint, vector<string> reg_m, vector<vector<string>> Stars, vector<vector<string>> Characters){
	vector<int> Accumulation;
	vector<int> count;
	vector<int> EssentialMembers;
	vector<int> LeftTerms;
	vector<vector<string>> EssentialPrimeImplicants;
	vector<vector<string>> LeftTermsCharacters;
	int left_stars = 0;

	File << endl;
	cout << endl;

	char A_to_J = 'A';
	File << "F(";
	cout << "F(";
	for (int i = 0; i < vint; i++){
		File << A_to_J;
		cout << A_to_J;
		A_to_J++;
		if (i < vint - 1){
			File << ",";
			cout << ",";
		}
	}
	File << ") = ";
	cout << ") = ";


	// set Accumulation to zero
	for (int i = 0; i < reg_m.size(); i++){
		Accumulation.push_back(0);
	}

	// set count to zero
	for (int i = 0; i < Stars.size(); i++){
		count.push_back(0);
	}

	// Accumulate times that minterms had been used 
	for (int i = 0; i < Stars.size(); i++){
		for (int j = 0; j < Stars[i].size(); j++){
			if (Stars[i][j] == "* "){
				Accumulation[j]++;
			}
		}
	}

	// if Accumulation times is 1, it is essential 
	for (int n = 0; n < Accumulation.size(); n++){
		if (Accumulation[n] == 1){
			for (int i = 0; i < Stars.size(); i++){
				for (int j = 0; j < Stars[i].size(); j++){
					if (count[i] == 0 && Stars[i][n] == "* "){
						EssentialMembers.push_back(i);
						Accumulation[n] = 0;
						Stars[i][n] = "  ";
						count[i]++;
					}
				}
			}
		}
	}

	// Set Essential Prime Implicants
	for (int member = 0; member < EssentialMembers.size(); member++){
		for (int i = 0; i < Characters.size(); i++){
			if (i == EssentialMembers[member]){
				int count = 0;
				vector<string> temp;
				for (int j = 0; j < Characters[i].size(); j++){
					temp.push_back(Characters[i][j]);
				}
				EssentialPrimeImplicants.push_back(temp);
			}
		}
	}

	// Output Essential Prime Implicants
	for (int i = 0; i < EssentialPrimeImplicants.size(); i++){
		for (int j = 0; j < EssentialPrimeImplicants[i].size(); j++){
			File << EssentialPrimeImplicants[i][j];
			cout << EssentialPrimeImplicants[i][j];
		}
		if (i < EssentialPrimeImplicants.size() - 1){
			File << " + ";
			cout << " + ";
		}
	}

	// Take off essential prime implicants
	for (int i = 0; i < EssentialMembers.size(); i++){
		for (int j = 0; j < Stars.size(); j++){
			if (j == EssentialMembers[i]){
				for (int k = 0; k < Stars[j].size(); k++){
					if (Stars[j][k] == "* "){
						for (int l = 0; l < Stars.size(); l++){
							Stars[l][k] = "  ";
						}
					}
				}
			}
		}
	}

	// find out if there is still stars
	for (int i = 0; i < Stars.size(); i++){
		for (int j = 0; j < Stars[i].size(); j++){
			if (Stars[i][j] == "* "){
				left_stars = 1;
				break;
			}
		}
		break;
	}

	while (left_stars == 1){
		// Accumulate times that Left Terms had been used 
		for (int i = 0; i < Stars.size(); i++){
			for (int j = 0; j < Stars[i].size(); j++){
				if (Stars[i][j] == "* "){
					LeftTerms.push_back(i);
					break;
				}
			}
		}

		// Count that which term has the mosr stars
		vector<int> count_stars_of_left_terms;

		for (int n = 0; n < LeftTerms.size(); n++){
			for (int i = 0; i < Stars.size(); i++){
				if (i == LeftTerms[n]){
					int temp = 0;
					for (int j = 0; j < Stars[i].size(); j++){
						if (Stars[i][j] == "* "){
							temp++;
						}
					}
					count_stars_of_left_terms.push_back(temp);
				}
			}
		}

		// which term in Left_Terms[Used_term]
		int Used_Term = 0;
		for (int i = 1; i < count_stars_of_left_terms.size(); i++){
			if (count_stars_of_left_terms[i] > Used_Term){
				Used_Term = i;
			}
		}

		// Save the left terms that be choosen
		vector<string> temp;
		for (int j = 0; j < Characters[LeftTerms[Used_Term]].size(); j++){
			temp.push_back(Characters[LeftTerms[Used_Term]][j]);
		}
		LeftTermsCharacters.push_back(temp);


		// Clean Stars
		for (int j = 0; j < Stars[LeftTerms[Used_Term]].size(); j++){
			if (Stars[LeftTerms[Used_Term]][j] == "* "){
				for (int i = 0; i < Stars.size(); i++){
					Stars[i][j] = "  ";
				}
			}
		}

		// find out if there is still stars
		left_stars = 0;

		for (int i = 0; i < Stars.size(); i++){
			for (int j = 0; j < Stars[i].size(); j++){
				if (Stars[i][j] == "* "){
					left_stars = 1;
					break;
				}
			}
			break;
		}
	}


	for (int i = 0; i < LeftTermsCharacters.size(); i++){
		if (EssentialPrimeImplicants.size() == 0 && i == 0){

		}
		else{
			File << " + ";
			cout << " + ";
		}
		for (int j = 0; j < LeftTermsCharacters[i].size(); j++){
			File << LeftTermsCharacters[i][j];
			cout << LeftTermsCharacters[i][j];
		}
	}
	File << endl << endl;
	cout << endl << endl;

	/* Check if correct inputs *//*
	for (int i = 0; i < Stars.size(); i++){
		 for (int j = 0; j < Stars[i].size(); j++){
			 cout << right << setw(6) << fixed << Stars[i][j];
		 }
	cout << endl;
	}*/
}

void interface(string& FileInput){
	int mode = 0;

	cout << "Which File would you like to test ?" << endl;
	cout << "1) 10 variable test with don't cares" << endl;
	cout << "2) 9 variable with redundant terms" << endl;
	cout << "3) 8 variables with patrick method" << endl;
	cout << "4) 4 variables with fully don't cares" << endl;
	cout << "5) Your own file ( Please enter your file name with .txt) " << endl << endl;
	cout << "You decide: ";
	cin >> mode;

	switch (mode) {
	case 1:
		FileInput = "10_Variable_Test.txt";
		break;
	case 2:
		FileInput = "9_Variable_Test.txt";
		break;
	case 3:
		FileInput = "8_Variable_Test.txt";
		break;
	case 4:
		FileInput = "4_Variable_Test.txt";
		break;
	case 5:
		cout << endl;
		cout << "Please enter your file name: ";
		cin >> FileInput;
		break;
	default:
		cout << " Sorry that we don't support this choice, please retry the code! ";
		break;
	}
}