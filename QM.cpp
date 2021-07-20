#include "QM.h"

int main() {
	// Determine the Input is variables ,minterms or don't cares
	char vmd;

	// Save the data of v, m or d
	string vstr, mstr, dstr, D_str;

	// Save the data in integer type
	int vint;
	vector<int> mint, dint;

	// Save the data in binary type
	vector<vector<int>> Binary_data;

	// Save the data of 
	vector<vector<vector<int>>> bit_0_order_int;
	vector<vector<vector<string>>> bit_0_order;

	// Save the Chart
	vector<vector<vector<vector<string>>>> Chart;

	// Save the data of combined minterms and dont cares
	vector<vector<vector<string>>> grouped_numbers;

	// Save the Prime Chart Elements
	vector<vector<string>> Prime;

	// Save the Prime Chart Elements Characters
	vector<vector<string>> Characters;

	// Save Stars
	vector<vector<string>> Stars;

	// Count each terms
	vector<vector<int>> accumulation;

	// File Output
	fstream File;
	File.open("Output_File.txt", ios::out); 
	if (!File){
		cerr << "Can't open file!\n";
		exit(1);     
	}

	// Save the file name
	string FileInput;
	
	interface(FileInput);

	// Read the File
	ifstream myfile(FileInput, ios::in);
	if (!myfile) {
		cerr << "Failed Opening" << endl;
		exit(1);
	}

	/* Arranging Inputs */
	while (myfile >> vmd) {
		if (vmd == '<') {
			getline(myfile, D_str);
			vstr = D_str;
		}
		else if (vmd == '{') {
			getline(myfile, D_str);
			mstr = D_str;
		}
		else if (vmd == '(') {
			getline(myfile, D_str);
			dstr = D_str;
		}
		else {
			cout << "Sorry that we cannot find those characters" << endl;
		}
	}
	
	/* Read the data, and transfer to integer type */
	vstr = vstr.substr(0, vstr.length() - 1);
	vector<string> reg_v = split(vstr, ", ");
	for (int i = 0; i < reg_v.size(); i++){
		vint = stoi(reg_v[i]);
	}

	/* Check if Correct Input *//*
		cout << vint << endl;
	}*/

	mstr = mstr.substr(0, mstr.length() - 1);
	vector<string> reg_m = split(mstr, ", ");
	for (int i = 0; i < reg_m.size(); i++){
		mint.push_back(stoi(reg_m[i]));
	}
	/* Check if Correct Input *//*
	for (int i = 0; i < mint.size(); i++){
		cout << mint[i] << endl;
	}*/

	dstr = dstr.substr(0, dstr.length() - 1);
	vector<string> reg_d = split(dstr, ",");
	for (int i = 0; i < reg_d.size(); i++){
		dint.push_back(stoi(reg_d[i]));
	}
	/* Check if Correct Input *//*
	for (int i = 0; i < dint.size(); i++){
		cout << dint[i] << endl;
	}*/

	Binary_data = getBinary(vint, mint, dint);

	/* Check if Correct Input *//*
	for (int i = 1; i < Binary_data.size(); i++){
		cout << Binary_data[i][vint + 1] << endl;
		cout << Binary_data[i][vint + 2] << endl;
		for (int j = 1; j < Binary_data[i].size() - 2; j++){
			cout << Binary_data[i][j];
		}
		cout << endl;
	}*/

	bit_0_order_int = getData(vint, Binary_data);

	/* Transform bit_0_order_int into <vector<vector<vector<string>>> type */
	for (int h = 0; h < bit_0_order_int.size(); h++){
		vector<vector<string>> temp_2D;
		for (int i = 0; i < bit_0_order_int[h].size(); i++){
			vector<string> temp_1D;
			for (int j = 0; j < bit_0_order_int[h][i].size(); j++){
				temp_1D.push_back(to_string(bit_0_order_int[h][i][j]));
			}
			temp_2D.push_back(temp_1D);
		}
		bit_0_order.push_back(temp_2D);
	}

	/* Check if Correct Input *//*
	for (int h = 0; h < bit_0_order.size(); h++){
		for (int i = 0; i < bit_0_order[h].size(); i++){
			for (int j = 0; j < bit_0_order[h][i].size(); j++){
				cout << bit_0_order[h][i][j];
			}
			cout << endl;
		}
	}*/

	Chart = getChart(vint, bit_0_order);

	/* Rearrange the sequence of term numbers */
	for (int a = 0; a < Chart.size(); a++){
		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				for (int d = 0; d < Chart[a][b][c].size(); d++){
					sort(Chart[a][b][c].begin() + vint, Chart[a][b][c].end());
				}
			}
		}
	}
	
	vector<vector<string>> BeUsed;
	for (int a = 0; a < Chart.size(); a++){
		vector<string> temp;
		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				for (int d = vint; d < Chart[a][b][c].size(); d++){
					temp.push_back(Chart[a][b][c][d]);
				}
			}
		}
		BeUsed.push_back(temp);
	}

	/* Check if Correct Input *//*
	for (int i = 0; i < BeUsed.size(); i++){
		for (int j = 0; j < BeUsed[i].size(); j++){
			cout << BeUsed[i][j] << " ";
		}
		cout << endl;
	}
	*/

	/* Check if don't cares */
	IfDontCares(vint, reg_d, Chart);
	
	/* In my opinion, Don't care terms should be checked if it is used in the chart */
	/* Check if being paired */
	IfPaired(vint, BeUsed, Chart);
	
	/* Check if the same */
	IfTheSame(vint, Chart);
	
	/* Check if correct input *//*
	for (int a = 0; a < Chart.size() - 1; a++){
		for (int b = 0; b < Chart[a].size(); b++){
			for (int c = 0; c < Chart[a][b].size(); c++){
				for (int d = 0; d < Chart[a][b][c].size(); d++){
					cout << Chart[a][b][c][d];
				}
				cout << endl;
			}
		}
	}*/
	
	setChart(File, vint, Chart);

	Prime = getPrimeChartElements(vint, Chart);

	/* Check if correct input *//*
	for (int i = 0; i < Prime.size(); i++){
		for (int j = 0; j < Prime[i].size(); j++){
			cout << Prime[i][j];
		}
		cout << endl;
	}
	*/

	Characters = getCharacters(vint, Prime);

	/* Check if correct input *//*
	for (int i = 0; i < Characters.size(); i++){
		for (int j = 0; j < Characters[i].size(); j++){
			cout << Characters[i][j];
		}
		cout << endl;
	}
	*/
	
	Stars = getStars(vint, reg_m, Prime);

	/* Check if correct input *//*
	for (int i = 0; i < Stars.size(); i++){
		for (int j = 0; j <Stars[i].size(); j++){
			cout << right << setw(3) << fixed << Stars[i][j];
		}
		cout << endl;
	}
	*/
	
	setPrimeChart(File, reg_m, Characters, Stars);
	
	setSentence(File, vint, reg_m, Stars, Characters);
	
	myfile.close();
	File.close();

	return 0;
}