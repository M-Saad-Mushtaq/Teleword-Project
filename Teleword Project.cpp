#include<iostream>
#include<fstream>
#include<Windows.h>
#include<chrono>
using namespace std;

void display(char grid[15][15], char allWords[500]);
void turnCaps(char words[500]);
void color(char grid[15][15]);
int numOfWords(char words[500]);
void a_Once(char grid[15][15], char allWords[500]);
void s_by_s(char grid[15][15], char allWords[500]);
void stat(char allWords[500], char grid[15][15]);
void teleword(char grid[15][15]);
bool forwardCheck(char grid[15][15], char allWords[500]);
bool reverseCheck(char grid[15][15], char allWords[500]);
bool upCheck(char grid[15][15], char allWords[500]);
bool downCheck(char grid[15][15], char allWords[500]);
bool diagonalDown_L2R_Check(char grid[15][15], char allWords[500]);
bool diagonalUp_R2L_Check(char grid[15][15], char allWords[500]);
bool diagonalUp_L2R_Check(char grid[15][15], char allWords[500]);
bool diagonalDown_R2L_Check(char grid[15][15], char allWords[500]);

int clrGrid[15][15] = {};
int varF = 0, varB = 0, varU = 0, varDw = 0, varD1 = 0, varD2 = 0, varD3 = 0, varD4 = 0;
int cf = 0, cr = 0, cu = 0, cdw = 0, cd1 = 0, cd2 = 0, cd3 = 0, cd4 = 0;
int lng_word = 0, shrt_word = 6923, avg_word = 0, t_scatter = 0, h_row = 0, h_col = 0;
int row[15] = {}, col[15] = {};

int main()
{
	char grid[15][15], allWords[500];

	ifstream readFile;
	readFile.open("teleword.txt");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			readFile >> grid[i][j];
		}
	}
	bool check = false;
	for (int i = 0; !check; i++)
	{
		readFile >> allWords[i];
		if (allWords[i] == '.')
		{
			check = true;
		}
	}
	readFile.close();
	display(grid, allWords);
	turnCaps(allWords);
	char in;
	while (true)
	{
		cout << "\nPress S to solve the puzzle at once.\nPress T to solve the puzzle step by step.\nPress X to print puzzle statistics.\n";
		cout << "Enter Option: ";
		cin >> in;
		if (in >= 97 && in <= 122) in -= 32;
		if (in == 'S'|| in == 'T' || in == 'X') break;
		else
			cout << "Wrong Input!!\n";
	}

	if (in == 'S') {
		a_Once(grid, allWords);
		color(grid);
		cout << endl << "Teleword: ";
		teleword(grid);
		cout << endl;
	}
	else if (in == 'T') {
		s_by_s(grid, allWords);
		cout << endl << "Teleword: ";
		teleword(grid);
		cout << endl;
	}
	else {
		stat(allWords, grid);
	}
	
	return 0;
}


void display(char grid[15][15], char allWords[500])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; true ; i++)
	{
		cout << allWords[i];
		if (allWords[i] == '.')
		{
			break;
		}
	}
	cout << endl;
}
int numOfWords(char words[500])
{
	int noWords = 0, temp = 0;
	for (int i = 0; true; i++)
	{
		if (words[i] == ',')
		{
			noWords++;
			if (temp > lng_word) lng_word = temp;
			else if (temp < shrt_word) shrt_word = temp;
			avg_word += temp;
			temp = 0;
		}
		else if (words[i] == '.')
		{
			noWords++;
			break;
		}
		else temp++;
	}
	avg_word = avg_word / noWords;
	return noWords;
}

void turnCaps(char words[500])
{
	for (int i = 0; true; i++)
	{
		if (words[i] == '.')
			break;
		if (words[i] != ',' && words[i] >= 97 && words[i] <= 122)
		{
			words[i] -= 32;
		}
	}
}

