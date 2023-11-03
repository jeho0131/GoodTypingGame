#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

//Ʋ�� ���ĺ� ���� ���� 
int num[26]; 

//Ʋ�� ���ĺ� ������ ���� �迭 
char ap[54] = {  'a','b','c','d','e','f','g','h',
				'i','j','k','l','m','n','o','p','q',
				'r','s','t','u','v','w','x','y','z',
				'A','B','C','D','E','F','G','H',
				'I','J','K','L','M','N','O','P','Q',
				'R','S','T','U','V','W','X','Y','Z'  };	

//��ŷ ������ ���� �迭
//�̸� 
char rankn[3][50];
//�ɸ��ð� 
int ranks[3];
//Ʋ�� Ƚ�� 
int rankm[3];
		
// ������ ������ ���� 
void cc(int colorNum) {
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), colorNum);
}

//���� �Է� ��ġ ���� 
void gotoxy(int x, int y) {
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
			
//Ʋ�� ���ĺ� Ȯ�� 
void wc(char word) {
	for(int i = 0; i < 26; i++) {
		if(word == ap[i] || word == ap[i+26]) {
			num[i] += 1;
		}
	}
}

//���� ���� 
void rankChange(int num) {
	strcpy(rankn[num+1], rankn[num]);
	ranks[num+1] = ranks[num];
	rankm[num+1] = rankm[num];
}

//��ŷ ��� 
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
	//���� ����� ���� ���� 
	FILE * fp;
	FILE * lankr;	
	FILE * lankw;
	fp = fopen("typing.txt", "r");
	lankr = fopen("lank.txt", "r");
	
	//������ 
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
	
	//��ŷ�� �о�� ���� 
	fscanf(lankr,"%s %d %d", &rankn[0], &ranks[0], &rankm[0]);
	fscanf(lankr,"%s %d %d", &rankn[1], &ranks[1], &rankm[1]);
	fscanf(lankr,"%s %d %d", &rankn[2], &ranks[2], &rankm[2]);

    //��ŷ�� �ƹ��͵� ������ ��ŷ�� ���� ��Ŀ ����  
	if(ranks[2] == 0 && rankm[2] == 0) {
		strcpy(rankn[2], "TypingGame");
		ranks[2] = 200;
		rankm[2] = 120;
	}
	
	//�ð� ���� ���� 
	time_t cT;
	struct tm * lT;
	cT = time(NULL);
	lT = localtime(&cT);
	
	int nt = lT -> tm_sec;
	int before = lT -> tm_sec;
	
	//�ܼ�â�� ������� â�� �̸� ���� 
	//system("mode con: cols=100 lines=70");
	system("title=typing Game");	
	
	cc(10); //�ʷϻ����� ���� ��ȯ 
	printf("\n[Ÿ���� ���� ����!] (�� 10����)\n\n");
	y += 3;
	 
	while(1) {
		//���� ���� 
		cc(14);
		printf("%d\n", end);
		y += 1;
		
		cc(15);	
		for(int j = 0; ; j++) {
			fseek(fp,0,SEEK_CUR);
			t = fgetc(fp);
			putchar(t);
			quiz[j] = t;
			
			//������ ��  			
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
		
		//������ ���� ���� ����. 
		for(int k = 0; ; k++) {
			a = getch();
			x += 1;
			b = a;
			cT = time(NULL);
			lT = localtime(&cT);
			after = lT -> tm_sec;
			
			//Ÿ�̸� ����  
			if(before > after) {
				clock += 59 - before + after + 1;
				before = lT -> tm_sec;
			}
			else if(before < after) {
				clock += after - before;
				before = lT -> tm_sec;
			}
			
			//�д� Ÿ��  
			if(nt == lT -> tm_sec) {
				if (tp < wn){
					tp = wn;
					wn = 0;
				}
			}
			
			//����Ű�� �������� ���� ������ �Ѿ��. 
			if(b == 13) {
				printf("\n\n");
				y += 2;
				break;
			}
			
			//�۾��� ����� �ٽþ���. 
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
			
			//�������� ���� �� ���� ���� �� ���� ������ �Ѿ��. 
			else if(qn < k) {
				x -= 1;
				printf("\n\n");
				y += 2;
				break;
			}
			
			//���� ���Ͱ� ������ �ٸ��� ���� ������ ���������� �ٲ��. 
			if(quiz[k] != a) {
				cc(12);
				printf("%c\a", a);
				cc(7);
				wc(a);
				w += 1;
				wn += 1;
				kb += 1;
			}
			
			//���� �Է��� �۾��� ������. 
			else {
				printf("%c", a);
				wn += 1;
				kb += 1;
			}
		}
		x = 0;
		//������ ���̻� ������ ������ ���� �ݺ��� ������.
		if(t == EOF) break;
		end -= 1;
	}
	
	//��ŷ�� �д� �ſ��� ���� �ɷ� �ٲ�  
	fclose(lankr);
	lankw = fopen("lank.txt", "w");
	
	//Ʋ�� Ƚ���� ���� Ƚ���� �˷��ش�. 
	printf("\nƲ�� Ƚ�� : %d, ���� Ƚ�� : %d\n", w, e);
  
  	//� �ܾ ���� ���� Ʋ�ȴ��� �� �� �ִ�. 
	printf("\n[����]\t[Ƚ��]\t[����]\t[Ƚ��]\n"); 
	for(int i = 0; i < 26; i++) {
		if(n == 2) {
			printf("\n");
			n = 0;
		}
		printf(" %c\t %d\t", ap[i], num[i]);
		n += 1;
	}
	
	//1�� �̳��� Ÿ���� �˷��ش�. 
	if(clock < 60) {
		printf("\n\nŸ�� : %d", wn);
	}
	//�д� Ÿ���� �˷��ش�. 
	else {
		printf("\n\nŸ�� : %d/��", tp);
	}
	
	//ġ�µ� �ɸ� �ð��� �˷��ش�. 
	printf("\t�ð� : %d��\n", clock);
	
	//�÷��̾��� �̸��� �Է� ����  
	printf("\n�ڽ��� �г����� �Է��Ͻÿ�.  ");
	scanf("%s", &player);
	
	//��ŷ�� �÷��̾��� ������ ���� �ٲٰ� ȭ�鿡 ������  
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
	
	//��ŷ�� ����  
	fprintf(lankw,"%s %d %d\n%s %d %d\n%s %d %d", 
			rankn[0], ranks[0], rankm[0], 
			rankn[1], ranks[1], rankm[1], 
			rankn[2], ranks[2], rankm[2]
			);

	fclose(fp);
	
	return 0;
}
