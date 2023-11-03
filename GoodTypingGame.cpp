#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

//틀린 알파벳 개수 저장 
int num[26]; 

//틀린 알파벳 구별을 위한 배열 
char ap[54] = {  'a','b','c','d','e','f','g','h',
				'i','j','k','l','m','n','o','p','q',
				'r','s','t','u','v','w','x','y','z',
				'A','B','C','D','E','F','G','H',
				'I','J','K','L','M','N','O','P','Q',
				'R','S','T','U','V','W','X','Y','Z'  };	

//랭킹 저장을 위한 배열
//이름 
char rankn[3][50];
//걸린시간 
int ranks[3];
//틀린 횟수 
int rankm[3];
		
// 글자의 색깔을 변경 
void cc(int colorNum) {
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), colorNum);
}

//글자 입력 위치 변경 
void gotoxy(int x, int y) {
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
			
//틀린 알파벳 확인 
void wc(char word) {
	for(int i = 0; i < 26; i++) {
		if(word == ap[i] || word == ap[i+26]) {
			num[i] += 1;
		}
	}
}

//순위 변경 
void rankChange(int num) {
	strcpy(rankn[num+1], rankn[num]);
	ranks[num+1] = ranks[num];
	rankm[num+1] = rankm[num];
}

//랭킹 출력 
void ranking() {
	cc(14);
	printf("\n\n\t\t      [RANKING]\n\n");
	cc(15);
	printf("\n\tname\t\tspeed\t\tmiss\n\n\n");
	printf("    [1]\t%s\t\t%d\t\t%d\n\n", rankn[0], ranks[0], rankm[0]);
	printf("    [2]\t%s\t\t%d\t\t%d\n\n", rankn[1], ranks[1], rankm[1]);
	printf("    [3]\t%s\t\t%d\t\t%d\n\n", rankn[2], ranks[2], rankm[2]);
}

int main() {
	//파일 입출력 변수 정의 
	FILE * fp;
	FILE * lankr;	
	FILE * lankw;
	fp = fopen("typing.txt", "r");
	lankr = fopen("lank.txt", "r");
	
	//변수들 
	char t;
	char quiz[500];
	char a;
	int b = 0;
	int x = 0;
	int y = 0;
	int qn = 0;
	int e = 0;
	int w = 0; 
	int wn = 0;
	int n = 0;
	int tp = 0;
	int clock = 0;
	int after = 0;
	int end = 10;
	int kb = 0;
	char player[50];
	
	//랭킹을 읽어와 저장 
	fscanf(lankr,"%s %d %d", &rankn[0], &ranks[0], &rankm[0]);
	fscanf(lankr,"%s %d %d", &rankn[1], &ranks[1], &rankm[1]);
	fscanf(lankr,"%s %d %d", &rankn[2], &ranks[2], &rankm[2]);

    //랭킹에 아무것도 없을시 랭킹에 인조 랭커 생성  
	if(ranks[2] == 0 && rankm[2] == 0) {
		strcpy(rankn[2], "TypingGame");
		ranks[2] = 200;
		rankm[2] = 120;
	}
	
	//시간 관련 변수 
	time_t cT;
	struct tm * lT;
	cT = time(NULL);
	lT = localtime(&cT);
	
	int nt = lT -> tm_sec;
	int before = lT -> tm_sec;
	
	//콘솔창의 사이즈와 창의 이름 정의 
	//system("mode con: cols=100 lines=70");
	system("title=typing Game");	
	
	cc(10); //초록색으로 글자 변환 
	printf("\n[타이핑 게임 시작!] (총 10문제)\n\n");
	y += 3;
	 
	while(1) {
		//문제 생성 
		cc(14);
		printf("%d\n", end);
		y += 1;
		
		cc(15);	
		for(int j = 0; ; j++) {
			fseek(fp,0,SEEK_CUR);
			t = fgetc(fp);
			putchar(t);
			quiz[j] = t;
			
			//문장의 끝  			
			if(t == '.' || t == '?' || t == '!') {
				fseek(fp,0,SEEK_CUR);
				t = fgetc(fp);
				printf("\n");
				qn = j;
				y += 1;
				cc(7);
				break;
			}
		}
		
		//문제에 따라서 답을 쓴다. 
		for(int k = 0; ; k++) {
			a = getch();
			x += 1;
			b = a;
			cT = time(NULL);
			lT = localtime(&cT);
			after = lT -> tm_sec;
			
			//타이머 역할  
			if(before > after) {
				clock += 59 - before + after + 1;
				before = lT -> tm_sec;
			}
			else if(before < after) {
				clock += after - before;
				before = lT -> tm_sec;
			}
			
			//분당 타수  
			if(nt == lT -> tm_sec) {
				if (tp < wn){
					tp = wn;
					wn = 0;
				}
			}
			
			//엔터키를 눌렀을때 다음 문제로 넘어간다. 
			if(b == 13) {
				printf("\n\n");
				y += 2;
				break;
			}
			
			//글씨를 지우고 다시쓴다. 
			else if(b == 8 && k != 0) {
				k = k - 2;
				x = x - 2;
				gotoxy(x, y);
				printf(" "); 
				e += 1;
				w -= 1;
				wn -= 2;
				kb -= 2;
			}
			
			//문제보다 글을 더 많이 썼을 때 다음 문제로 넘어간다. 
			else if(qn < k) {
				x -= 1;
				printf("\n\n");
				y += 2;
				break;
			}
			
			//글을 쓴것과 문제가 다를시 내가 쓴글이 빨간색으로 바뀐다. 
			if(quiz[k] != a) {
				cc(12);
				printf("%c\a", a);
				cc(7);
				wc(a);
				w += 1;
				wn += 1;
				kb += 1;
			}
			
			//내가 입력한 글씨가 써진다. 
			else {
				printf("%c", a);
				wn += 1;
				kb += 1;
			}
		}
		x = 0;
		//파일의 더이상 문장이 없을시 무한 반복을 나간다.
		if(t == EOF) break;
		end -= 1;
	}
	
	//랭킹을 읽는 거에서 쓰는 걸로 바꿈  
	fclose(lankr);
	lankw = fopen("lank.txt", "w");
	
	//틀린 횟수와 지운 횟수를 알려준다. 
	printf("\n틀린 횟수 : %d, 지운 횟수 : %d\n", w, e);
  
  	//어떤 단어가 제일 많이 틀렸는지 알 수 있다. 
	printf("\n[종류]\t[횟수]\t[종류]\t[횟수]\n"); 
	for(int i = 0; i < 26; i++) {
		if(n == 2) {
			printf("\n");
			n = 0;
		}
		printf(" %c\t %d\t", ap[i], num[i]);
		n += 1;
	}
	
	//1분 이내에 타수를 알려준다. 
	if(clock < 60) {
		printf("\n\n타자 : %d", wn);
	}
	//분당 타수를 알려준다. 
	else {
		printf("\n\n타자 : %d/분", tp);
	}
	
	//치는데 걸린 시간을 알려준다. 
	printf("\t시간 : %d초\n", clock);
	
	//플레이어의 이름을 입력 받음  
	printf("\n자신의 닉네임을 입력하시오.  ");
	scanf("%s", &player);
	
	//랭킹을 플레이어의 성적의 따라 바꾸고 화면에 보여줌  
	if(kb >= 390 && ranks[2] >= clock && rankm[2] >= w) {
		if(ranks[0] > clock) {
			rankChange(1);
			rankChange(0);
			strcpy(rankn[0], player);
			ranks[0] = clock;
			rankm[0] = w;
			ranking();
		}
		
		else if(ranks[1] > clock) {
			rankChange(1);
			strcpy(rankn[1], player);
			ranks[1] = clock;
			rankm[1] = w;
			ranking();
		}
		
		else {
			strcpy(rankn[2], player);
			ranks[2] = clock;
			rankm[2] = w;
			ranking();
		}
	}
	else {
		ranking();
		cc(4);
		printf("\n\t\t['%s' you not ranker]\n\n", player);
		cc(15);
	}
	
	//랭킹을 저장  
	fprintf(lankw,"%s %d %d\n%s %d %d\n%s %d %d", 
			rankn[0], ranks[0], rankm[0], 
			rankn[1], ranks[1], rankm[1], 
			rankn[2], ranks[2], rankm[2]
			);

	fclose(fp);
	
	return 0;
}
