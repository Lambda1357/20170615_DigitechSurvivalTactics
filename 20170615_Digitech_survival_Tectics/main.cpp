#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>

//낮의 활동갯수 정의
#define DAYTIME_ACTCOUNT 3

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursorOff(void)
{
	CONSOLE_CURSOR_INFO Information;
	Information.dwSize = 1;
	Information.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void bfclear()
{
	while (getchar() != '\n');
}

void cursorOn(void)
{
	CONSOLE_CURSOR_INFO Information;

	Information.dwSize = 20;
	Information.bVisible = TRUE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

char* roomtyper(int typecode)
{
	switch (typecode)
	{
	case 0:
		return "없음";
		break;
	case 1:
		return "초소";
		break;
	case 2:
		return "식당";
		break;
	case 3:
		return "탐사기지";
	case 4:
		return "창고";

	}
}

struct shelt_room
{
	//0은 미건설 1은 방어시설, 2는 인구시설, 3은 탐색시설, 4는 저장고
	short roomtype = 0;
	short roomlv;
	int aply_bonus;
};
struct item
{
	char name[21];
	int cur_cnt;
	int stackmax;
};
struct shelter
{
	shelt_room roomspace[20];
	int def, srch;
	int maxlife;
	int curlife;
	item inven[20];
};
struct leader
{
	char username[21];

	shelter* base;
};

//건물 업그레이드 미구현, 저장량 상승효과 없음.
void buildroom(shelter* m_base)
{
	{
		/*버그때문에 일단 봉인
		for (int i = 0; i < 5; i++)
			printf("%d번: %s\t%d번: %s\n%d번: %s\n%d번: %s", i + 1, roomtyper(m_base->roomspace[i].roomtype),
			i+5,roomtyper(m_base->roomspace[i+4].roomtype),i+10,roomtyper(m_base->roomspace[i+9].roomtype));*/
		int roomnum;
		char temp;
		printf("경로당 내부는 생각보다 넓다. 약간의 자원이 있다면 손볼 수 있을 것 같다...\n");
		while (1)
		{
			puts("-----------------------------------------");
			printf("1. 벽을 보강하고 초소를 만들자. (방어시설)\n2. 텃밭과 간이 침대를 만들어 생활공간을 만들자 (인구시설)\n3. 망루를 만들어 근처를 둘러보자 (탐색시설)\n0. 건설을 종료한다.\n어떤 시설을 제작해볼까? (숫자 입력)>>");
			bfclear();
			temp = getchar();
			switch (temp)
			{
			case '1':
				while (1)
				{
					printf("방어시설을 몇 번 공간에 만드시겠습니까?");
					bfclear();
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							bfclear();
							char temp = getchar();
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "나무")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 1,1,5 };
									printf("건설을 성공적으로 마쳤습니다.\n");
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("방어시설 건설을 그만두시겠습니까? (그만두려면 y 입력)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("계속 진행합니다.\n");
				}
				break;
			case '2':
				while (1)
				{
					printf("식당을 몇 번 공간에 만드시겠습니까?");
					bfclear();
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							bfclear();
							char temp = getchar();
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "나무")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 2,1,5 };
									printf("건설을 성공적으로 마쳤습니다.\n");
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("식당 건설을 그만두시겠습니까? (그만두려면 y 입력)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("계속 진행합니다.\n");
				}
				break;
			case '3':
				while (1)
				{
					printf("탐색거점을 몇 번 공간에 만드시겠습니까?");
					bfclear();
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "나무")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 3,1,5 };
									printf("건설을 성공적으로 마쳤습니다.\n");
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("탐사시설 건설을 그만두시겠습니까? (그만두려면 y 입력)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("계속 진행합니다.\n");
				}
				break;
			case '0':
				break;
			default:
				printf("유효한 값을 입력하세요\n");
			}
			printf("건설작업을 종료할까요? (종료한다면 y)>>");
			bfclear();
			char acter = getchar();
			if (acter == 'Y' || acter == 'y') break;
			else printf("건설작업을 다시 시작합니다.\n\n");
		}
	}
}

