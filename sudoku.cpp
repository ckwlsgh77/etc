#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

#define SIZE 10

int real_answer[SIZE][SIZE] = { 0, };
int sudoku_map[SIZE][SIZE] = { 0, };
int input_answer[SIZE][SIZE] = { 0, };
int undo_x[5];
int undo_y[5];
int undo_ans[5];
int undo_count = 0;
int numberOfundo = 1;

bool check_row(int map[SIZE][SIZE],int x, int y) {
	for (int i = 1; i < 10; i++) {
		if (i != y && map[x][y] == map[x][i])
			return false;
	}
	return true;
}
bool check_col(int map[SIZE][SIZE],int x, int y) {
	for (int i = 1; i < 10; i++) {
		if (i != x && map[x][y] == map[i][y])
			return false;
	}
	return true;
}
bool check_square(int map[SIZE][SIZE],int x, int y) {
	int start_x;
	int start_y;

	if (x > 6)
		start_x = 7;
	else if (x > 3)
		start_x= 4;
	else
		start_x = 1;

	if (y > 6)
		start_y = 7;
	else if (y > 3)
		start_y = 4;
	else
		start_y = 1;

	for (int i = start_x; i < start_x + 3; i++) {
		for (int j = start_y; j < start_y + 3; j++) {
			if (i != x && j != y && map[x][y] == map[i][j])
				return false;
		}
	}
	return true;
}
bool make_answer(int x, int y) {
	if (real_answer[x][y] == 0) {
		bool lock = true;
		bool lock_count[9] = { 0, };

		while (lock) {
			int temp = rand() % 9 + 1;

			for (int i = 0; i < 9; i++) {
				if (lock_count[i] == 0)
					break;
				if (i == 8) {
					real_answer[x][y] = 0;
					return false;
				}
			}

			if (lock_count[temp - 1] == 0) {
				real_answer[x][y] = temp;

				if (check_col(real_answer, x, y) && check_row(real_answer, x, y) && check_square(real_answer, x, y)) {
					if (y < 9) {
						if (make_answer(x, y + 1))
							lock = false;
					}
					else if (y >= 9) {

						if (x + 1 > 9) {
							return true;
						}

						if (make_answer(x + 1, 1))
							lock = false;
					}
					lock_count[temp - 1] = true;
				}
				else {
					lock_count[temp - 1] = true;
				}

				
			}
			else
				continue;
		}
		return true;
	}
	else
		return false;
}

void make_map() {

	int random;
	int count = 0;
	
	for (int i = 0; i < 5; i++) {
		undo_x[i] = 0;
		undo_y[i] = 0;
		undo_ans[i] = 0;
	}
	
	int x;
	int y;
	int map[10][10] = { 0, };
	srand(time(NULL));
	make_answer(1, 1);


	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			sudoku_map[i][j] = real_answer[i][j];
		}
	}

	while (count <= 42) {
		int x = rand() % 9 + 1;
		int y = rand() % 9 + 1;

		if (sudoku_map[x][y] != 0) {
			sudoku_map[x][y] = 0;
			count++;
		}
		else
			continue;
	}

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			input_answer[i][j] = sudoku_map[i][j];
		}
	}


}