void color(char grid[15][15])
{
	system("cls");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (clrGrid[i][j] == 1)
			{
				cout << "\x1B[33m" << grid[i][j] << " ";
			}
			else if (clrGrid[i][j] == 2)
			{
				cout << "\x1B[34m" << grid[i][j] << " ";
			}
			else if (clrGrid[i][j] >= 3)
			{
				cout << "\x1B[31m" << grid[i][j] << " ";
			}
			else
				cout << "\x1B[37m" << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\x1B[37m";
}

void a_Once(char grid[15][15], char allWords[500])
{
	int noOfWords = numOfWords(allWords);
	for (int i = 0; i < noOfWords; i++)
	{
		forwardCheck(grid, allWords);
		reverseCheck(grid, allWords);
		upCheck(grid, allWords);
		downCheck(grid, allWords);
		diagonalDown_L2R_Check(grid, allWords);
		diagonalUp_R2L_Check(grid, allWords);
		diagonalUp_L2R_Check(grid, allWords);
		diagonalDown_R2L_Check(grid, allWords);
	}
	
}

void s_by_s(char grid[15][15], char allWords[500])
{
	int l = 0;
	int noOfWords = numOfWords(allWords);
	for (int i = 0; i < noOfWords; i++)
	{
		if (i != 0) system("pause");
		forwardCheck(grid, allWords);
		reverseCheck(grid, allWords);
		upCheck(grid, allWords);
		downCheck(grid, allWords);
		diagonalDown_L2R_Check(grid, allWords);
		diagonalUp_R2L_Check(grid, allWords);
		diagonalUp_L2R_Check(grid, allWords);
		diagonalDown_R2L_Check(grid, allWords);
		color(grid);
		cout << endl;
		for (int vr = 0; true; vr++)
		{
			cout << allWords[vr];
			if (allWords[vr] == '.') break;
		}
		cout << endl << endl;
	}
	
}

void stat(char allWords[500], char grid[15][15])
{
	auto start = chrono::steady_clock::now();
	a_Once(grid, allWords);
	auto end = chrono::steady_clock::now();
	color(grid);
	cout << endl << "Teleword: ";
	teleword(grid);
	cout << endl << endl;
	cout << endl << "Time Taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
	int not_imp = numOfWords(allWords);
	cout << "Longest Word Length: " << lng_word << endl;
	cout << "Shortest Word Length: " << shrt_word << endl;
	cout << "Average Word Length: " << avg_word << endl;
	cout << "Word Distribution: " << "Horizontal: " << cf + cr << " (" << cf << ", " << cr << ")" << " Vertical: " << cu + cdw << " (" << cdw << ", " << cu << ")" << " Diagonal: " << cd1 + cd2 + cd3 + cd4 << " (" << cd1 + cd3 << ", " << cd2 + cd4 << ")" << endl;
	cout << "Teleword Scatter: " << t_scatter << endl;
	for (int i = 0; i < 15; i++)
	{
		if (col[i] >= col[h_col]) h_col = i;
		if (row[i] >= row[h_row]) h_row = i;
	}
	cout << "Heaviest Row: " << h_row << endl;
	cout << "Heaviest Column: " << h_col << endl;
}

void teleword(char grid[15][15])
{
	int temp = -1;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (clrGrid[i][j] == 0)
			{
				cout << grid[i][j];
				if (i > temp) t_scatter++, temp = i;
			}
		}
	}
}

bool forwardCheck(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_j;
	for (int i = 0; true; i++)
	{
		word[i] = allWords[varF++];
		if (allWords[varF] == ',' || allWords[varF] == '.') 
		{
			wordSize = i + 1;
			varF++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 1;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			k = 0;
			count = 1;
			if (word[k] == grid[i][j])
			{
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk)
				{
					if (word[k] == grid[i][j])
					{
						j++, count++, k++;
					}
					else
						j--,fullChk = false;
				}
				if (fullChk)
				{
					row[i]++;
					cf++;
					for (int p = initial_j; p < j; p++)
						col[p]++, clrGrid[i][p]++;
				}
			}
			if (count == wordSize) return true;
		}
	}
	return false;
}

bool reverseCheck(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_j;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varB++];
		if (allWords[varB] == ',' || allWords[varB] == '.')
		{
			wordSize = i + 1;
			varB++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 1;
	for (int i = 14; i >= 0; i--)
	{
		for (int j = 14; j >= 0; j--)
		{
			k = 0;
			count = 1;
			if (word[k] == grid[i][j])
			{
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk)
				{
					if (word[k] == grid[i][j])
					{
						j--, count++, k++;
					}
					else
						j++,fullChk = false;
				}
				if (fullChk)
				{
					row[i]++;
					cr++;
					for (int p = initial_j; p > j; p--)
						col[p]++, clrGrid[i][p]++;
				}
			}
			if (count == wordSize) return true;
		}
	}


	return false;
}

bool upCheck(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varU++];
		if (allWords[varU] == ',' || allWords[varU] == '.')
		{
			wordSize = i + 1;
			varU++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 1;
	for (int j = 0; j < 15; j++)
	{
		for (int i = 14; i >= 0; i--)
		{
			k = 0;
			count = 1;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				bool fullChk = true;
				while (k < wordSize && fullChk) {
					if (word[k] == grid[i][j])
					{
						i--, count++, k++;
					}
					else
						i++, fullChk = false;
				}
				if (fullChk)
				{
					col[j]++;
					cu++;
					for (int p = initial_i; p > i; p--)
						row[p]++, clrGrid[p][j]++;
				}
			}
			if (count == wordSize) return true;
		}
	}
	return false;
}