int finditem(shelter* base)
{
	int srchbody;
	printf("1.나무 찾기,2.돌 찾기");
	bfclear();
	char temp = getchar();
	switch (temp)
	{
	case '1':
		if (base->curlife > 0)
		{
			int i;
			while (1)
			{
				printf("파견할 인원 수는?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; strcmp(base->inven[i].name, "나무") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("나무를 %d개 찾았다!", rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t현재 갯수 %d개", base->inven[i].cur_cnt);
				if (rslt != 0) printf("공간이 모자라 %d개의 자원이 버려졌습니다.", rslt);
				printf("\n");
				return 1;
			}
			else { printf("에러:아이템의 저장위치를 찾을 수 없었습니다.\n"); return 0; }
		}
		else { printf("파견보낼 사람이 없습니다.\n"); return 0; }
		break;
	case '2':
		if (base->curlife > 0)
		{
			int i;
			while (1)
			{
				printf("파견할 인원 수는?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; strcmp(base->inven[i].name, "돌") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("돌을 %d개 찾았다!", rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t현재 갯수 %d개", base->inven[i].cur_cnt);
				if (rslt != 0) printf("공간이 모자라 %d개의 자원이 버려졌습니다.", rslt);
				printf("\n");
				return 1;
			}
			else { printf("에러:아이템의 저장위치를 찾을 수 없었습니다.\n"); return 0; }
		}
		else { printf("파견보낼 사람이 없습니다.\n"); return 0; }
		break;
	default:
		printf("입력에서 오류가 있었습니다.\n");
		return 0;
		break;
	}
}

//
void rescuetribe(shelter* base)
{
	int srchbody, rqpoint = 0;
	if (base->curlife > 0)
	{
		int i;
		while (1)
		{
			printf("파견할 인원 수는?");
			bfclear();
			scanf("%d", &srchbody);
			if ((srchbody < base->curlife) && (srchbody > 0)) break;
			else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
		}
		int restemp;
		while (1)
		{
			printf("자원을 장비하여 보내면 사람을 더 구할 수 있을지도 모릅니다.\n1. 나무\n2.돌\n0. 장비하지 않는다.");
			bfclear();
			char temp = getchar();
			switch (temp)
			{
			case '1':
				for (i = 0; i < 20; i++) { if (!strcmp(base->inven[i].name, "나무")) break; };
				printf("%s:몇 개 사용하시겠습니까?", base->inven[i].name);
				scanf("%d", &restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += restemp * 1;
					printf("%s %d 개 사용하였다.", base->inven[i].name, restemp);
				}
				else printf("갯수가 너무 크거나 작습니다.");
				break;
			case '2':
				for (i = 0; i < 20; i++) { if (!strcmp(base->inven[i].name, "돌")) break; };
				printf("%s:몇 개 사용하시겠습니까?");
				scanf("%d", &restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += (int)(restemp * 1.5);
					printf("%s %d 개 사용하였다.\n", base->inven[i].name, restemp);
				}
				else printf("갯수가 너무 크거나 작습니다.\n");
				break;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
			}
			printf("자원추가를 더 할까요? (하지 않으려면 N 입력)");
			bfclear();
			char lastpic = getchar();
			if (lastpic == 'n' || lastpic == 'N') break;
		}
		//0으로 나눔 예외 발생. 살려줘ㅓㅓㅓㅓㅓ
		int rslt = rand() % ((srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5))) == 0 ? 1 : (srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5));
		if (rslt + base->curlife < base->maxlife)
		{
			base->curlife += rslt;
			printf("%d명의 사람을 구하는데 성공했다\n", rslt);
		}
		else
		{
			int overbody = ((base->curlife + rslt) - base->maxlife);
			base->curlife += rslt - overbody;
			printf("%d명의 사람을 구출했지만, 정착지의 공간이 모자라 %d명의 사람들만 정착지에 들어왔다.\n", rslt, rslt - overbody);
		}
	}
	else printf("파견보낼 사람이 없습니다.\n");
}
void defsrchchk(leader* user)
{
	user->base->def = 0;
	user->base->maxlife = 10;
	for (int j = 0; j < 20; j++)
	{
		user->base->inven[j].stackmax = 30;
	}
	for (int i = 0; i < 20; i++)
	{
		switch (user->base->roomspace[i].roomtype)
		{
		case 1:
			user->base->def += user->base->roomspace[i].aply_bonus;
			break;
		case 2:
			user->base->maxlife += user->base->roomspace[i].aply_bonus;
			break;
		case 3:
			for (int j = 0; j < 20; j++)
			{
				user->base->inven[j].stackmax += user->base->roomspace[i].aply_bonus;
			}
			break;
		default:
			break;
		}
	}
}

