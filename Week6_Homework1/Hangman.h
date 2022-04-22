#include <iostream>
#include <Windows.h>	// �̰� ������ ���� ���ϸ� no Target Architecture�� �߻��Ѵ�.
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>	//kbhit(),getch() �� ����ϱ� ���� ���
#include <vector>
#include <fstream>

using namespace std;
class Hangman {

public:
	void gotoxy(int x, int y);	// �ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ�
	int GetkeyDown();	// Ű�� �Է��� �������� ó���� �Լ�
	void DrawStart(int life, int score, vector<string>& pastWord, const char* name, string line[65]);	// ���� ������ ȭ���� �׸���. &�� pastWord�� ���� �ּҸ� �Ű������� �ϱ����� �߰�
	void SetDiction(vector<string>& strArr);	// �ܾ���� ��� �ִ� �Լ�
	void StartGame();	// ���ӽ��� ���
	void load(string line[65], const char* name);
};
static int k = 0;

void Hangman::load(string line[65], const char* name = "HangmanProgress.txt") {
	ifstream fs(name);
	if (fs) {
		getline(fs, line[0]);
		for (k = 1; k < 65; k++) {
			for (int i = 0; i < 8; i++) {
				getline(fs, line[k]);
				gotoxy(5, 14 + i);
				cout << line[k] << endl;
				k += 8;
			}
		}
	}
}
void Hangman::gotoxy(int x, int y) {

	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int Hangman::GetkeyDown() {
	if (_kbhit() != 0) {	// �Է��� ���´ٸ�
		return _getch();	// �Է��� ���� ���ۿ� �Է��Ѱ��� �����Ѵ�.
	}
}

void Hangman::DrawStart(int life, int score, vector<string>& pastWord, const char* name, string line[65]) {
	system("cls");

	//gotoxy(5, 1);
	//cout << "life = " << life;
	//gotoxy(5, 2);
	//cout << "score = " << score;
	//gotoxy(5, 8);
	//cout << "past = ";
	//for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {	// vector<string> Ÿ���� intŸ������ ��ȯ
	//	cout << pastWord[i] << " ";
	//}
	//gotoxy(5, 12);
	//cout << "input = ";




}

void Hangman::SetDiction(vector<string>& strArr) {
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };	//���� �ܾ�
	for (int i = 0; i < 4; i++) {
		string tmp = str[i];
		strArr.push_back(tmp);
	}
}


void Hangman::StartGame() {
	int score = 0;
	vector<string> pastWord;	// �Է��� ���ܾ� ����
	vector<string> strArr;		// ���� �ܾ�
	SetDiction(strArr);	// �Ű����� ����� ���� �Ʊ� &�� �����

	while (true) {
		int num = 0;
		srand((unsigned int)time(NULL));	// ���� �Լ� ����� ���� �õ尪 ����
		num = rand() % static_cast<int>(strArr.size());	// �ܾ �����ϰ� ����

		string str;	//_ _ _ �� ǥ���� ����
		string str_result = strArr[num];	// �ܾ �´��� ����Ȯ�ο����� ����
		int result_len = static_cast<int>(str_result.length());	// �����ϰ� ���� �ܾ��� ���̸� Ȯ��
		string line[65];	// HangmanProgress.txt �� ������ 65���̹Ƿ� �迭 ����
		ifstream fs("HangmanProgress.txt");	// ������ �д´�.
		getline(fs, line[0]);	// ù��° �� �ּ�ó��
		for (int i = 0; i < result_len; i++) {
			str += "_";	// ���� ���̸�ŭ _�� ����
		}
		int life = 7;	// ������� 8���� ����!
		DrawStart(life, score, pastWord, "HangmanProgress.txt", line);
		while (true) {	// �Ѱ��� �ܾ ���ߴ� ����
				// ���·�,����,���ܾ� ǥ��
			gotoxy(5, 8);
			cout << "past = ";
			for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {	// vector<string> Ÿ���� intŸ������ ��ȯ
				cout << pastWord[i] << " ";
			}
			gotoxy(5, 1);
			cout << "life = " << life;
			gotoxy(5, 2);
			cout << "score = " << score;
			gotoxy(5, 12);
			cout << "input = ";

			if (fs) {	// ���࿡ file�� �ִٸ� true
				for (k = 1; k < 65; k++) {	// ������ ���� �д´�.
					for (int i = 0; i < 8; i++) {	// 8�پ� ����ϱ� ���ؼ�
						getline(fs, line[k + i]);	// 8�� �̾ �������� ���� ���
						gotoxy(5, 14 + i);	// ����� �̻ڰ� �ϱ� ���� ���
						cout << line[k + i] << endl;	// ������ ���϶����� ���
						k += 8;	// 8�پ� ������� ���� ���
					}
				}
			}

			// ������ ����
			gotoxy(5, 5);
			for (int i = 0; i < result_len; i++) {
				cout << str[i] << " ";	// _ _ _ �� ǥ��
			}
			cout << endl;

			// �Է�
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;	// �Է¹ޱ�
			pastWord.push_back(strInput);	// �Է��� �ܾ� ǥ��

			if (strInput.length() == 1) {
				for (int i = 0; i < result_len; i++) {
					if (str_result[i] == strInput[0]) {
						str[i] = strInput[0];
					}
				}
			}
			else if (strInput.length() > 1) {
				if (str_result == strInput) {
					score += 1;
					pastWord.clear();	// ������ ��� ���Ҹ� ����
					break;	// �Ѱ� �ܾ ���߰� ����1�� �׵�
				}
			}
			life -= 1;	// �Է��Ҷ� ���� -1 �� ����



			if (life < 0) {
				score -= 1;
				if (score < 0) {
					score = 0;
					pastWord.clear();
					break;
				}
			}

		}
	}
}