bool downCheck(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varDw++];
		if (allWords[varDw] == ',' || allWords[varDw] == '.')
		{
			wordSize = i + 1;
			varDw++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 1;
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			k = 0;
			count = 1;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				bool fullChk = true;
				while (k < wordSize && fullChk) {
					if (word[k] == grid[i][j])
					{
						i++, count++, k++;
					}
					else
						i--, fullChk = false;
				}
				if (fullChk)
				{
					col[j]++;
					cdw++;
					for (int p = initial_i; p < i; p++)
						row[p]++, clrGrid[p][j]++;
				}
			}
			if (count == wordSize) return true;
		}
	}
	return false;
}

bool diagonalDown_L2R_Check(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i, initial_j;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varD1++];
		if (allWords[varD1] == ',' || allWords[varD1] == '.')
		{
			wordSize = i + 1;
			varD1++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			k = 0;
			count = 0;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk ) {
					if (word[k] == grid[i][j])
					{
						i++, j++, count++, k++;
					}
					else if (word[k] != grid[i][j] || i == 14 || j == 14)
						i = initial_i, j = initial_j, fullChk = false;
				}
				if (fullChk)
				{
					cd1++;
					for (int p = initial_i, q = initial_j; p < i && q < j; p++,q++)
						row[p]++, col[q]++, clrGrid[p][q]++;
				}
			}
			if (count == wordSize)
				return true;
		}
	}
	return false;
}

bool diagonalUp_R2L_Check(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i, initial_j;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varD2++];
		if (allWords[varD2] == ',' || allWords[varD2] == '.')
		{
			wordSize = i + 1;
			varD2++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 0;
	for (int i = 14; i >= 0; i--)
	{
		for (int j = 14; j >= 0; j--)
		{
			k = 0;
			count = 0;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk) {
					if (word[k] == grid[i][j])
					{
						i--, j--, count++, k++;
					}
					else if (word[k] != grid[i][j] || i == 0 || j == 0)
						i = initial_i, j = initial_j, fullChk = false;
				}
				if (fullChk)
				{
					cd2++;
					for (int p = initial_i, q = initial_j; p > i && q > j; p--, q--)
						row[p]++, col[q]++, clrGrid[p][q]++;
				}
			}
			if (count == wordSize)
				return true;
		}
	}
	return false;
}

bool diagonalUp_L2R_Check(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i, initial_j;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varD3++];
		if (allWords[varD3] == ',' || allWords[varD3] == '.')
		{
			wordSize = i + 1;
			varD3++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 0;
	for (int i = 14; i >= 0; i--)
	{
		for (int j = 0; j < 15; j++)
		{
			k = 0;
			count = 0;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk) {
					if (word[k] == grid[i][j])
					{
						i--, j++, count++, k++;
					}
					else if (word[k] != grid[i][j] || (i == 0 && j == 14))
						i = initial_i, j = initial_j, fullChk = false;
				}
				if (fullChk)
				{
					cd3++;
					for (int p = initial_i, q = initial_j; p > i && q < j; p--, q++)
						row[p]++, col[q]++, clrGrid[p][q]++;
				}
			}
			if (count == wordSize)
				return true;
		}
	}
	return false;
}

bool diagonalDown_R2L_Check(char grid[15][15], char allWords[500]) {
	char word[15];
	int wordSize;
	int initial_i, initial_j;

	for (int i = 0; true; i++)
	{
		word[i] = allWords[varD4++];
		if (allWords[varD4] == ',' || allWords[varD4] == '.')
		{
			wordSize = i + 1;
			varD4++;
			word[i + 1] = '-';
			break;
		}
	}
	int k = 0;
	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 14; j >= 0; j--)
		{
			k = 0;
			count = 0;
			if (word[k] == grid[i][j])
			{
				initial_i = i;
				initial_j = j;
				bool fullChk = true;
				while (k < wordSize && fullChk) {
					if (word[k] == grid[i][j])
					{
						i++, j--, count++, k++;
					}
					else if (word[k] != grid[i][j] || (i == 14 && j == 0))
						i = initial_i, j = initial_j, fullChk = false;
				}
				if (fullChk)
				{
					cd4++;
					for (int p = initial_i, q = initial_j; p < i && q > j; p++, q--)
						row[p]++, col[q]++, clrGrid[p][q]++;
				}
			}
			if (count == wordSize)
				return true;
		}
	}
	return false;
}