void daytime(leader* user)
{
	int actcnt = DAYTIME_ACTCOUNT;
	printf("\t\t%s의 경로당\n", user->username);
	printf("------------------------------------------------\n\n");
	printf("                생존자 수 : %d/%d\n\n", user->base->maxlife, user->base->curlife);
	printf("------------------------------------------------\n\n");

	printf("지금은 낮 시간이다. 아무래도 좀비들의 활동이 줄어들 것 같다.\n");
	while (actcnt > 1)
	{
		printf("무엇을 할까?\n>> 경로당의 시설을 건설하자 (R)\n>> 자원을 찾으러 떠나자 (F)\n>> 조난당한 사람을 구하자  (S)\n\n알파벳 입력>>");
		bfclear();
		char selchar = getchar();
		switch (selchar)
		{
		case 'r': case 'R':
			buildroom(user->base); actcnt--;
			defsrchchk(user);
			break;
		case 'f': case 'F':
			if (finditem(user->base) != 0) actcnt--;
			break;
		case 's': case 'S':
			rescuetribe(user->base); actcnt--;
			break;
		default:
			printf("잘못 입력하셨습니다. 다시 입력하세요\n");
			break;
		}
	}
}

void nighttime(leader* user, int level)
{
	printf("석양이.."); Sleep(1000); printf("점점.."); Sleep(800);
	printf("진다"); Sleep(500); printf("."); Sleep(300); printf("."); Sleep(300); printf("."); Sleep(300); puts("");
	printf("밤이 되었다. 좀비로부터 살아남아야 한다..\n");
	int zombiemax = ((level*level) / 2) + 3;
	int zombiemin = zombiemax / 2;
	int curwave = (rand() % (zombiemax - zombiemin)) + zombiemin;
	printf("좀비 %d마리가 이쪽으로 오고 있다..\n", curwave);
	Sleep(1000);
	if (curwave - user->base->def > user->base->curlife)
	{
		printf("수많은 좀비들의 습격을");
		if ((curwave - user->base->def) - user->base->curlife < 3)
		{
			printf(" 잘 막아내는 듯 했으나, 소수의 좀비들이 바리케이트를 넘어왔다!\n");
			if (((rand() % 6) + 1) < 3)
			{
				int hidepeople = (user->base->curlife / 10) + 1;
				printf("아수라장이 된 경로당에서, %d명만이 간신히 숨어서 버텨내는 데 성공했다..\n", hidepeople);
				user->base->curlife = hidepeople;
			}
			else
			{
				printf("좀비들이 들어오자 아수라장이 된 경로당은 속수무책으로 좀비의 소굴어 되었다..\n");
				user->base->curlife = 0;
			}
		}
		else
		{
			printf("막아내기란 불가능했다..\n");
			user->base->curlife = 0;
		}
	}
	else
	{
		int deathpeople = 0;
		for (int i = (curwave - user->base->def); i > 0; i--)
		{
			if ((rand() % 100) < 33)
			{
				user->base->curlife--;
				deathpeople++;
			}
		}
		if (deathpeople == 0) printf("이번 밤은 무사히 지나갔다. 다행스럽게 사망자는 아무도 없었다.\n");
		else
		{
			printf("이번 밤은 좀비로부터 살아남았다.. %d명의 사람이 좀비와 교전중 세상을 떠났다.\n", deathpeople);
		}
	}
}