void print_sudoku() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(100);
	system("cls");
	Sleep(100);
	printf("\n    1 2 3   4 5 6   7 8 9 \n");
	printf("  ┏━━━━━━━┳━━━━━━━┳━━━━━━━┓\n");
	for (int i = 1; i < 10; i++) {
		printf("%d ", i);
		for (int j = 1; j < 10; j++) {

			if (j % 3 == 1) {
				printf("┃ ");
			}

			if (input_answer[i][j] == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf(". ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if(sudoku_map[i][j] == 0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("%d ", input_answer[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
				printf("%d ", input_answer[i][j]);
		}
		printf("┃\n");

		if (i % 3 == 0 && i !=9 ) {
			printf("  ┣━━━━━━━╋━━━━━━━╋━━━━━━━┨\n");
		}
	}
	printf("  ┗━━━━━━━┻━━━━━━━┻━━━━━━━┛\n\n");
}
bool input_number(int x, int y, int input_ans) {

	if (sudoku_map[x][y] == 0) {

		undo_x[undo_count % 5] = x;
		undo_y[undo_count % 5] = y;
		undo_ans[undo_count % 5] = input_answer[x][y];

		input_answer[x][y] = input_ans;

		undo_count++;
		return true;
	}
	else
		return false;

	return false;
}

void search_error() {
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			if (sudoku_map[i][j] == 0 && input_answer[i][j] != 0) {
				if (!(check_col(input_answer, i, j) && check_row(input_answer, i, j) && check_square(input_answer, i, j))) {
					printf("(%d,%d)의 셀의 값이 잘못되었습니다.\n", i, j);
					return;
				}
			}
		}
	}
	printf("내가 보기엔 얼추 다 맞는거 같아ㅎㅎ\n");
}

void undo() {

	if (numberOfundo >= 6) {
		printf("나는 5개까지 밖에 기억을 못해서 되돌려 줄수 없어요.\n");
	}
	else if(undo_count - numberOfundo < 0) {
		printf("그전에는 입력이 없었는데요?\n");
	}
	else {
		input_answer[undo_x[(undo_count - numberOfundo) % 5]][undo_y[(undo_count - numberOfundo) % 5]] =undo_ans[(undo_count - numberOfundo) % 5];
		numberOfundo++;
	}
}

void clearInputBuffer()
{
	
	while (getchar() != '\n');
}

bool check_ans(void) {

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			if (input_answer[i][j] != real_answer[i][j]) {
				return false;
			}
		}
	}
	return true;

}

void game() {
	
	bool first = true;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("\n  도움말은 h를 눌러주세요 :) By JINHO\n");
	Sleep(2000);
	while (1) {
		
		char x;
		if (first) {
			make_map();
			first = false;
			print_sudoku();
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("입력 > ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		scanf("%c", &x);

		switch (x) {
		case 'A': 
			for (int i = 1; i < 10; i++) {
				for (int j = 1; j < 10; j++) {
					input_answer[i][j] = sudoku_map[i][j];
				}
			}
			print_sudoku();
			numberOfundo = 1;
			undo_count = 0;
			for (int i = 0; i < 5; i++) {
				undo_x[i] = 0;
				undo_y[i] = 0;
				undo_ans[i] = 0;
			}
			break;
		case 'U':
			undo();
			print_sudoku();
			break;
		case 'N':
			first = 1;
			numberOfundo = 1;
			break;
		case 'V': search_error();
			//print_sudoku();
			break;
		case 'q':
			printf("게임을 종료합니다.\n");
			return;
			break;
		case 'O':
			if (check_ans()) {
				printf("정답입니다.\n");
				printf("N : 새게임 하기\n");
				printf("q : 끝내기\n");
			}
			else
				printf("정답이아닙니다 ㅋ\n");
			
			break;
		case 'h':
			printf("\n행 열 값 으로 입력합니다. ex) 1 2 3 --> 1번째행 2번째열에 3을쓰기\n");
			printf("--그외 명령어--\n");
			printf("A : 처음부터 다시\n");
			printf("V : 틀린곳 찾기\n"); 
			printf("U : 입력 되돌리기\n");
			printf("N : 새게임 하기\n");
			printf("O : 채점하기\n");
			printf("q : 끝내기\n\n"); 
			break;
		default :
			if (49 <= x && x <= 57) {
				char y;
				char input;
				int input_x;
				int input_y;
				int input_ans;
				scanf(" %c", &y);
				scanf(" %c", &input);

				input_ans = input - 48;

				if (input_number(x - 48, y - 48, input_ans)) {
					print_sudoku();
				}
				else
					printf("그곳에는 입력 할 수 없습니다.\n");
				numberOfundo = 1;
			}
			else
				printf("잘못된 입력 입니다.\n");
			break;
		}
		clearInputBuffer();

	}

}

int main()
{
	game();


    return 0;
}


