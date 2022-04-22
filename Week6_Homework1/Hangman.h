#include <iostream>
#include <Windows.h>	// 이걸 맨위에 선언 안하면 no Target Architecture가 발생한다.
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>	//kbhit(),getch() 을 사용하기 위해 사용
#include <vector>
#include <fstream>

using namespace std;
class Hangman {

public:
	void gotoxy(int x, int y);	// 콘솔 내부의 특정 위치로 커서를 이동시키는 함수
	int GetkeyDown();	// 키가 입력이 들어왔을때 처리할 함수
	void DrawStart(int life, int score, vector<string>& pastWord, const char* name, string line[65]);	// 게임 시작후 화면을 그린다. &는 pastWord의 시작 주소를 매개변수로 하기위해 추가
	void SetDiction(vector<string>& strArr);	// 단어들이 들어 있는 함수
	void StartGame();	// 게임실행 기능
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
	if (_kbhit() != 0) {	// 입력이 들어온다면
		return _getch();	// 입력한 값을 버퍼에 입력한값을 리턴한다.
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
	//for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {	// vector<string> 타입을 int타입으로 변환
	//	cout << pastWord[i] << " ";
	//}
	//gotoxy(5, 12);
	//cout << "input = ";




}

void Hangman::SetDiction(vector<string>& strArr) {
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };	//샘플 단어
	for (int i = 0; i < 4; i++) {
		string tmp = str[i];
		strArr.push_back(tmp);
	}
}


void Hangman::StartGame() {
	int score = 0;
	vector<string> pastWord;	// 입력한 영단어 저장
	vector<string> strArr;		// 맞출 단어
	SetDiction(strArr);	// 매개변수 사용을 위해 아까 &을 사용함

	while (true) {
		int num = 0;
		srand((unsigned int)time(NULL));	// 랜덤 함수 사용을 위한 시드값 생성
		num = rand() % static_cast<int>(strArr.size());	// 단어를 랜덤하게 설정

		string str;	//_ _ _ 로 표현할 변수
		string str_result = strArr[num];	// 단어가 맞는지 정답확인용으로 저장
		int result_len = static_cast<int>(str_result.length());	// 랜덤하게 들어온 단어의 길이를 확인
		string line[65];	// HangmanProgress.txt 의 파일이 65줄이므로 배열 생성
		ifstream fs("HangmanProgress.txt");	// 파일을 읽는다.
		getline(fs, line[0]);	// 첫번째 줄 주석처리
		for (int i = 0; i < result_len; i++) {
			str += "_";	// 정답 길이만큼 _를 만듬
		}
		int life = 7;	// 생명력은 8으로 고정!
		DrawStart(life, score, pastWord, "HangmanProgress.txt", line);
		while (true) {	// 한개의 단어를 맞추는 구문
				// 생력력,점수,사용단어 표기
			gotoxy(5, 8);
			cout << "past = ";
			for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {	// vector<string> 타입을 int타입으로 변환
				cout << pastWord[i] << " ";
			}
			gotoxy(5, 1);
			cout << "life = " << life;
			gotoxy(5, 2);
			cout << "score = " << score;
			gotoxy(5, 12);
			cout << "input = ";

			if (fs) {	// 만약에 file이 있다면 true
				for (k = 1; k < 65; k++) {	// 파일을 전부 읽는다.
					for (int i = 0; i < 8; i++) {	// 8줄씩 출력하기 위해서
						getline(fs, line[k + i]);	// 8줄 이어서 가져오기 위해 사용
						gotoxy(5, 14 + i);	// 출력을 이쁘게 하기 위해 사용
						cout << line[k + i] << endl;	// 가져온 파일라인을 출력
						k += 8;	// 8줄씩 띄워쓰기 위해 사용
					}
				}
			}

			// 문제를 만듬
			gotoxy(5, 5);
			for (int i = 0; i < result_len; i++) {
				cout << str[i] << " ";	// _ _ _ 로 표시
			}
			cout << endl;

			// 입력
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;	// 입력받기
			pastWord.push_back(strInput);	// 입력한 단어 표시

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
					pastWord.clear();	// 백터의 모든 원소를 제거
					break;	// 한개 단어를 맞추고 점수1점 휙득
				}
			}
			life -= 1;	// 입력할때 마다 -1 씩 감소



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