void logo()
{
	cursorOff();
	int x,y;
	while (1)
	{
		x = (rand() % 4) + 3, y = rand() % 4;
		gotoxy(x, y); puts("          살       살");
		gotoxy(x, y+1); puts("        살  살     살                                                남              ");
		gotoxy(x, y+2); puts("       살    살    살살살                               남           남                                   라라라라라라    라");
		gotoxy(x, y+3); puts("      살      살   살                     아            남           남남남                 아                      라    라");
		gotoxy(x, y+4); puts("                   살             아      아            남           남            아       아                      라    라");
		gotoxy(x, y+5); puts("                               아    아   아아아        남남남남남   남         아    아    아아아        라라라라라라    라라라라");
		gotoxy(x, y+6); puts("           살살살살            아    아   아                         남         아    아    아            라              라");
		gotoxy(x, y+7); puts("                 살             아아아    아              남남남남남남           아아아     아            라              라");
		gotoxy(x, y+8); puts("           살살살살                       아              남        남                      아            라라라라라라    라");
		gotoxy(x, y+9); puts("           살                                             남남남남남남");
		gotoxy(x, y+10); puts("           살살살살");                                            
		gotoxy(x, y+14); puts("                              디           지지지지지지   지        텍텍텍텍텍    텍 텍           ""                        ""   !!!");
		gotoxy(x, y+15); puts("              디디디디디디디  디                    지    지        텍            텍 텍         ""   리리리리리리    리   ""     !!!");
		gotoxy(x, y+16); puts("              디              디                   지     지        텍텍텍텍  텍텍텍 텍                      리    리        !!!");
		gotoxy(x, y+17); puts("              디              디                 지       지        텍            텍 텍                      리    리        !!!");
		gotoxy(x, y+18); puts("              디              디               지  지     지        텍텍텍텍텍    텍 텍            리리리리리리    리        !!!");
		gotoxy(x, y+19); puts("              디              디             지     지    지                                       리              리        !!!");
		gotoxy(x, y+20); puts("              디디디디디디디  디           지        지   지             텍텍텍텍텍텍              리              리");
		gotoxy(x, y+21); puts("                              디                                                    텍             리리리리리리    리        !!!");
		gotoxy(x, y+22); puts("                                                                                    텍");
		puts(""); puts("");
		puts("						아무키나 눌러서 게임 시작");
		Sleep(1000);
		system("cls");
		if (kbhit()) 
		{
			cursorOn();
			break; 
		}
	}
}

void gameover()
{
	puts("		      !,    ");
	puts("	             ,:");
	puts("	          = #**: .     ");
	puts("	         !=.**.:~#*- ");
	puts("	             *.    ");
	puts("	             ==     ");
	puts("	            !;~;    ");
	puts("	           .* ~-$    ");
	puts("	          ~:!  *: -     ");
	puts("	        ~; .    ., -@  ");
	puts("	        ;.~      :!$*   ");
	puts("	        ;       !  ~@  ");
	puts("	        !          ~# ");
	puts("	        ;          ~$");
	puts("	        -  -.      ~# ");
	puts("	        !=;.    $. *@ ");
	puts("	        ;..........-$  ");
	puts("	      -------~-;;;;~,,,;");
	puts("	     ======;;*####@#=*:; : ");
	puts(""); puts("");
	puts(" ::::::::      :::     ::::    ::::  :::::::::: ");
	puts(":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:        ");
	puts("+:+         +:+   +:+  +:+ +:+:+ +:+ +:+        ");
	puts(":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#   ");
	puts("+#+   +#+# +#+     +#+ +#+       +#+ +#+        ");
	puts("#+#    #+# #+#     #+# #+#       #+# #+#        ");
	puts(" ########  ###     ### ###       ### ########## ");
	puts(" ::::::::  :::     ::: :::::::::::   :::::::::  ");
	puts(":+:    :+: :+:     :+: :+:           :+:    :+: ");
	puts("+:+    +:+ +:+     +:+ +:+           +:+    +:+ ");
	puts("+#+    +:+ +#+     +:+ +#++:++:+#    +#++:++#:  ");
	puts("+#+    +#+  +#+   +#+  +#+           +#+    +#+ ");
	puts("#+#    #+#   #+#+#+#   #+#           #+#    #+# ");
	puts(" ########      ###     ###########   ###    ### ");
}


void main()
{
	leader realuser;
	shelter base;
	int liveday;
	while (1)
	{
		liveday = 0;
		base.maxlife = 10;
		base.curlife = base.maxlife;
		realuser.base = &base;
		strcpy(realuser.base->inven[0].name, "나무");
		strcpy(realuser.base->inven[1].name, "돌");
		realuser.base->inven[0].cur_cnt = 30;
		realuser.base->inven[0].stackmax = 30;

		logo();

		printf("당신의 이름은 무엇입니까? (영어 20글자 한글 10글자 이내로)");
		scanf("%s", realuser.username);


		for (int i = 0; i < 20; i++)
			realuser.base->roomspace[i].roomtype = 0;
		while (1)
		{
			daytime(&realuser);
			nighttime(&realuser, liveday);
			if (realuser.base->curlife <= 0)
			{
				gameover();
				puts("===========================================");
				printf("\t모두가 죽었습니다. 살아남은 사람은 없습니다.\n");
				break;
			}
			liveday++;
		}
		printf("\t%d일간 살아남았다.");
		printf("새로운 게임을 시작하시겠습니까? (Y를 입력해 새 게임 시작)");
		bfclear();
		char resel = getchar();
		if (!(resel == 'y' || resel == 'Y')) break;
		else system("cls");
	}
}